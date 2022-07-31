//Author: Brent Marin
//Description: Header file for stock class

#ifndef STOCK_H
#define STOCK_H
#include <string>
using namespace std;

class Stock{
	public:
		Stock(string ticker); 							//Takes stock symbol to load live data
		Stock(string,double,double,double,double,string,int);  //Load historical data into object (see Stock.cpp for arguments)
		string getSymbol();           				     //Returns stock ticker symbol
		double getAsk();              				     //Returns ask price (how much you can buy the stock for)
		double getBid();              				     //Returns bid price (how much you can sell the stock for)
		double getLow();               				     //Returns low stock price for the day
		double getHigh();             				     //Returns high stock price for the day
		double getOpen();             				     //Returns stock price at open
		double getClose();              					//Returns stock price at close
		double getLow52Weeks();         					//Returns 52 week low stock price
		double getHigh52Weeks();        					//Returns 52 week high stock price
		int getVolume();                					//Returns trading volume for the day
		string getLastTradeDate();      					//Returns date last trade of this stock was made

	private:
		string symbol;                  					//Ticker symbol
		double ask;                     					//How much you can buy stock for
		double bid;                     					//How much you can sell stock for
		double low;                     					//Low on the day
		double high;                    					//High on the day
		double open;                    					//Open price
		double close;                   					//Close price
		double low_52_weeks;            					//52 week low price
		double high_52_weeks;           					//52 week high price
		int volume;                     					//Daily trading volume
		string last_trade_date;         					//Date of last traded stock
};

#endif
