#!/bin/sh

if [ $# -ne 1 ]
then
    echo "$0: usage $0 filnavn"
    exit 1
fi

if [ -r $1 ]
then
    echo "$0: $1: lesbar fil"
else
    echo "$0: $1: ikke lesbar fil"
fi