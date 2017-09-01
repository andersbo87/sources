#!/bin/sh

# Copyright (c) 2013 Anders Bolt-Evensen
# All rights reserved.
# 
# Redistribution and use in source and binary forms, 
# with or without modification are permitted providing that the following
# conditions are met:
# 1) Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer
# 2) Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other other materials provided with this distribution
# 3) Neither the name Anders Bolt-Evensen nor the names of the contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ANDERS BOLT-EVENSEN BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVICED OF THE POSSIBILITY OF SUCH DAMAGE.

# 
# NOTE: IN THIS SCRIPT, WHERE MESSAGES ARE PRINTED IN COLORS, 
# I USE printf(1) INSTEAD OF echo(1), WHICH IS THE TOOL I NORMALLY
# WOULD USE. THIS IS BECAUSE OF COLOR COMPABILITY PROBLEMS WITH FreeBSD's 
# echo(1) UTILITY.
# 

# The first order of business is to make sure that this script is run by a user
# with the required privilegies. In other words, to make sure that only the
# root user can run this script.

trap_control_t()
{
    # This function is called when SIGINFO is received.
    # The SIGINFO signal is only available on BSD-based systems, such as 
    # Darwin (OS X), FreeBSD, NetBSD and OpenBSD.
    printf "\033[01;33mSIGINFO received: Updating ports on `uname`.\033[00m\n"
}

control_c()
{
    printf "\033]0;\007" #remove the custom title set by this script
    printf "\n\033[01;31mThe updating process has been stopped.\033[00m\n"
    rm -f $HOME/ports.txt
    exit 0
}

trap control_c SIGINT
main()
{
    if [ $(id -u) != "0" ]
    then
	printf "\033[00;31mMust be run as root.\033[00m\n"
	exit 1
    fi
    # The next order of business is the check which OS the user is using.
    # I intend to add support for the following operating systems:
    # *) Linux (apt-get)
    # *) Mac OS X (MacPorts, Homebrew, fink, pkgng)
    # *) FreeBSD (portsnap)
    # *) Solaris (pkg)
    # *) OpenBSD (pkgng)
    # *) NetBSD (pkgng)
    
    echo "---> Checking operating system."
    osname=`uname`
    echo "-> $osname"
    # Users of Darwin can set the verbose option,
    #so that MacPorts can print more verbose messages.
    if [ "$1" = "-v" ]
    then
	if [ "$osname" != "Darwin" ]
	then
	    printf "\033[00;31mOnly users of Darwin (Mac OS X) can use the -v (verbose) option.\033[00m\n"
	    exit 1
	fi
    # FreeBSD users can specify the -pm option to tell updateports to use
    # portmaster as tool used to update installed ports.
    elif [ "$1" = "-pm" ]
    then
	if [ "$osname" != "FreeBSD" ]
	then
	    printf "\033[00;31mOnly users of FreeBSD may use the -pm (portmaster) option.\033[00m\n"
	    exit 1
	else
	    # Check if Portmaster is installed
	    pm=`which portmaster`
	    if [ "$pm" == "" ]
	    then
		printf "\033[00;31mIf you want to use Portmaster to upgrade your ports, please install it from /usr/ports/ports-mgmt/portmaster.\033[00m\n"
		exit 2
	    fi
	fi
    elif [ "$1" = "-pkg" ]
    then
	if [ "$osname" != "FreeBSD" ]
	then
	    printf "\033[00;31mOnly users of FreeBSD may use the -pkg option.\033[00m\n"
	    exit 1
	fi
    # FreeBSD users can specify the -pu option to tell updateports to use
    # portupgrade as tool used to update installed ports.
    elif [ "$1" = "-pu" ]
    then
	if [ "$osname" != "FreeBSD" ]
	then
	    printf "\033[00;31mOnly users of FreeBSD may usethe -pu (portupgrade) option.\033[00m\n"
	    exit 1
	else
	    pu=`which portupgrade`
	    if [ "$pu" == "" ]
	    then
		printf "\033[00;31mIf you want to use Portupgrade to update your installed ports, please install it from /usr/ports/ports-mgmt/portupgrade.\033[00m\n"
		exit 2
	    fi
	fi
    else
	if [ "$1" != "-pkgsrc" ]
	then
	    if [ "$1" != "" ]
	    then
		printf "\033[00;31mYou've typed an illegal option, $1. Please see the manual page for usage info.\033[00m\n"
		exit 1
	    fi
	fi
    fi
    if [ $osname = "Linux"  ]
    then
	printf "\033[01;33m---> Updating ports on Linux.\033[00m\n"
	updateLinux
    elif [ $osname = "Darwin" ] # Darwin is the name of the BSD part of Mac OS X.
    then
	printf "\033[01;32m---> Updating ports on Darwin (Mac OS X).\033[00m\n"
	trap trap_control_t SIGINFO
	updateDarwin $1
    elif [ $osname = "FreeBSD" ]
    then
	printf "\033[01;32m---> Updating ports on FreeBSD.\033[00m\n"
	trap trap_control_t : xcSIGINFO
	updateFreeBSD $1
    elif [ $osname = "SunOS" ] # SunOS = Solaris.
    then
	printf "\033[01;32m---> Updating ports and base system SunOS (Solaris).\033[00m\n"
	updateSolaris $1
    elif [ $osname = "OpenBSD" ]
    then
	printf "\033[01;33m-> Upgrading via pkgsrc (OpenBSD).\033[00m\n"
	trap trap_control_t SIGINFO
	updatePkgsrc
    elif [ "$osname" = "NetBSD" ]
    then
	printf "\033[01;33m-> Upgrading via pkgsrc (NetBSD).\033[00m\n"
	trap trap_control_t SIGINFO
	updatePkgsrc
    else
	echo "Sorry, but your operating system, $osname, is unfortunately not supported by this script."
	echo "$0 is supposed to support the following operating systems:"
	printf "Linux\nDarwin (Mac OS X)\nFreeBSD\nSunOS (Solaris)\nOpenBSD\nNetBSD\n"
    fi
}

# On FreeBSD 9.1 and 10.0, a new ports managements tool, pkg, was added.
# This is done to simplify the updating and installation process of ports
# on FreeBSD. See pkg(8) manual page for more info.
updatePkgFreeBSD()
{
    echo "As a precaution, until pkg is fully supported (with a remote repository) on FreeBSD, you might want to use the repository on PC-BSD which should work with FreeBSD. If you decide to do so, please modify the PACKAGESITE line on /usr/local/etc/pkg.conf (create the file if it does not exist, or copy /usr/local/etc/pkg.conf.sample if that file exists), so that the PACKAGESITE line looks like this: PACKAGESITE: ftp://fpt.pcbsd.org/pub/mirror/packages/9.1-RELEASE/amd64 (replase amd64 with your system architecture (i.e. i386)."
    pkg upgrade -fy
}

# Update ports via pkgsrc. pkgsrc is a ports system that can be found on many
# operating systems. However, in this script, initially, we'll only use
# this script when this script is run from either NetBSD or OpenBSD, or when
# the user uses the -pkgsrc option.

updatePkgsrc()
{
    printf "\033[01;32m---> Updating pkgsrc ports on $osname.\033[00m\n"
    res=0
    pkgin_exists=`which pkgin`
    if [ "$pkgin_exists" == "" ]
    then
	printf "Type the directory where pkgsrc is stored (i.e. /usr/pkgsrc): "
	read ans
	cd $ans
	export CVS_RSH=ssh
	cvs up -dP
        # Now, I'll check whether bmake (on OpenBSD) exists.
	bmakeexists=`which bmake`
	if [ "$bmakeexists" != "" ]
	then
	    printf "\033[01;32m-> Executing bmake update.\033[00m\n"
	    bmake update
	    res=$?
	    if [ "$res" == "0" ]
	    then
		printf "\033[01;32m-> Your pkgsrc ports should now be up-to-date. :)\033[00m\n"
	    else
		printf "\033[00;31m-> Something has gone wrong and the updating process has been stopped.\033[00m\n"
	    fi
	else
	    printf "\033[01;32m-> Assuming that 'standard' make can handle pkgsrc.\033[00m\n"
	    make update
	    res=$?
	    if [ "$res" == "0" ]
	    then
		printf "\033[01;32m-> Your pkgsrc ports should now be up-to-date. :)\033[00m\n"
	    else
		printf "\033[00;31m-> Something has gone wrong and the updating process has been stopped.\033[00m\n"
	    fi
	fi
    else
	pkgin -y update
	pkgin -y upgrade
	res=$?
	if [ "$res" == "0" ]
	then
	    printf "\033[01;32m-> Your pkgsrc ports should now be up-to-date. :)\033[00m\n"
	else
	    printf "\033[00;31m-> Something has gone wrong and the updating process has been stopped.\033[00m\n"
	fi
    fi
}

# Update ports on Solaris
updateSolaris()
{
    if [ "$1" == "-pkgsrc" ]
    then
	updatePkgsrc
    else
	# In fact, the pkg tool in Solaris is used to both install and upgrade
	# BOTH 3rd party ports AND the Solaris/SunOS base system.
	# In other words, running both of the commands below, updates both
	# SunOS/Solaris (i.e. from 11.0 to 11.1) as well as eventual installed
	# 3rd party ports.
	pkg install pkg:/package/pkg
	pkg update --accept
    fi
}

# Update ports on Linux
updateLinux()
{
    if [ "$1" == "-pkgsrc" ]
    then
	updatePkgsrc
    else	
	# Assuming apt-get will get the job done.
	apt-get update 
	apt-get dist-upgrade 
    fi
}

# A few of the supported OS'es have their own command line utility
# to update the base system. The following function will update
# Darwin and FreeBSD.
updateBaseSystem()
{
    #trap trap_control_t SIGINFO
    if [ ! -f $HOME/softupd.txt ]
    then
	touch $HOME/softupd.txt
    fi
    os=`uname`
    if [ "$os" == "Darwin" ]
    then
	printf "Would you like to execute softwareupdate(8) to update the Darwin base system as well as your installed ports? (Y/n) "
	read ans
	if [ "$ans" == "y" -o "$ans" == "Y" ]
	then
	    echo "Updating your base system by executing softwareupdate -l..."
	    # Run the software update process as a child so that the tee
	    # process can begin earlier (to speed up the entire process)...
	    /usr/sbin/softwareupdate -l &
	    /usr/sbin/softwareupdate -l | /usr/bin/tee -a $HOME/softupd.txt &>/dev/null
	    res=`grep -o "restart" softupd.txt`
	    res2=`grep -o "Software Update found the following new or updated software" $HOME/softupd.txt`
	    rm $HOME/softupd.txt
	    if [ "$res2" == "Software Update found the following new or updated software" ]
	    then
		echo "There are new updates available."
		if [ "$res" == "restart" ]
		then
		    echo "One or more updates require a computer restart. After updating ports, you should restart your computer."
		    sleep 10
		    if [ "$1" == "-v" ]
		    then
			/usr/sbin/softwareupdate -iav
		    else
			/usr/sbin/softwareupdate -ia
		    fi
		else
		    echo "Installing new software..."
		    if [ "$1" == "-v" ]
		    then
			/usr/sbin/softwareupdate -iav
		    else
			/usr/sbin/softwareupdate -ia
		    fi
		fi
	    else
		echo "There are no new software available."
	    fi
	elif [ "$ans" == "n" -o "$ans" == "N" ]
	then
	    echo "Going on as normal without updating your base system."
	elif [ "$ans" == "" ]
	then
	    echo "Updating your base system by executing softwareupdate -l..."
	    # Run the software update process as a child so that the tee
	    # process can begin earlier (to speed up the process)...
	    /usr/sbin/softwareupdate -l &
	    /usr/sbin/softwareupdate -l | /usr/bin/tee -a $HOME/softupd.txt &>/dev/null
	    res=`grep -o "restart" $HOME/softupd.txt`
	    res2=`grep -o "Software Update found the following new or updated software" $HOME/softupd.txt`
	    rm $HOME/softupd.txt
	    if [ "$res2" == "Software Update found the following new or updated software" ]
	    then
		echo "There are new updates available."
		if [ "$res" == "restart" ]
		then
		    echo "One or more updates require a computer restart. After updating ports, you should restart your computer."
		    sleep 10
		    if [ "$1" == "-v" ]
		    then
			/usr/sbin/softwareupdate -iav
		    else
			/usr/sbin/softwareupdate -ia
		    fi
		else
		    echo "Installing new software..."
		    if [ "$1" == "-v" ]
		    then
			/usr/sbin/softwareupdate -iav
		    else
			/usr/sbin/softwareupdate -ia
		    fi
		fi
	    else
		echo "There are no new software available."
	    fi
	else
	    echo "Please type either 'y' for yes or 'n' for no."
	    updateBaseSystem
	fi
    elif [ "$os" == "FreeBSD" ]
    then
	# When executing freebsd-update fetch, it is more convenient to
	# use the "more" pager than "less", because if there either are no
	# available updates or only a few of them, if the "less" utility
	# is used, the script stops intil the user presses 'q' on the keyboard.
	# By changing the pager from less to more,
	# I hope to avoid that problem.
	tmp=`uname -v`
	expVersion=`echo $tmp | cut -f1 -d"-"` 
	# freebsd-update is not supported on systems not running the STABLE or RELEASE branch 
	# (in other words, FreeBSD 11 which is in a highly experimental stage, is not supported by freebsd-update
	# and therefore it's not nessessary to run freebsd-update on FreeBSD 11 yet.)
	if [ "$expVersion" != "FreeBSD 11.0" ]
	then
	    OLDPAGER=$PAGER
	    PAGER=more
	    printf "Would you like to run freebsd-update(8) to update the FreeBSD base system as well as your installed ports? (Y/n) "
	    read ans
	    if [ "$ans" == "y" -o "$ans" == "Y" ]
	    then
		echo "Updating your base system by executing 'freebsd-update fetch'..."
		/usr/sbin/freebsd-update fetch install
	    elif [ "$ans" == "n" -o "$ans" == "N" ]
	    then
		echo "Going on as normal without updating your base system."
	    elif [ "$ans" == "" ]
	    then
		echo "Updating your base system by executing 'freebsd-update fetch install'..."
		/usr/sbin/freebsd-update fetch install
	    else
		echo "Please type 'y' for yes or 'n' for no."
		updateBaseSystem
	    fi
	    # Reset the pager:
	    PAGER=$OLDPAGER
	fi
    fi
}

# Update ports on Darwin
updateDarwin()
{
    updateBaseSystem $1
    macportscript=`which port`
    finkscript=`which fink`
    brewscript=`which brew`
    if [ "$1" == "-pkgsrc" ]
    then
	updatePkgsrc
    else
	if [ "$macportscript" == "" -a "$finkscript" == "" -a "$brewscript" == "" ]
	then
	    echo "Please install either MacPorts, Fink or HomeBrew and run this script again."
	    exit 1
	fi
	# From what I've read, Mac users are only recommended to use one
	# port system at a time, so therefore I do not assume that one computer
	# has more than one installed port system.
	if [ "$macportscript" != "" ]
	then
	    if [ "$1" == "-v" ]
	    then
		port -v selfupdate
	    else
		port selfupdate
	    fi
	    echo "-> Checking for out-of-date ports..."
	    updates=`port list outdated`
	    if [ "$updates" == "" ]
	    then
		# Echo the "Your MacPorts ar up-to-date" messge in green color:
		printf "\033[01;32m-> Your MacPorts are up-to-date.\033[00m\n"
	    else
		if [ ! -f $HOME/ports.txt ]
		then
		    touch $HOME/ports.txt
		fi
		printf "\033[01;32m--> The following ports will be updated:\033[00m\n"
		port list outdated &
		port list outdated | /usr/bin/tee -a $HOME/ports.txt &>/dev/null
		numberOfPorts=`port list outdated | wc -l`
		numberOfPorts=`echo $numberOfPorts | tr -d ' '`
		# Set the total number of ports to be updated as the shell title
		printf "\033]0;$numberOfPorts to be updated\007"
		printf "\033[01;32m--> Updating out-of-date ports.\033[00m\n"
		if [ "$1" == "-v" ]
		then
		    #port -v upgrade outdated
		    updatedPorts=1
		    while read line
		    do
			echo "Updating port $updatedPorts of $numberOfPorts."
			# Set Updating port N of X as the shell title
			printf "\033]0;Updating port $updatedPorts of $numberOfPorts\007"
			tmp=`echo $line | cut -f1 -d" "`
			port -vn upgrade $tmp
			tmpRes=$?
			if [ "$tmpRes" != "0" ]
			then
			    printf "\033[01;31mSomething went wrong and the update process has been stopped.\033[00m\n"
			else
			    if [ "$updatedPorts" -lt "$numberOfPorts" ]
			    then
				updatedPorts=`expr $updatedPorts + 1`
			    fi
			fi
		    done < $HOME/ports.txt
		    if [ "$updatedPorts" != "$numberOfPorts" ]
		    then
			printf "\033[01;31mOnly $updatedPorts of $numberOfPorts ports were installed.\nYou should either run this script again or run sudo port upgrade outdated.\033[00m\n"
		    else
			printf "\033[01;32m-> Your MacPorts are now up-to-date.\033[00m\n"
		    fi
		else
		    updatedPorts=1
		    while read line
		    do
			echo "Updating port $updatedPorts of $numberOfPorts."
			printf "\033]0;Updating port $updatedPorts of $numberOfPorts\007"
			tmp=`echo $line | cut -f1 -d" "`
			port -n upgrade $tmp
			tmpRes=$?
			if [ "$tmpRes" != "0" ]
			then
			    printf "\033[01;31mSomething went wrong and the update process has been stopped.\033[00m\n"
			else
			    if [ "$updatedPorts" -lt "$numberOfPorts" ]
			    then
				updatedPorts=`expr $updatedPorts + 1`
			    fi
			fi
		    done < $HOME/ports.txt
		    res=$?
		    if [ "$updatedPorts" != "$numberOfPorts" ]
		    then
			printf "\033[01;31mOnly $updatedPorts of $numberOfPorts ports were installed.\nYou should either run this script again or run sudo port upgrade outdated.\033[00m\n"
		    else
			printf "\033[01;32m-> Your MacPorts are now up-to-date.\033[00m\n"
		    fi
		fi
		rm -f $HOME/ports.txt
		printf "\033]0;\007"
	    fi
	elif [ "$finkscript" != "" ]
	then
	    echo "-> Updating via Fink."
	elif [ "$brewscript" != "" ]
	then
	    printf "\033[01;32m-> Updating via HomeBrew.\033[00m\n"
	    brew update
	    printf "\033[01;32m-> Now I'm listing eventual outdated ports.\033[00m\n"
	    brew outdated
	    askIfHomebrewListedOutdatedPorts
	    res=$?
	    if [ $res == "1" ]
	    then
		brew update
	    fi
	fi
    fi
}

askIfHomebrewListedOutdatedPorts()
{
    result=0
    printf "Are there any ports printed below 'Now listing outdated ports'? (y/n) "
    read ans
    if [ $ans == "Y" -o $ans == "y" ]
    then
        result=1
    elif [ $ans == "N" -o $ans == "n" ]
    then
        result=2
    else
	askIfHomebrewListedOutdatedPorts
    fi
    return $result
}

# Update ports on FreeBSD
updateFreeBSD(){
    updateBaseSystem
    var=$1
    if [ "$1" == "-pkgsrc" ]
    then
	updatePkgsrc
    elif [ "$1" == "-pkg" ]
    then
	updatePkgFreeBSD
    else
	printf "\033[01;32m-> About to update your installed ports on FreeBSD.\033[00m\n"
	portsnap fetch update
	echo "After running portsnap fetch update, it might be a good idea to read /usr/ports/UPDATING. This file contains important information about nessesary steps to update one or more ports."
	askToReadUPDATINGfile
	func=$?
	if [ "$func" == 1 ]
	then
	    less /usr/ports/UPDATING
	    func=0
	    askIfManualActionMustBeTaken $1
	    func=$?
	    if [ $func == 1 ]
	    then
		executeExtraNessesaryCommands $1
		printf "\033[01;32m-> Going on as normal.\033[00m\n"
		updatePortsOnFreeBSD $1
	    else
		printf "\033[01;32m-> Going on as normal.\033[00m\n"
		updatePortsOnFreeBSD $1
	    fi
	else
	    printf "\033[01;32m-> Going on as normal.\033[00m\n"
	    updatePortsOnFreeBSD $1
	fi
    fi
}
# Sometimes, as detailed in /usr/ports/UPDATING, manual action might have to
# be taken to maintin compability and prevent other issues that might arise
# when updating installed software. 
# If such an action is nessesary, the following function is meant to let 
# the user type in and execute the required command. 
executeExtraNessesaryCommands()
{
    res=0
    echo "Type the command that has to be executed before continuing."
    echo "Only one command can be typed at a time."
    printf "Command to be executed: "
    read command
    $command
    func1=0
    func2=0
    askToReadUPDATINGfile $1
    func1=$?
    if [ $func1 == 1 ]
    then
	less /usr/ports/UPDATING
	reAskIfActionMustBeTaken $1
	func2=$?
	if [ $func2 == 1 ]
	then
	    executeExtraNessesaryCommands
	fi
    else
	func2=0
	reAskIfActionMustBeTaken $1
	func2=$?
	if [ $func2 == 1 ]
	then
	    executeExtraNessesaryCommands
	fi
    fi
    return $res
}

#The following function is meant to be used if there are more than one
#command nessesary to be run before the update can continue.
reAskIfActionMustBeTaken()
{
    res=0
    printf "Do you need to execute any more commands before continuing? (y/n) "
    read ans
    if [ "$ans" == "Y" -o "$ans" == "y" ]
    then
	res=1
    elif [ "$ans" == "N" -o "$ans" == "n" ]
    then
	res=2
    else
	echo "Please answer y (yes) or n (no)."
	reAskIfActionMustBeTaken
    fi
    return $res
}
askPortUtility()
{
    res=0
    printf "Which port utility would you like to use?\n"
    printf "Type 'pm' for portmaster or 'pu' for portupgrade: "
    read ans
    if [ $ans == "pm" ]
    then
	res=1
    elif [ $ans == "pu" ]
    then
	res=2
    else
	askPortUtility
    fi
    return $res
}

updatePortsOnFreeBSD()
{
    pm="null"
    pu="null"
    res=0
    if [ -f /usr/local/sbin/portmaster ]
    then
	pm="portmaster"
    fi
    if [ -f /usr/local/sbin/portupgrade ]
    then
	pu="portupgrade"
    fi
    if [ -z "$1" ]
    then
	if [ "$pm" == "portmaster" -a "$pu" == "portupgrade" ]
	then
	    askPortUtility
	    result=$?
	    if [ $result == 1 ]
	    then
		printf "\033[01;32m-> Checking for updates using Portmaster.\033[00m\n"
		/usr/local/sbin/portmaster -Da
		res=$?
		getReturnedValueOfFreeBSDPortUpgrade $res
	    elif [ $result == 2 ]
	    then
		printf "\033[01;32m-> Checking for updates using Portupgrade.\033[00m\n"
		/usr/local/sbin/portupgrade -a
		res=$?
		getReturnedValueOfFreeBSDPortUpgrade $res
	    fi
	elif [ $pm == "portmaster" -a $pu  == "null" ]
	then
	    printf "\033[01;32m-> Checking for updates using Portmaster (as a child).\033[00m\n"
	    /usr/local/sbin/portmaster -Da &
	    res=$?
	    getReturnedValueOfFreeBSDPortUpgrade $res
	elif [ $pm == "null" -a $pu == "portupgrade" ]
	then
	    printf "\033[01;32m-> Checking for updates using Portupgrade.\033[00m\n"
	    /usr/local/sbin/portupgrade -a
	    res=$?
	    getReturnedValueOfFreeBSDPortUpgrade $res
	elif [ $pm == "null" -a $pu == "null" ]
	then
	    printf "\033[01;31mNeither Portmaster nor Portupgrade seems to be installed. Please install either or both of those utilities and run this script again.\033[00m\n"
	    exit 1
	fi
    elif [ "$1" == "-pm" ]
    then
	printf "\033[01;32m-> Checking for updated ports using Portmaster (as a child).\033[00m\n"
	/usr/local/sbin/portmaster -Da
	res=$?
	getReturnedValueOfFreeBSDPortUpgrade $res
    elif [ "$1" == "-pu" ]
    then
	printf "\033[01;32m-> Checking for updated ports using Portupgrade.\033[00m\n"
	/usr/local/sbin/portupgrade -a
	res=$?
	getReturnedValueOfFreeBSDPortUpgrade $res
    fi
}
getReturnedValueOfFreeBSDPortUpgrade()
{
    if [ $1 -eq 0 ]
    then
	printf "\033[01;32mYour installed ports are now up-to-date.\033[00m\n"
    else
	printf "\033[00;31m\nSomething has gone wrong, and the updating process has been stopped.\033[00m\n"
    fi
}

askIfManualActionMustBeTaken()
{
    ret=0
    printf "Do you need to take some manual action? (y/n) "
    read ans
    if [ "$ans" == "Y" -o "$ans" == "y" ]
    then
	ret=1
    elif [ "$ans" == "N" -o "$ans" == "n" ]
    then
	ret=2
    else
	echo "Please answer y for yes or n for no."
	askIfManualActionMustBeTaken
    fi
    return $ret
}

askToReadUPDATINGfile()
{
    ret=0
    printf "Would you like to read /usr/ports/UPDATING?(y/n) "
    read ans
    if [ "$ans" == "Y" -o "$ans" == "y" ]
    then
	ret=1
    elif [ "$ans" == "N" -o "$ans" == "n" ]
    then
	#echo "Do something more..."
	ret=2
    else
	echo "Please answer y for yes or n for no."
	askToReadUPDATINGfile
    fi
    return $ret
}
# Calling the main function:
main $1

