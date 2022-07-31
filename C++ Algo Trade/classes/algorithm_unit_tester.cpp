// Testing program for algorithm tester base class

#include<iostream>
#include"AlgorithmTester.h"
#include"Stock.h"
#include<vector>
using namespace std;

int main(){
	
	string start = "2012-01-01";
	string end = "2014-12-31";
	double trans = 20;
	double initinvest = 20000;
	int numcomps = 10;
//	AlgorithmTester A1(start,end,trans,initinvest,numcomps); 
/*	Used for testing, but cannot be instantiated now because it is an abstract class
	
	// test old dates
	string testdate = "2003-10-12";
	cout << "should be a failure" << endl;
	A1.setStartDate(testdate);
	testdate = "2004-07-20";
	cout << "should be a failure" << endl;
	A1.setStartDate(testdate);
	testdate = "2004-09-10";
	cout << "should be a success" << endl;
	A1.setStartDate(testdate);
	testdate = "2004-08-09";
	cout << "should be a failure" << endl;
	A1.setStartDate(testdate);
	testdate = "2004-08-19";
	cout << "should be a success" << endl;
	A1.setStartDate(testdate);
	// test newer dates
	testdate = "2012-12-31";
	cout << "should be a success" << endl;
	A1.setEndDate(testdate);
	testdate = "2012-12-32";
	cout << "should be a failure" << endl;
	A1.setEndDate(testdate);
	// Test having a more recent start time than end time
	AlgorithmTester A2(end,start,trans,initinvest,numcomps);

	// Test checkDate function
	string date1 = "2008-01-12";
	string date2 = "2012-03-13";
	testdate = "2010-02-04";
	cout << "should be success" << endl;
	if( A1.checkDate(testdate,date1,date2) ) cout << "Valid date" << endl;
	date1 = testdate;
	date2 = testdate;
	cout << "Not sure what will happen" << endl;
	if( A1.checkDate(testdate,date1,date2) ) cout << "Valid date" << endl;

	// Test incrementDay method
	testdate = "2012-02-28";
	string newdate = A1.incrementDay(testdate,50);
	cout << testdate << " + 50 = " << newdate << endl;
	testdate = "2010-04-29";
	newdate = A1.incrementDay(testdate,50); 
	cout << testdate << " + 50 = " << newdate << endl;
	testdate = "2008-01-30";
	newdate = A1.incrementDay(testdate,50);
	cout << testdate << " + 50 = " << newdate << endl;
	testdate = "2009-12-30";
	newdate = A1.incrementDay(testdate,50);
	cout << testdate << " + 50 = " << newdate << endl;
	testdate = "2005-04-16";
	newdate = A1.incrementDay(testdate,50);
	cout << testdate << " + 50 = " << newdate << endl;

	// Test getData method
	vector<Stock*> myStocks;
	myStocks = A1.getData("GOOG","2016-04-15","2016-04-15");
	cout << "Received " << myStocks.size() << " stocks." << endl;
	cout << "Should be 1 stock" << endl;

	vector<Stock*> myStocks2;
	myStocks2 = A1.getData("GOOG","2010-05-20","2015-08-10");
	cout << "Received " << myStocks2.size() << " stocks." << endl;
	cout << "should be many stocks" << endl;
	cout << myStocks[0]->getVolume() << endl;
	A1.destroyData(myStocks);
	cout << "myStocks now has size " << myStocks.size() << endl;
	A1.destroyData(myStocks2);
	cout << "myStocks2 now has size " << myStocks2.size() << endl;
*/
	
}
