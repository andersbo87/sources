#!/bin/sh

removeOld(){
    /usr/bin/printf "\033[1mRemoving old packages from /usr/ports/packages/old/.\033[0m\n"
    rm /usr/ports/packages/old/*
}

if [ "$1" == "removeOld" ]
then
   removeOld
else
    for list in `/usr/sbin/pkg version | /usr/bin/grep "<"`
    do
	if [ "$list" != "<" ]
	then
	    p=`/usr/sbin/pkg info $list | /usr/bin/grep Origin | /usr/bin/cut -c 18-`
	    echo $p
	fi
    done
    
    for oldinstall in `/usr/sbin/pkg version | /usr/bin/grep "<"`
    do
	if [ "$oldinstall" != "<" ]
	then
            i=$(($i+1))
            port=`/usr/sbin/pkg info $oldinstall | /usr/bin/grep Origin | /usr/bin/cut -c 18-`
            oldversion=`/usr/sbin/pkg info $oldinstall | /usr/bin/head -1`
            name=`/usr/sbin/pkg info $oldinstall | /usr/bin/grep Name | /usr/bin/cut -c 18-`
	    if [ -e /usr/ports/packages/All/$oldversion.txz ]
	    then
		/usr/bin/printf "\033[1mMoving old package from /usr/ports/packages/All/$oldversion.txz to /usr/ports/packages/old/$oldversion.txz\033[0m\n"
		/bin/mv /usr/ports/packages/All/$oldversion.txz /usr/ports/packages/old/
	    else
		/usr/bin/printf "\033[1m$oldversion.txz already moved to /usr/ports/packages/old/$oldversion.txz.\033[0m\n"
	    fi
	fi
    done
fi


