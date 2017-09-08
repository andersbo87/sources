#!/bin/sh

# Sjekker hvilken kompilator vi skal bruke for å kompilere programmene:
_cpp=`which c++`
_gpp=`which g++`

if [ "$_cpp" != "" ]
then
    $_cpp bst.cpp -o bst
    $_cpp RBTre.cpp -o rbtre
elif [ "$_gpp" != "" ]
then
    $_gpp bst.cpp -o bst
    $_gpp RBTre.cpp -o rbtre
else
    echo "Det ser ikke ut til at du har installert GCC eller noen andre C++-kompatible kompilatorer (verken C++ eller G++ ble funnet)."
    exit 1
fi
echo "Programmene som skal løse oppgave 3 skal nå være opprettet. Syntaksen for å kjøre programmet er bst fil1 [fil2] og rbtre fil1 [fil2]."
