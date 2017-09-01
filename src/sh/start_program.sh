#!/bin/sh

if [ $# -ne 1 ]
then
    echo "$0: usage: $0 application"
    exit 1
fi

echo "Starter $1 om 5 sekunder"
sleep 5
if $1 
then 
    echo "Hurra, nå er vi ferdig!"
else
    echo "Darn. Noe gikk galt"
fi