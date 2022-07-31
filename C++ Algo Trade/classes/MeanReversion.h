//Mean reversion trading algorithm header file

#ifndef MEANREVERSION_H
#define MEANREVERSION_H
#include "AlgorithmTester.h"
#include <string>
using namespace std;

class MeanReversion: public AlgorithmTester{
	public:
		MeanReversion(int rollingWindow=50,string start_date="2015-9-30", string end_date="2015-12-31",double transactionFee=8,double initialInvestment=50000,int maxCompanies=20);
		virtual void runBacktest(void);           					//Function to run algorithm on historical data
		virtual void runLive(int num2Display);               			//Function to display stock picks with live data
		void setRollingWindow(int);   							//Function to set rolling window size

	private:
		double calcWindowMean(string ticker, string start, string end);  //Function to calculate mean for a window
		int rollingWindow; 										//Stores size for a rolling window
};


#endif
