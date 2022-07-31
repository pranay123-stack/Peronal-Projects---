//Portfolio class definitions

#include "Portfolio.h"
using namespace std;

//Default Constructor to set size to 0
Portfolio::Portfolio(){
	size = 0;
}

//Destructor to free any dynamically allocated stocks
Portfolio::~Portfolio(){
	for(int i=0;i<stock_list.size();i++)
		delete stock_list[i];
	size = 0;
}

//Function to add a stock to a portfolio
void Portfolio::addStock(string ticker_name,double low, double high, double open, double close, string ltd, int volume){
	stock_list.push_back(new Stock(ticker_name,low,high,open,close,ltd,volume));
	Companies.insert(pair<string,int>(ticker_name,Companies[ticker_name]++));
	calculateValue(); //Recalculate portfolio value w/ new stock
	size = stock_list.size();
}

//Function to search for and remove stock from portfolio
void Portfolio::removeStock(string ticker_name){
	for(int i=0;i<stock_list.size();i++){
		if(stock_list[i] -> getSymbol() == ticker_name){
			delete stock_list[i];
			stock_list.erase(stock_list.begin() + i);
		}	
	}
	calculateValue();
	size = stock_list.size();
}

//Function to calculate total portfolio value
void Portfolio::calculateValue(void){
	current_value = 0;
	for(int i=0;i<stock_list.size();i++)
		current_value += stock_list[i] -> getBid();
}

//Function to return total portfolio value
double Portfolio::getPortfolioValue(void){
	return current_value;
}

//Retrieve number of stocks in portfolio
int Portfolio::getSize(){
	return size;
}
