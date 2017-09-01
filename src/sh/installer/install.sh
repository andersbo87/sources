#!/bin/sh
deps () {
    file1=$(/usr/bin/make -C /usr/ports/$1 all-depends-list)
    /usr/bin/make -C /usr/ports/$1 config-recursive
    file2=$(/usr/bin/make -C /usr/ports/$1 all-depends-list)
    if [ "$file1" != "$file2" ]
    then
	echo "Difference in the dependency list for /usr/ports/$1. Re-running /usr/bin/make -C /usr/ports/$1 config-recursive"
	deps $1
    else
	echo "Configure complete. Fetching required distfiles."
    fi
}

if [ $(/usr/bin/id -u) != 0 ]
then
    echo "Must be run as root."
    exit 1
fi

if [ $# != 1 ]
then
    echo "One paramter must be typed"
    exit 1
fi
dir=$1
if [ $1 == "." ]
then
    dir=`/bin/pwd | /usr/bin/cut -c 12-`
fi

/usr/bin/make -C /usr/ports/$dir config-conditional
deps $dir

/usr/bin/make -C /usr/ports/$dir checksum-recursive
for file in `/usr/bin/make -C /usr/ports/$dir all-depends-list | /usr/bin/cut -c 12-`
do
    #portversion=`/usr/sbin/pkg search -oef $file | /usr/bin/grep Version | /usr/bin/cut -c 18-`
    #portname=`/usr/sbin/pkg search -oef $file | /usr/bin/grep Name | /usr/bin/cut -c 18-`
    #/usr/sbin/pkg info $portname > /dev/null 2>&1
    #portname=`/usr/sbin/pkg info -f $file | /usr/bin/grep Name | /usr/bin/cut -c 18- 2>/dev/null`
    /usr/sbin/pkg info $file > /dev/null 2>&1
    res=$?
    if [ $res -ne 0 ]
    then
	echo "===>>> $file does not seem to be installed."
	sleep 4
	/usr/bin/make -C /usr/ports/$file package install clean
	newres=$?
	if [ $newres -ne 0 ]
	then
	    exit $newres
	fi
    else
	portname=`/usr/sbin/pkg info -f $file | /usr/bin/grep "Name           : " | /usr/bin/cut -c 18- 2>/dev/null`
	portversion=`/usr/sbin/pkg info -f $file | /usr/bin/grep "Version        : " | /usr/bin/cut -c 18- 2>/dev/null`
	if [ ! -e "/usr/ports/packages/All/$portname-$portversion.txz" ]
	then
	    echo "===>>> /usr/ports/packages/All/$portname-$portversion.txz does not seem to exist."
	    sleep 4
	    make -C /usr/ports/$file package clean
	    newres=$?
	    if [ $newres -ne 0 ]
	    then
		exit $newres
	    fi
	fi
    fi
done
/usr/sbin/pkg info $dir > /dev/null 2>&1
res2=$?
if [ $res -ne 0 ]
then
    /usr/bin/make -C /usr/ports/$dir package install clean clean-depends
else
    portname=`/usr/sbin/pkg info -f $dir | /usr/bin/grep "Name           : " | /usr/bin/cut -c 18- 2>/dev/null`
    portversion=`/usr/sbin/pkg info -f $dir | /usr/bin/grep "Version        : " | /usr/bin/cut -c 18- 2>/dev/null`
    if [ ! -e "/usr/ports/packages/All/$portname-$portversion.txz" ]
    then
	/usr/bin/make -C /usr/ports/$dir package clean clean-depends
    else
	echo "/usr/ports/packages/All/$portname-$portversion.txz already exists."
	/usr/bin/make -C /usr/ports/$dir clean clean-depends
    fi
fi
