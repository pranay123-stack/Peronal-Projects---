//Momentum algorithm object

#include "AlgorithmTester.h"
#include "Momentum.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

//Default constructor
Momentum::Momentum(int rollingWindow, double percent, string start, string end, double transactionFee,double initialInvestment, int maxCompanies):AlgorithmTester(start,end,transactionFee,initialInvestment,maxCompanies){
	setRollingWindow(rollingWindow);
	setPercent(percent);
	if(isGreater(incrementDay(start,rollingWindow),end)){
		cout << "Your start and end date are too close together. " << endl;
		cout << "The end date is being pushed back" << endl;
		setEndDate(incrementDay(start,rollingWindow));
	}
}

//set rolling window for delta calculation
void Momentum::setRollingWindow(int window){
	if(window > 0)
		rollingWindow = window;
	else{
		cout<<"Window must be at least 1"<<endl;
		rollingWindow = 2;
	}
}

//Function to set percent of stock price change to buy and sell stock
void Momentum::setPercent(double pct){
	if(pct > 0 && pct < 1){
		percent = pct;
	}else{
		cout<<"Percent must be between 0 and 1"<<endl;
		percent = .2;
	}
}

//calculate close price change betweeen startDate and endDate for a stock
double Momentum::calcDelta(string ticker,string startDate, string endDate){
	vector<Stock*> stocks = getData(ticker, startDate, endDate);
	if(stocks.size() != 0){
		double delta = ((stocks[stocks.size()-1] -> getClose()) - (stocks[0] -> getClose()));
		destroyData(stocks);
		return delta;
	}else
		return 0;
}

//Function to run algorithm on historical data
void Momentum::runBacktest(void){
	string windowBegin = getStartDate();
	string currentDate = incrementDay(getStartDate(),50);
	int companiesOwned = 0;
	vector<double> buyPrices;

	//Loop until start date reaches end date
	while(isGreater(getEndDate(),currentDate)){		
		cout<<"Date: "<<currentDate<<endl;
		cout<<"Current cash: "<<getCurrentCash()<<endl;
		cout<<"You are invested in "<<trading_folio.Companies.size()<<" companies."<< endl;

		//Sell any stocks we need to
		for(map<string,int>::iterator it = trading_folio.Companies.begin(); it != trading_folio.Companies.end(); it++){
			vector<Stock*> tmp = getData(it -> first,currentDate,currentDate);
			if(tmp.size() == 1){
				Stock current = *tmp[0];
				double delta = calcDelta(it -> first,windowBegin,currentDate);
				double currentPrice = current.getClose();
				double thresh = currentPrice * percent; //Sell triggered when stock price changes more than percent of the current price
				if(thresh <= (delta * -1.0)){
					cout<<"sell all "<<(it -> first)<<" stocks"<<endl;
					for(int i=0;i<trading_folio.getSize();i++){
						if((trading_folio.stock_list[i] -> getSymbol()) == (it -> first)){
							setCurrentCash(getCurrentCash() + currentPrice);	
						}
					}
					trading_folio.Companies.erase(it);
					trading_folio.removeStock(current.getSymbol());
					companiesOwned--;
				}
			}
			destroyData(tmp);
		}
		if( companiesOwned != getNumCompanies() ){ //No need to search through companies if the portfolio is full

			//Look through list of tickers for stocks below mean and keep a list of the top numCompanies
			vector<string> potentialTickers;
			vector<double> potentialPrices;
			vector<double> potentialDiffs;
			map<double,string> pairs;
			for(int i=0;i<tickerList.size();i++){
				//Get info on stock
				vector<Stock*> tmp = getData(tickerList[i],currentDate,currentDate); //Get only stock for day
				if(tmp.size() == 1){ //Check there is a stock for the day
					Stock currentStock = *tmp[0];
					double delta = calcDelta(tickerList[i],windowBegin,currentDate);
					double currentPrice = currentStock.getClose();
					double thresh = percent * currentPrice; //This is percent of current price change
					string symbol = currentStock.getSymbol();

					//Check if they are already in the portfolio
					bool inPortfolio = false;
					for(map<string,int>::iterator iter = trading_folio.Companies.begin(); iter != trading_folio.Companies.end(); iter++){
						string folio_symbol = iter->first;
						if(folio_symbol == symbol)
							inPortfolio = true;
					}

					//Evaluate stock based on criteria in if statement
					if(delta > thresh && !inPortfolio && currentStock.getVolume() >= 500000 && currentStock.getClose() > 2 ){
						pairs.insert(pair<double,string>(delta,symbol));
					}
				}
				destroyData(tmp);
			}

			//Buy stock in the top numCompanies found

			double dollarsPerCompany = getCurrentCash()/(double)(getNumCompanies() - companiesOwned);
			vector<Stock*> newStock;

			cout << "Considering " << pairs.size() << " companies." << endl;
			for(map<double,string>::iterator k=pairs.begin(); k != pairs.end(); k++){  
				double totalBought = 0;
				newStock = getData(k -> second,currentDate,currentDate);
				if(totalBought + newStock[0]->getClose() + getTransactionFee() < dollarsPerCompany){
					while(totalBought + newStock[0]->getClose() + getTransactionFee() < dollarsPerCompany){
						setCurrentCash(getCurrentCash() - newStock[0]->getClose());
						trading_folio.addStock(k->second,newStock[0] -> getLow(),newStock[0] -> getHigh(), newStock[0] -> getOpen(), newStock[0] -> getClose(), newStock[0] -> getLastTradeDate(), newStock[0] -> getVolume());
						totalBought += newStock[0]->getClose();
					}
					setCurrentCash(getCurrentCash() - getTransactionFee());
					companiesOwned++;
					cout<<"bought "<< trading_folio.Companies[k->second]<<" stocks of "<<k->second<<endl;
				}
				if(companiesOwned >= getNumCompanies())
					break;

			}
			destroyData(newStock);	
		}
		//Increment to the next day and repeat
		windowBegin = incrementDay(windowBegin,1);
		currentDate = incrementDay(currentDate,1);		
	}

	//At end of testing, cash in all stocks and display earnings results
	double currentPrice;
	for(int i=0;i<trading_folio.getSize();i++){
		currentPrice = trading_folio.stock_list[i]->getClose();
		setCurrentCash(getCurrentCash() + currentPrice);	
	}
	cout << "Initial Investment was: $" << getInitialInvestment()<< endl;
	cout << "Cash after running algortihm: $" << getCurrentCash() << endl;
	cout << "Total profit was: $" << getCurrentCash()-getInitialInvestment() <<endl;
}

//Function to run algorithm daily on live data
void Momentum::runLive(int numToDisplay){
	//Read in ticker list
	vector<Stock*> stockVector;
	for(int i=0;  i<tickerList.size(); i++){
		system("clear");
		cout << "Now loading all the Stocks... this may take a while" << endl;
		cout << ((double)i/tickerList.size())*100 << "% of the stocks loaded. " << endl;
		cout << "Loading " << tickerList[i] << endl;
		stockVector.push_back(new Stock(tickerList[i]));
	}	
	
	//Look for best stocks in ticker list
	map<double, string> deltas;
	for(int i=0;i<stockVector.size();i++){
		//Note this is a one day delta, it would be better to keep an up to date database of values for this
		double delta = (stockVector[i] -> getClose()) - (stockVector[i] -> getOpen());
		if(delta > 0)
			deltas.insert(pair<double, string>(delta,stockVector[i] -> getSymbol()));	
	}

	//Display the top found stocks
	int j = 0;
	cout << "Here are the top " << numToDisplay << " quickest moving stocks today recommended by the momentum algorithm:" << endl;
	for(map<double, string>::iterator iter = deltas.begin(); iter != deltas.end(); iter++){
		cout << j+1 << ": " << iter->second;
		j++;
		if(j >= numToDisplay)
			break;
	}
	destroyData(stockVector);
}
