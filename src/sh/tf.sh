#!/bin/sh

if [ -r "$1" ]
then
    echo $1 er en eksisterende fil
    exit 0
else
    echo Skriv inn et filnavn
    read filnavn
    if [ -r $filnavn ]
    then
	echo $filnavn er en eksisterende fil
    else
	touch $filnavn
    fi
fi