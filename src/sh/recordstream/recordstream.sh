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

slink()
{
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
	    streamlink --player "/usr/local/bin/vlc --file-caching 1000 --network-caching 4000" https://www.twitch.tv/$1 $2
	fi
    elif [ "$#" -eq "3" ]
    then
	ext=`echo ${3} | cut -d"." -f2`
	filename=`echo ${3} | cut -d"." -f1`
	if [ -e "$3" ]
	then
	    echo "executing livestreamer https://www.twitch.tv/$1 $2"
	    echo "$3 already exits. Writing to $filename-$(date +%d.%m.%Y_%H.%M.%S).$ext instead."
	    streamlink https://www.twitch.tv/$1 $2 -o "$filename-$(date +%d.%m.%Y_%H.%M.%S).$ext"
	else
	    streamlink https://www.twitch.tv/$1 $2 -o $3
	fi
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
	    livestreamer --player "/usr/local/bin/vlc --file-caching 1000 --network-caching 4000" https://www.twitch.tv/$1 $2
	fi
    elif [ "$#" -eq "3" ]
    then
	ext=`echo ${3} | cut -d"." -f2`
	filename=`echo ${3} | cut -d"." -f1`
	if [ -e "$3" ]
	then
	    echo "executing livestreamer https://www.twitch.tv/$1 $2"
	    echo "$3 already exits. Writing to $filename-$(date +%d.%m.%Y_%H.%M.%S).$ext instead."
	    livestreamer https://www.twitch.tv/$1 $2 -o "$filename-$(date +%d.%m.%Y_%H.%M.%S).$ext"
	else
	    livestreamer https://www.twitch.tv/$1 $2 -o $3
	fi
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
	    lstream
	elif [ "$ans" = "sl" ]
	then
	    slink
	else
	    askuser
	fi
    done
}    

if [ "$ls_exists" != "" -a "$sl_exists" == "" ]
then
    lstream
elif [ "$sl_exists" != "" -a "$ls_exists" = "" ]
then
    slink
elif [ "$ls_exists" != "" -a "$sl_exists" != "" ]
then
    askuser
else
    echo "Please install either livestreamer or streamlink"
    exit 1
fi

