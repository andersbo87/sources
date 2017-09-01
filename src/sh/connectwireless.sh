#!/bin/sh

# Sjekke om brukeren er rotbruker
if [ $(id -u) -ne 0 ]
then
    echo "This script must be run as root."
    exit 1
fi

# Dette skriptet skal koble en D-Link USB wifi-enhet på nett,
# og kan kjøres når systemet av en eller annen merkelig grunn ikke kobler
# til nettet automatisk gjennom denne enheten.
ifconfig wlan0 create wlandev run0
/etc/rc.d/netif restart # Forutsetter at wlans_run0="wlan0" er skrevet i /etc/rc.conf og at /etc/wpa_supplicant.conf inneholder nødvendig info for å koble til det trådløse nettet.
