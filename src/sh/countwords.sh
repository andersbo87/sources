#!/bin/sh
if [ -r $1 ]
then
    if [[ $2 = [0-9]* ]]
    then
	tr -cs a-zA-Z '\n' < $1 | tr A-Z a-z | sort | uniq -c | sort -nr | head -$2
    else
	echo $2 er ikke et tall
    fi
else
    echo Filen $1 finnes ikke
fi