#!/bin/bash
checkroot(){
    if [ $(id -u) != 0 ]
    then
	echo "This script must be run as root."
	exit 1
    fi
}
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
    HDIR=`eval echo "~${SUDO_USER:-${USER}}"`
    if [ ! -d $HDIR/.config/jobber ]
    then
	mkdir $HDIR/.config/jobber
	less /var/db/postgres/data12/postgresql.conf | grep "port = " > $HDIR/.config/jobber/jobber.conf
	chown -R `echo ${SUDO_USER:-${USER}}`:`echo ${SUDO_USER:-${USER}}` $HDIR/.config/jobber
    fi
fi
