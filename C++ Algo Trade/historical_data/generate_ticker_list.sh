#!/bin/sh

for file in ./historical_data_csv/*;do
	echo "$file" | cut -d "/" -f 3 >> "tickers.txt"
done
