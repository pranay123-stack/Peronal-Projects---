#!/bin/sh

while read line; do
	url="real-chart.finance.yahoo.com/table.csv?s=$line&a=07&b=19&c=2004&d=03&e=18&f=2016&g=d&ignore=.csv"
	curl -o "./historical_data/$line" "$url"
done < "tickers2.txt" 
