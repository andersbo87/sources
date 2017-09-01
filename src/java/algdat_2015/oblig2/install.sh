#!/bin/sh

java=`which java`
javac=`which javac`
osname=`uname -a`
sudo=`which sudo`
if [ "$java" == "" ]
then
    if [ "$osname" == "Linux" ]
    then
	aptget=`which apt-get`
	if [ $sudo == "" ]
	then
	    echo "Please log in as root and run this script again."
	    exit 1
	fi
	if [ $aptget == "" ]
	then
	    echo "You do not seem to have Java installed. Please install Java using your favorite package manager (if possible)."
	    exit 1
	else
	    $sudo $aptget install openjdk-7-jdk
	fi
    elif [ $osname == "FreeBSD" ]
    then
	if [ $sudo == "" ]
	then
	    echo "Please log in as root and run this script again."
	    exit 1
	fi
	pkg=`which pkg`
	if [ $pkg != "" ]
	then
	    $pkg install openjdk8
	else
	    if [ -d "/usr/ports" ]
	    then
		sudo portsnap fetch update
		sudo make -C /usr/ports/java/openjdk8 install clean
	    else
		sudo portsnap fetch extract
		sudo make -C /usr/ports/java/openjdk8 install clean
	    fi
	fi
    else
	echo "Java does not seem to be installed. Please install Java manually and run this script again."
    fi
else
    # I Solaris returneres no $program in $PATH hvis det etterspurte programmet
    # ikke er installert.
    if [[ $java == no* ]] 
    then
	sudo pkg install developer/java/openjdk8
    fi
fi
if [ "$javac" == "" ]
then
    if [ "$osname" == "Linux" ]
    then
	aptget=`which apt-get`
	if [ "$sudo" == "" ]
	then
	    echo "Please log in as root and run this script again."
	    exit 1
	fi
	if [ "$aptget" == "" ]
	then
	    echo "You do not seem to have Java installed. Please install Java JDK using your favorite package manager (if possible)."
	    exit 1
	else
	    $sudo $aptget install openjdk-7-jdk
	fi
    elif [ "$osname" == "FreeBSD" ]
    then
	if [ "$sudo" == "" ]
	then
	    echo "Please log in as root and run this script again."
	    exit 1
	fi
	pkg=`which pkg`
	if [ "$pkg" != "" ]
	then
	    sudo $pkg install openjdk8
	else
	    if [ -d "/usr/ports" ]
	    then
		sudo portsnap fetch update
		sudo make -C /usr/ports/java/openjdk8 install clean
	    else
		sudo portsnap fetch extract
		sudo make -C /usr/ports/java/openjdk8 install clean
	    fi
	fi
    else
	echo "Java does not seem to be installed. Please install Java JDK manually and run this script again."
    fi
else
    if [[ $javac == no* ]]
    then
	sudo pkg install developer/java/openjdk8
    fi
    $javac quicksort.java
    $javac randomizeQuicksort.java
    $javac radixSort.java
    echo "Compilation of source files should now be complete."
fi
