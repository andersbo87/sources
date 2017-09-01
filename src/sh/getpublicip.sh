#!/bin/sh

ipaddress=`curl -s checkip.dyndns.org|cut -d ":" -f2|cut -d "<" -f1`
if [ "$ipaddress" == "" ]
then
    echo "You were logged in `date` on `tty`."
    echo "You are not connected to the Internet."
else
    echo "You were logged in `date` from IP $ipaddress on `tty`."
fi
