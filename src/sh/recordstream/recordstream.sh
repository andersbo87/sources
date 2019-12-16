#!/bin/sh

# Et skallprogram som bruker kommandoen livestreamer til å ta opp en sending fra Twitch.
# Tenkt syntaks:
# recordstream bruker kvalitet
# Programmet benytter VLC som spiller, og har en file-cache på 1 sekund og
# en nettverkscache på 4 sekunder.

# Sjekke om livestreamer eksisterer:
ls_exists=`which livestreamer`
sl_exists=`which streamlink`
#if [ "$ls_exists" = "" ]
#then
#    echo "Please install livestreamer."
#    exit 1
#fi

echo $#

slink()
{
    echo "Parameters: $@"
    echo "Parameter1: $1"
    if [ "$#" -lt 2 ]
    then
	echo "Please provide at least username and video quality."
	exit 1
    elif [ "$#" -eq 2 ]
    then
	# Sjekke om VLC eksisterer
	vlc_exists=`which vlc`
	if [ "$vlc_exists" = "" ]
	then
	    echo "Please install VLC."
	    exit 1
	else
	    for substr in "twitch"; do
		if [ -z "${1##*$substr*}" ]
		then
		    #streamlink --player "/usr/local/bin/vlc --file-caching 1000 --network-caching 4000" $1 $2
		    streamlink --player "$vlc_exists --file-caching 1000 --network-caching 4000" $1 $2
		else
		    streamlink --player "$vlc_exists --file-caching 1000 --network-caching 4000" https://www.twitch.tv/$1 $2
		fi
	    done
	fi
    elif [ "$#" -eq "3" ]
    then
	ext=`echo ${3} | cut -d"." -f2`
	filename=`echo ${3} | cut -d"." -f1`
	for substr in "twitch"; do
	    if [ -z "${1##*$substr*}" ]
	    then
		if [ -e "$3" ]
		then
		    echo "executing livestreamer $1 $2"
		    echo "$3 already exits. Writing to $filename-$(date +%d.%m.%Y_%H.%M.%S).$ext instead."
		    streamlink $1 $2 -o "$filename-$(date +%d.%m.%Y_%H.%M.%S).$ext"
		else
		    streamlink $1 $2 -o $3
		fi
	    else
		if [ -e "$3" ]
		then
		    echo "executing livestreamer https://www.twitch.tv/$1 $2"
		    echo "$3 already exits. Writing to $filename-$(date +%d.%m.%Y_%H.%M.%S).$ext instead."
		    streamlink https://www.twitch.tv/$1 $2 -o "$filename-$(date +%d.%m.%Y_%H.%M.%S).$ext"
		else
		    streamlink https://www.twitch.tv/$1 $2 -o $3
		fi
	    fi
	done
    elif [ "$#" -gt "3" ]
    then
	echo "$0 does not accept more than 3 arguments."
	exit 1
    fi
}

lstream() {
    if [ "$#" -lt 2 ]
    then
	echo "Please provide at least username and video quality."
	exit 1
    elif [ "$#" -eq 2 ]
    then
	# Sjekke om VLC eksisterer
	vlc_exists=`which vlc`
	if [ "$vlc_exists" = "" ]
	then
	    echo "Please install VLC."
	    exit 1
	else
	    for substr in "twitch"; do
		if [ -z "${1##*$substr*}" ]
		then
		    livestreamer --player "$vlc_exists --file-caching 1000 --network-caching 4000" $1 $2
		else
		    livestreamer --player "$vlc_exists --file-caching 1000 --network-caching 4000" https://www.twitch.tv/$1 $2
		fi
	    done
	fi
    elif [ "$#" -eq "3" ]
    then
	ext=`echo ${3} | cut -d"." -f2`
	filename=`echo ${3} | cut -d"." -f1`
	for substr in "twitch"; do
	    if [ -z "${1##*$substr*}" ]
	    then
		if [ -e "$3" ]
		then
		    echo "executing livestreamer $1 $2"
		    echo "$3 already exits. Writing to $filename-$(date +%d.%m.%Y_%H.%M.%S).$ext instead."
		    livestreamer $1 $2 -o "$filename-$(date +%d.%m.%Y_%H.%M.%S).$ext"
		else
		    livestreamer $1 $2 -o $3
		fi
	    else
		if [ -e "$3" ]
		then
		    echo "executing livestreamer https://www.twitch.tv/$1 $2"
		    echo "$3 already exits. Writing to $filename-$(date +%d.%m.%Y_%H.%M.%S).$ext instead."
		    livestreamer https://www.twitch.tv/$1 $2 -o "$filename-$(date +%d.%m.%Y_%H.%M.%S).$ext"
		else
		    livestreamer https://www.twitch.tv/$1 $2 -o $3
		fi
	    fi
	done
    elif [ "$#" -gt "3" ]
    then
	echo "$0 does not accept more than 3 arguments."
	exit 1
    fi
}

askuser()
{
    # ask the user which tool to use.
    printf "Please type ls for livestreamer or sl for streamlink: "
    while read ans; do
	if [ "$ans" = "ls" ]
	then
	    lstream $1 $2 $3
	elif [ "$ans" = "sl" ]
	then
	    slink $1 $2 $3
	else
	    askuser
	fi
	exit 0
    done
}    

if [ "$ls_exists" != "" -a "$sl_exists" = "" ]
then
    lstream $1 $2 $3
    exit 0
elif [ "$sl_exists" != "" -a "$ls_exists" = "" ]
then
    slink $1 $2 $3
    exit 0
elif [ "$ls_exists" != "" -a "$sl_exists" != "" ]
then
    askuser $1 $2 $3
    exit 0
else
    echo "Please install either livestreamer or streamlink"
    exit 1
fi

