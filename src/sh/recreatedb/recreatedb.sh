#!/bin/sh

# Skallprogram som fjerner og oppretter en tom database
# og som eventuelt legger inn nye data hva. en SQL-fil.

# La oss sjekke om "programmene" dropdb, createdb og psql eksisterer:
name=$0
echo $name
drdb=`which dropdb`
if [ "$drdb" = "" ]
then
    echo "Vennligst installer serverutgaven av en 'ny' PostgreSQL-versjon, f. eks. postgresql 9.3 eller 10"
    exit 1
fi
crdb=`which createdb`
if [ "$crdb" = "" ]
then
     echo "Vennligst installer serverutgaven av en 'ny' PostgreSQL-versjon, f. eks. postgresql 9.3 eller 10"
     exit 1
fi
pg=`which psql`
if [ "$pg" = "" ]
then
     echo "Vennligst installer serverutgaven av en 'ny' PostgreSQL-versjon, f. eks. postgresql 9.3 eller 10"
    exit 1
fi
if [ $# -lt 1 -o $# -gt 2 ]
then
    echo "bruk: $0 databasenavn"
    echo "      $0 databasenavn filnavn"
    exit 1
fi
$drdb $1
$crdb $1
if [ $# -eq 2 ]
then
    if [ -e $2 ]
    then
	$pg -d $1 -f $2
    else
	echo "Filen $2 finnes ikke."
    fi
fi
