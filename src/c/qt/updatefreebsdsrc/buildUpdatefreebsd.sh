#!/bin/sh
qmake=`which qmake-qt4`
gmake=`which gmake`
make=`which make`
if [ $qmake == "" ]
then
    echo "Please install qmake-qt4."
    exit 1
fi
$qmake updatefreebsd/updatefreebsd.pro -o Makefile
printf "install:   FORCE
       mkdir -p /usr/local/sbin/
       install -o root -g wheel -m 555 updatefreebsd.sh /usr/local/sbin/updatefreebsd
       install -o root -g wheel -m 555 updatefreebsdgui /usr/local/sbin/updatefreebsdgui
       install -o root -g wheel -m 644 updatefreebsd.desktop /usr/local/share/applications/updatefreebsd.desktop
       install -o root -g wheel -m 644 freebsd.png /usr/local/share/pixmaps/freebsd.png

uninstall:   FORCE
	rm /usr/local/sbin/updatefreebsd
	rm /usr/local/sbin/updatefreebsdgui
	rm /usr/local/share/pixmaps/freebsd.png
	rm /usr/local/share/applications/updatefreebsd.desktop
deinstall: FORCE
	rm /usr/local/sbin/updatefreebsd
	rm /usr/local/sbin/updatefreebsdgui
	rm /usr/local/share/pixmaps/freebsd.png
	rm /usr/local/share/applications/updatefreebsd.desktop" >> Makefile
if [ $gmake != "" ]
then
    $gmake install clean
else
    $make install clean
fi
