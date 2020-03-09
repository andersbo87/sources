#!/bin/bash
checkroot(){
    if [ $(id -u) != 0 ]
    then
	echo "This script must be run as root."
	exit 1
    fi
}

# Let's fetch the home directory of the user running the command using "sudo".
# This does not work if run using the "su" command.
HDIR=`eval echo "~${SUDO_USER:-${USER}}"`
if [ -e "/usr/lib/x86_64-linux-gnu/qt5/bin/qmake" ]
then
    # /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -o ../Makefile ../jobber.pro -spec linux-clang
    /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -o ../Makefile ../jobber.pro
else
    echo "Please install QT5 before running this script."
    exit 1
fi

if [ "$1" == "uninstall" ]
then
    checkroot
    make -C ../ uninstall
    rm ../Makefile
    rm -rf $HDIR/.config/jobber/
elif [ "$1" == "compile" ]
then
    make -C ../
    rm ../Makefile
elif [ "$1" == "clean" ]
then
    make -C ../ clean
    rm ../Makefile
else
    make -C ../
    make -C ../ install clean
    rm -f install ../Makefile
    
    # Create a settings file which stores information about
    # which port to connect to. (Normally it's 5432).
    # In the process, let's check which version is installed.
    # If multiple versions are installed, let's use the newest one.
    mkdir -p $HDIR/.config/jobber
    if [ -d /etc/postresql/13/ ]
    then
	less /etc/postgresql/13/main/postgresql.conf | grep "port = " > $HDIR/.config/jobber/jobber.conf
    elif [ -d /etc/postgresql/12/ ]
    then
	less /etc/postgresql/12/main/postgresql.conf | grep "port = " > $HDIR/.config/jobber/jobber.conf
    elif [ -d /etc/postgresql/11/ ]
    then
	less /etc/postgresql/11/main/postgresql.conf | grep "port = " > $HDIR/.config/jobber/jobber.conf
    elif [ -d /etc/postgresql/10/ ]
    then
	    less /etc/postgresql/10/main/postgresql.conf | grep "port = " > $HDIR/.config/jobber/jobber.conf
    fi
    chown -R `echo ${SUDO_USER:-${USER}}` $HDIR/.config/jobber
fi
