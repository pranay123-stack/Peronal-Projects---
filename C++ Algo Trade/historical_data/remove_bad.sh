#!/bin/sh

while read line; do
	git rm "historical_data_csv/"$line""
done < "remove.txt" 
