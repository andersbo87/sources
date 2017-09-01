#!/bin/sh

curl_exists=`which curl`
# This little shell script returns the computer's public IP address.
if [ "$curl_exists" != "" ]
then
    ipaddress=`curl -s checkip.dyndns.org|cut -d ":" -f2|cut -d "<" -f1`
else
    cd $HOME
    ipaddress=`fetch -q http://checkip.dyndns.org && less checkip.dyndns.org | cut -d ":" -f2|cut -d "<" -f1`
    #rm checkip.dyndns.org
fi
local_ip=`netstat -n | awk '{print $4}' | grep -o "[0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | grep -v "127.0.0.1" | sort -u`
echo "Public IP address : $ipaddress"
echo "Private IP address: $local_ip"
