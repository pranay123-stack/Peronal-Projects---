//Algorithm tester base class implementation

#include "AlgorithmTester.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <map>
using namespace std;

//Constructor function
AlgorithmTester::AlgorithmTester(string start_date, string end_date, double transactionFee, double initialInvestment, int numCompanies){
	//Set constructor variables
	setStartDate(start_date);
	setEndDate(end_date);
	setInitialInvestment(initialInvestment);
	setTransactionFee(transactionFee);
	setNumCompanies(numCompanies);
	currentCash = initialInvestment;
	ifstream in("../historical_data/tickers.txt");
	string ticker;

	//Puts all the valid tickers into a list
	if(in.is_open()){
		while (in >> ticker){
			tickerList.push_back(ticker);
		}
	}else{
		cout << "Error: Could not read in tickers list" << endl;
	}

	//Read in historical data	
	ifstream infile("../historical_data/tickers.txt");
	if(infile.is_open()){
		//Creates a map where each stock ticker is the key
		while (infile >> ticker){
			vector<string> vec;
			stockHistoricalData.insert(make_pair(ticker, vec));
		}

		//Maps all of the historical data of a stock to its ticker
		for(map< string, vector<string> >::iterator it = stockHistoricalData.begin(); it != stockHistoricalData.end(); it++){
			string pathToStock = "../historical_data/historical_data_csv/";
			pathToStock.append(it->first);
			ifstream in(pathToStock.c_str());
			string dataLine;
			if(in.is_open()){
				getline(in, dataLine);
				while (getline(in, dataLine))
					stockHistoricalData[it->first].push_back(dataLine);
			}else
				cout<<"Could not open file "<<pathToStock<<endl;
		}
	}else
		cout<<"Could not open list of tickers"<<endl;
}

// Get data from a certain ticker from start to end date, data is returned as a vector of stocks, with each stock containing the data at a given day
vector<Stock*> AlgorithmTester::getData(string ticker, string start, string end){
	vector<Stock*> StockData;
	for(vector<string>::iterator it = stockHistoricalData.find(ticker)->second.begin(); it != stockHistoricalData.find(ticker)->second.end(); it++){
		string data = *it;
		int pos = data.find(',',0);
		string date = data.substr(0,pos);
		if(checkDate(date,start,end)){
			for( int i = 0; i < ticker.size(); i++) ticker[i] = toupper(ticker[i]);
			int nextpos = data.find(',',pos+1);
			string open = data.substr(pos+1,nextpos-pos-1);
			pos = data.find(',',nextpos+1);
			string high = data.substr(nextpos+1,pos-nextpos-1);
			nextpos = data.find(',',pos+1);
			string low = data.substr(pos+1,nextpos-pos-1);
			pos = data.find(',',nextpos+1);
			string close = data.substr(nextpos+1,pos-nextpos-1);
			nextpos = data.find(',',pos+1);
			string volume = data.substr(pos+1,nextpos-pos-1);
			pos = data.find(',',nextpos+1);
			string adjclose = data.substr(nextpos+1,pos-nextpos-1);
			StockData.push_back(new Stock(ticker,atof(low.c_str()),atof(high.c_str()),atof(open.c_str()),atof(close.c_str()),date,atoi(volume.c_str())));			
		}
	}
	return StockData;
}

//Deletes a dynamically allocated stock vector
void AlgorithmTester::destroyData(vector<Stock*> & StockData){
	for( int i = 0; i < StockData.size(); i++ ){
		delete StockData[i];
	}
	StockData.clear();
}

/////////////////////////////////////////////////////////////////////////////
// Get and Set Functionality
////////////////////////////////////////////////////////////////////////////

//Transaction fee set function
void AlgorithmTester::setTransactionFee(double fee){
	if(fee >= 0)
		transactionFee = fee;
	else{
		cout<<"Fee must be a positive value"<<endl;
		transactionFee = 0;
	}
}

//Max number of companies in portfolio set function
void AlgorithmTester::setNumCompanies(int maxCompanies){
	if(maxCompanies > 0)
		numCompanies = maxCompanies;
	else{
		cout<<"Number of companies must be greater than 1"<<endl;
		numCompanies = 20;
	}
}

//Set initial dollar amount to invest
void AlgorithmTester::setInitialInvestment(double dollars){
	if(dollars > 0)
		initialInvestment = dollars;
	else{
		cout<<"Initial investment amount must be greater than 0"<<endl;
		initialInvestment = 50000;
	}
}

//Return transaction fee
double AlgorithmTester::getTransactionFee(){
	return transactionFee;
}

//Returns the currentCash, which indicates how much money the algorithm currently has to work with
double AlgorithmTester::getCurrentCash(){
	return currentCash;
}

//Sets currentCash
void AlgorithmTester::setCurrentCash(double cCash){
	currentCash = cCash;
}

//Returns the number of companies
int AlgorithmTester::getNumCompanies(){
	return numCompanies;
}

//Returns the start date of the window to backtest the algorithm
string AlgorithmTester::getStartDate(){
	return start_date;
}

//Returns the end date of the window to test the algorithm
string AlgorithmTester::getEndDate(){
	return end_date;
}

//Returns the initial investment the algorithm has to work with
double AlgorithmTester::getInitialInvestment(){
	return initialInvestment;
}

//////////////////////////////////////////////////////////////////////
// Date Functionality
/////////////////////////////////////////////////////////////////////

/* The function below are all functions to deal with dates. We considered a date object but decided against it because
 * we though we would need minimal date functionality, plus we didn't want to deal with multiple inheritance that would
 * seem natural if we added a date class. 
 */

//Startdate set function
void AlgorithmTester::setStartDate(string date){
	string month = date.substr(5,2);
	string year = date.substr(0,4);
	string day = date.substr(8,2);
	int monthnum = atoi(month.c_str());
	int yearnum = atoi(year.c_str());
	int daynum = atoi(day.c_str());
	if((yearnum == 2004 && monthnum < 8) || yearnum < 2004 || (yearnum == 2004 && monthnum == 8 && daynum < 19)){
		cout<<"Earliest date supported by historical data is 2004-08-19"<<endl;
		start_date = year + '-' + month + '-' + day;
	}	
	else{ 
		start_date = date;
	}
}

//Enddate set function
void AlgorithmTester::setEndDate(string date){
	string month = date.substr(5,2);
	string year = date.substr(0,4);
	string day = date.substr(8,2);
	int monthnum = atoi(month.c_str());
	int yearnum = atoi(year.c_str());
	int daynum = atoi(day.c_str());
	if( yearnum > 2015 || daynum > 31 || monthnum > 12 ){
		cout<<"Latest date supported by historical data is 2012-12-31"<<endl;
		exit(EXIT_FAILURE);
	}
	else end_date = date;
	if( isGreater(start_date,end_date) ) {
		cout << "You can't have a later start date than end date. Pick a new end date: " << endl;
		cout << "start date: " << start_date << endl;
		cout << "end date:   " << end_date << endl;
		string newdate;
		cin >> newdate;
		setEndDate(newdate);
	}
}

// Increment current date by inc number of days
string AlgorithmTester::incrementDay(string date, int inc){
	// For the sake of simplicity, we are assuming no leap years 
	string::size_type sz;
	string month = date.substr(5,2);
	string year = date.substr(0,4);
	string day = date.substr(8,2);
	int monthnum = atoi(month.c_str());
	int	yearnum = atoi(year.c_str());
	int daynum = atoi(day.c_str());
	int increment = 1;
	int i = 1; 
	while( i <= inc ){
		if( daynum + increment > 28 && monthnum == 2 ) {
			monthnum++;
			daynum = (daynum+increment) - 28;
		}else if( daynum + increment > 30 && (monthnum == 4 || monthnum == 6 || monthnum == 9 || monthnum == 11)) {
			daynum = (daynum+increment) - 30;
			if( monthnum == 12 ) {
				monthnum = 1;
				yearnum++;
			}else monthnum++;
		}else if( daynum + increment > 31 && (monthnum == 1 || monthnum == 3 || monthnum == 5 || monthnum == 7 || monthnum == 8 || monthnum == 10 || monthnum == 12)){
			daynum = (daynum+increment) - 31;
			if( monthnum == 12 ) {
				monthnum = 1;
				yearnum++;
			}else monthnum++;
		}	else daynum+=increment;
		i++;
	}
	stringstream ss1;
	ss1 << monthnum;
	string newmonth = ss1.str();
	if( monthnum < 10 ) newmonth = '0' + newmonth;
	stringstream ss2;
	ss2 << yearnum;
	string newyear = ss2.str();
	stringstream ss3;
	ss3 << daynum;
	string newday = ss3.str();
	if( daynum < 10 ) newday = '0' + newday;

	string newdate;
	newdate = newyear + '-' + newmonth + '-' + newday;
	return newdate;
}

// Returns 1 if date is greater than date2
int AlgorithmTester::isGreater(string date, string date2){
	string month = date.substr(5,2);
	string year = date.substr(0,4);
	string day = date.substr(8,2);
	int monthnum = atoi(month.c_str());
	int yearnum = atoi(year.c_str());
	int daynum = atoi(day.c_str());
	string smonth = date2.substr(5,2);
	string syear = date2.substr(0,4);
	string sday = date2.substr(8,2);
	int month2 = atoi(smonth.c_str());
	int year2 = atoi(syear.c_str());
	int day2 = atoi(sday.c_str());
	if( (yearnum == year2 && monthnum > month2) || (yearnum == year2 && monthnum == month2 && daynum > day2)  || yearnum > year2) {
		return 1;
	}   
	else return 0;
}

//Returns 1 if a date is within a range of dates
int AlgorithmTester::checkDate(string date, string start, string end){
	string::size_type sz;
	string year = date.substr(0,4);
	string month = date.substr(5,2);
	string day = date.substr(8,2);
	int monthnum = atoi(month.c_str());
	int yearnum = atoi(year.c_str());
	int daynum = atoi(day.c_str());
	string smonth = start.substr(5,2);
	string syear = start.substr(0,4);
	string sday = start.substr(8,2);
	int startmonth = atoi(smonth.c_str());
	int startyear = atoi(syear.c_str());
	int startday = atoi(sday.c_str());
	string emonth = end.substr(5,2);
	string eyear = end.substr(0,4);
	string eday = end.substr(8,2);
	int endmonth = atoi(emonth.c_str());
	int endyear = atoi(eyear.c_str());
	int endday = atoi(eday.c_str());
	if( (yearnum == endyear && monthnum > endmonth) || yearnum > endyear || (yearnum == endyear && monthnum == endmonth && daynum > endday)) return 0;
	else if( (yearnum == startyear && monthnum < startmonth) || yearnum < startyear || (yearnum == startyear && monthnum == startmonth && daynum < startday)) return 0;
	else return 1;
}


