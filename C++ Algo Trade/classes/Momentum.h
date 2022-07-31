//Momentum trading algorithm header file

#ifndef MOMENTUM_H
#define MOMENTUM_H
#include "AlgorithmTester.h"
#include <string>
using namespace std;

class Momentum: public AlgorithmTester{
	public:
		Momentum(int rollingWindow=5,double percent=.2,string start_date="2015-9-30", string end_date="2015-12-31",double transactionFee=8,double initialInvestment=50000,int maxCompanies=20);
		virtual void runBacktest(void);           					//Function to run algorithm on historical data
		virtual void runLive(int);               					//Function to run algorithm on live data
		void setRollingWindow(int);   							//Function to set rolling window size
		void setPercent(double); 								//Functino to set threshold percent

	private:
		double calcDelta(string ticker, string start, string end);  	//Function to calculate price change between two dates
		int rollingWindow; 										//Stores size for a rolling window
		double percent; 										//Stores percentage for threshold calculation
};


#endif
