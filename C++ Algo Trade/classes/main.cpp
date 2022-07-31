// Main Function
//

#include "AlgorithmTester.h"
#include "MeanReversion.h"
#include "Momentum.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(void)
{
	// Clear screen and display a neat screen to the user
	system("clear");
	cout << "#############################################################" << endl;
	cout << "##################   ALGORITHMIC TRADING   ##################" << endl;
	cout << "#############################################################" << endl << endl;

	cout << "                         Authors                             " << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "        Brad Sherman, Brent Marin, Charlie Osborne           " << endl;
	cout << "            Fundamentals of Computing 2 Project              " << endl << endl;

	cout << "For this program there are a few bits of information we need " << endl;
	cout << "to find out about what you want to do first." << endl;

	string name;                    // Get name of user for a personalized experience
	int money=50000;                // Initial investment
	int numcomps=20;	            // How diverse the user would like their portfolio
	string start="2015-09-30:";     // Start date used for back testing
	string end="2015-12-31";	    // End date used for back testing
	double transFee = 8.00;         // Transaction fee for buying/selling stocks
	int testtype;                   // 1 for a live test, 0 for a back test
	int algtype;                    // 1 for MeanReversion, 0 for Momentum
	int numtodisplay;               // Amount of stocks shown on a live test
	int rollingWindow=25;              // Width of window to consider data from

	cout << "Before we start, please enter your name: ";
	cin >> name;
	cout << endl;
	cout << "Thanks for using our trader " << name << ". First we need to decide " << endl;
	cout << "whether you would like to do live buying/selling or if you   " << endl;
	cout << "would like to run a back test. Enter 1 for live test and 0   " << endl;
	cout << "for a back test: ";
	cin >> testtype;
	cout << endl;
	cout << "Now, we need to know which algorithm you would like to use.  " << endl;
	cout << "The choices are Mean Reversion and Momentum. See below for details:" << endl;
	cout << "Mean Reversion: " << endl;
	cout << "	This algorithm calculates a running average for a certain " << endl;
	cout << "	window, and if a stock is below its mean, it would be a   " << endl;
	cout << "	good stock to buy. If a stock is above its mean, it would " << endl;
	cout << "	be a good stock to sell. This is because the algorithm    " << endl;
	cout << "	assumes every stock will eventually go back to its mean.  " << endl << endl;
	cout << "Momentum: " << endl;
	cout << "	This algorithm attempts to \"ride the waves\" of a stock. " << endl;
	cout << "	It searches for increases in price and buys it before the " << endl;
	cout << "	stock reaches its peak. Adversely, it sells stocks that   " << endl;
	cout << "	begin to dip in price before it drops all the way down.   " << endl;
	cout << "	This algorithm is better suited for more up to date data, " << endl;
	cout << "	as we only have daily data." << endl;
	cout << endl << "Enter 1 for Mean Reversion and 0 for Momentum: ";
	cin >> algtype;


	if( testtype ) { // Live Test
		cout << "For a live test, we will suggest to you the top stocks the " << endl;
		cout << "day based on the algorithm you chose. All we need to know  " << endl;
		cout << "how many stocks you would like to be displayed:            " << endl;
		cin >> numtodisplay;
		if( algtype ) { // Mean Reversion
			MeanReversion algorithm(rollingWindow,start,end,transFee,money,numcomps);
			cout << "after meanreversion object instantiated" << endl;
			algorithm.runLive(numtodisplay);

		} else {        // Momentum
			cout << "What percentage of today's stock price should trigger a buy/sell (we suggest .2)?"<<endl;
			double percent;
			cin >> percent;
			Momentum algorithm(rollingWindow,percent,start, end,transFee,money,numcomps);
			algorithm.runLive(numtodisplay);
		}
	}else {          // Back Test
		cout << "Now for a few more specific details." << endl;
		cout << "How much money do you have to invest?" << endl;
		cin >> money;
		cout << "How diverse would you like your portfolio to be? (How many different companies)" << endl;
		cin >> numcomps;
		cout << "For back testing, you need to set a start and end date (format is Year-Mn-Dy )." << endl;
		cout << "Start date: ";
		cin >> start;
		cout << endl << "End date: ";
		cin >> end;
		if( algtype ) { // Mean Reversion
			cout << "What is the desired rolling mean window (we suggest 50)?"<<endl;
			cin >> rollingWindow;
			MeanReversion algorithm(rollingWindow, start,end,transFee,money,numcomps);
			algorithm.runBacktest();
		} else {        // Momentum
			cout << "What is the desired rolling mean window (we suggest 5)?"<<endl;
			cin >> rollingWindow;
			cout << "What percentage of today's stock price should trigger a buy/sell (we suggest .2)?"<<endl;
			double percent;
			cin >> percent;
			Momentum algorithm(rollingWindow,percent,start, end,transFee,money,numcomps);
			algorithm.runBacktest();
		}
	}
}

