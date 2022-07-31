//AlgorithmTester base class for algorithms
//
//All dates should be formatted YEAR-MN-DY in this and derived classes

#ifndef ALGORITHMTESTER_H
#define ALGORITHMTESTER_H
#include "Stock.h"
#include "Portfolio.h"
#include<string>
#include <map>

using namespace std;

class AlgorithmTester{
	public:
		AlgorithmTester(string start_date, string end_date, double transactionFee, double initialInvestment, int numCompanies);
		void setStartDate(string date);       			     		//Set backtest startdate
		void setEndDate(string date);         			     		//Set backtest enddate 
		int isGreater(string date1, string date2); 					//Check if date string argument one is greater than date string argument 2
		int checkDate(string date1, string date2, string date3);    	//Check if date1 is between date2 and date3
		void setTransactionFee(double fee); 			     		//Set transaction fee to buy any amount of one company's stock at one time
		void setNumCompanies(int maxCompanies);                		//Set max number of stocks that will be in the portfolio at once
		void setInitialInvestment(double initialInvestment);   		//Set the initial dollar amount of stocks to be invested in
		vector<Stock*> getData(string ticker, string dt1, string dt2);   //Get data for stock inbetween date dt1 and date dt2          
		void destroyData(vector<Stock*>&);                               //Deallocate the data for a returns from getData **MUST be called after getData**
		string incrementDay(string date,int increment); 				//Increment date by increment days
		virtual void runBacktest(void)=0;   						//All derived algorithms must be able to run a backtest
		virtual void runLive(int num2Display)=0; 				     //All derived algorithms must implement a live trading function
		Portfolio trading_folio;		          		               //Portfolio object for algorithm to store stocks
		vector<string> tickerList; 								//List of all tickers on the NASDAQ exchange
		double getCurrentCash(); 								//Get function for current cash reserves
		void setCurrentCash(double); 								//Set current cash reserve
		int getNumCompanies(); 									//Show max number of companies for portfolio
		double getTransactionFee(); 								//Show the transaction fee
		string getStartDate(); 									//Show backtesting start date
		string getEndDate(); 									//Show backtesting end date
		double getInitialInvestment(); 							//Show initial investment amount

	private:
		string start_date;  				                         //When to start testing an algorithm
		string end_date;   				          	               //When to end testing an algorithm
		double transactionFee; 					                    //Transaction fee to buy any amount of one company's stock at one time
		double initialInvestment;          	          	          //Dollar amount to start trading with
		int numCompanies;                                     			//Max number of companies to own stock in at one time
		double currentCash; 									//Stores cash reserve during algorithm
		map<string, vector<string> > stockHistoricalData;                //Map that stores loaded historical data
};


#endif

