// Brad Sherman
// Implementation for stock class

#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string>
#include"Stock.h"
#include<curl/curl.h>
#include<algorithm>
using namespace std;

//Curl specific callback function
static size_t WriteCallback(void * contents, size_t size, size_t nmemb, void * userp){
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

Stock::Stock(string sym){
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	string contents;
	if(curl){
		//Make request for JSON
		string baseURL = "https://www.enclout.com/api/v1/yahoo_finance/show.json?auth_token=xxxxxx&text=";
		string URL;
		URL = baseURL + sym;
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contents);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if( contents.find("N/A",0) ){
			ask = 0;
			bid = 0;
			last_trade_date = "N/A";
			low = 0;
			high = 0;
			low_52_weeks = 0;
			high_52_weeks = 0;
			volume = 0;
			open = 0;
			close = 0;
		

		//Parse JSON into our data members
		int pos = contents.find('\"', 10);
		int nextpos = contents.find('\"', pos + 1);
		symbol = contents.substr(pos+1, nextpos-pos-1);
		for( int i = 0; i < symbol.length(); i++ ) symbol[i] = toupper(symbol[i]);
		} else{
			int pos = contents.find('\"', 10);
			int nextpos = contents.find('\"', pos + 1);
			symbol = contents.substr(pos+1, nextpos-pos-1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			ask = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			bid = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			last_trade_date = contents.substr(pos+1, nextpos-pos-1);
			for(int i=0;i<2;i++){ //Reformat dates to match historical data
				int pos = last_trade_date.rfind(string("/"));
				last_trade_date.replace(pos,1,string("-"));
			}
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			low = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			high = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			low_52_weeks = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			high_52_weeks = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			volume = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			open = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			pos = contents.find('\"', nextpos+1);
			nextpos = contents.find('\"', pos + 1);
			close = atof(contents.substr(pos+1, nextpos-pos-1).c_str());
		}
	}
}

// Other constructor for historical data
Stock::Stock(string sym, double l, double h, double o, double c, string ltd, int v){
	symbol = sym;
	low = l;
	high = h;
	open = o;
	close = c;
	last_trade_date = ltd;
	volume = v;
}

//Get functions for class
string Stock::getSymbol(){
	return symbol;
}
double Stock::getAsk(){
	return ask;
}
double Stock::getBid(){
	return bid;
}
double Stock::getLow(){
	return low;
}
double Stock::getHigh(){
	return high;
}
double Stock::getOpen(){
	return open;
}
double Stock::getClose(){
	return close;
}
double Stock::getLow52Weeks(){
	return low_52_weeks;
}
double Stock::getHigh52Weeks(){
	return high_52_weeks;
}
string Stock::getLastTradeDate(){
	return last_trade_date;
}
int Stock::getVolume(){
	return volume;
}

