#!/bin/bash

xboard=`which xboard`
stockfish=`which stockfish`
polyglot=`which polyglot`
aptget=`which apt-get`
if [ "$xboard" == "" ]
then
    echo "xboard does not seem to be installed."
    if [ "$aptget" != "" ]
    then
	sudo apt-get install xboard
    else
	echo "Please install xboard"
    fi
fi
if [ "$polyglot" == "" ]
then
    echo "Required program polyglot does not seem to be installed."
    if [ "$aptget" != "" ]
    then
	sudo apt-get install polyglot
    else
	echo "Please install polyglot"
    fi
fi
if [ "$stockfish" == "" ]
then
    echo "stockfish does not seem to be installed."
    if [ "$aptget" != "" ]
    then
	sudo apt-get install stockfish
    else
	echo "Please install stockfish"
    fi
fi
$xboard -fUCI -fcp $stockfish -sUCI -scp $stockfish
