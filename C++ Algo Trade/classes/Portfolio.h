//Portfolio class header

#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include "Stock.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class Portfolio{
	public:
		Portfolio(); 												//Default constructor
		~Portfolio();                         							//Deconstructor to delete dynamically allocated stock objects
		void addStock(string,double, double, double, double, string, int);    //Add a stock (see Portfolio.cpp for function arguments)
		void removeStock(string ticker_name); 							//Remove a stock by ticker name
		double getPortfolioValue(void);       							//Returns current value of all stocks in portfolio	
		map<string,int> Companies;            							//Dictionary of Stock tickers, Num stocks
		vector<Stock*> stock_list;            							//List of pointers to stocks in portfolio
		int getSize(void);		    		  							//Get number of stocks
	private:
		void calculateValue(void); 						               //Updates total value of all stocks in portfolio
		double current_value;                						     //Holds total value of all stocks in portfolio
		int size;                            							//Number of stocks in the portfolio
};


#endif
