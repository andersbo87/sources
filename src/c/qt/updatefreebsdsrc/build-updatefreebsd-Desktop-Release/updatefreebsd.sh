#!/bin/sh

# Checking operating system
osname=`uname`
if [ "$osname" != "FreeBSD" ]; then
    echo "The tool updatefreebsd is only supposed to be run on FreeBSD."
    exit 1
fi

gksu=`which gksu`
if [ "$gksu" == "" -o "$gksu" == "gksu: Command not found" ]
then
    # Sjekke om vi er root eller ikke.
    if [ "$(id -u)" == "0" ]
    then
	# Installerer gksu på en elller annen måte.
	if [ -d "/usr/ports" ];
	then
	    portmaster=`which portmaster`
	    if [ "$portmaster" == "" -o "$portmaster" == "portmaster: Command not found" ]
	    then
		echo "Portmaster is not installed."
		portupgrade=`which portupgrade`
		if [ "$portupgrade" == "" -o "$portupgrade" == "portupgrade: Command not found" ]
		then
		    echo "Portupgrade is not installed."
		    # Let's then fall back to the regular make:
		    make -C /usr/ports/sysutils/gksu install clean
		else
		    # Using portinstall, a port of portupgrade (ports-mgmt/portupgrade)
		    /usr/local/sbin/portinstall gksu
		fi
	    else
		# Using portmaster (ports-mgmt/portmaster)
		/usr/local/sbin/portmaster -D sysutils/gksu
	    fi
	else
	    pkg install gksu
	fi
    else
	/usr/local/bin/zenity --error --text="updatefreebsd må kjøres som rotbruker. Som ledd i dette, må programmet gksu (som lar deg kjøre et grafisk program som rot) installeres. Vennligst åpne opp et terminalvindu og skriv 'sudo updatefreebsd'" --title "Oppdater FreeBSD"
	exit 1
    fi
fi
$gksu updatefreebsdgui
