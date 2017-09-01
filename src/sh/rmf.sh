#!/bin/sh

if [ -d $1 ]
then
    echo "Dette er en mappe"
    printf "Do you really want to remove the folder named $1?(y,n) "
    read answer
    if [ "$answer" == "y" -o "$answer" == "Y" ]
    then
	/bin/rm -rfv $1
    else
	exit 0
    fi
else
    /bin/rm -ri $*
fi