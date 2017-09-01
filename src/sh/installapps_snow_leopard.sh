#!/bin/sh
#sjekke om brukeren er rotbruker
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

echo "Dette skriptet installerer programmer som krever at du starter restarter datamaskinen. Vil du installere dette programmet (j,n)?"
read svar
installall=0
if [ "$svar" = "j" -o "$svar" = "J" ]
then
    installall=1
elif [ "$svar" = "n" -o "$svar" = "N" ]
then
    installall=0
else
    echo Vennligst svar med j eller n
    exit 1
fi
echo $installall
#"aktiverer" at-kommandoen
launchctl load -w /System/Library/LaunchDaemons/com.apple.atrun.plist
#echo "Viser skjulte filer og mapper"
#chflags -R nohidden /
echo "\"monterer\" bildefilene som inneholder programmene som skal installeres"
echo "\"monterer\" AppCleaner"
hdiutil mount "$HOME/Downloads/AppCleaner1.2.2.dmg" -quiet
echo "\"monterer\" Firefox"
hdiutil mount "$HOME/Downloads/Firefox 3.5.dmg" -quiet
echo "\"monterer\" GetTube"
hdiutil mount "$HOME/Downloads/GetTube.dmg" -quiet
echo "\"monterer\" Google Earth"
hdiutil mount "$HOME/Downloads/GoogleEarthMac.dmg" -quiet
#hdiutil mount "$HOME/Downloads/iWork09.dmg"
if [ "$installall" = "1" ]
then
    echo ilife
    #echo "\"monterer\" iLife 09"
    #hdiutil mount "$HOME/Downloads/iLife09.dmg" -quiet
    echo "\"monterer\" Olympus Master 2"
    hdiutil mount "$HOME/Downloads/olympus_master_2_en.dmg" -quiet
else
    echo ikke ilife
fi
echo "\"monterer\" iPhone SDK 3.1.2 med Xcode 3.2.1"
hdiutil mount "$HOME/Downloads/iphone_sdk_3.1.2_with_xcode_3.2.1__snow_leopard__10m2003.dmg" -quiet
echo "\"monterer\" MacFUSE"
hdiutil mount "$HOME/Downloads/MacFUSE-2.0.3,2.dmg" -quiet
echo "\"monterer\" MacPorts"
hdiutil mount "$HOME/Downloads/MacPorts-1.8.0-10.6-SnowLeopard.dmg" -quiet
echo "\"monterer\" MacScanInstaller"
hdiutil mount "$HOME/Downloads/MacScanInstaller.dmg" -quiet
echo "\"monterer\" MSN"
hdiutil mount "$HOME/Downloads/messenger702.dmg" -quiet
echo "\"monterer\" MySQL"
hdiutil mount "$HOME/Downloads/mysql-5.1.42-osx10.6-x86_64.dmg" -quiet
echo "\"monterer\" NetBeans"
hdiutil mount "$HOME/Downloads/netbeans-6.8-ml-macosx.dmg" -quiet
echo "\"monterer\" NTFS-3G"
hdiutil mount "$HOME/Downloads/NTFS-3G_2009.4.4-catacombae.dmg" -quiet
echo "\"monterer\" OnyX"
hdiutil mount "$HOME/Downloads/OnyX.dmg" -quiet
echo "\"monterer\" Opera"
hdiutil mount "$HOME/Downloads/Opera_10.00_Setup_Intel.dmg" -quiet
echo "\"monterer\" Parallels Desktop"
hdiutil mount "$HOME/Downloads/ParallelsDesktop-parallels-en_US-4.0.3810.237520.dmg" -quiet
#hdiutil mount "$HOME/Downloads/Silverlight.2.0.dmg" -quiet
echo "\"monterer\" Skype"
hdiutil mount "$HOME/Downloads/Skype_2.7.0.330.dmg" -quiet
echo "\"monterer\" Spotify"
hdiutil mount "$HOME/Downloads/Spotify.dmg" -quiet
echo "\"monterer\" Subersion"
hdiutil mount "$HOME/Downloads/Subversion 1.5.1-2 Universal.dmg" -quiet
echo "\"monterer\" TextMate"
hdiutil mount "$HOME/Downloads/TextMate_1.5.7.dmg" -quiet
echo "\"monterer\" VLC"
hdiutil mount "$HOME/Downloads/vlc-1.0.3-intel.dmg" -quiet
#"installerer" programmene
echo "Installerer AppCleaner"
cp -R "/Volumes/AppCleaner/AppCleaner.app" "/Applications/AppCleaner.app"
#cp -R "$HOME/Downloads/emacs/nextstep/Emacs.app" "/Applications/Emacs.app"
echo "Installerer Firefox"
cp -R "/Volumes/Firefox/Firefox.app" "/Applications/Firefox.app"
echo "Installerer Flip4Mac"
installer -dumplog -pkg "Downloads/Flip4Mac WMV.mpkg" -target /
echo "Installerer GetTube"
cp -R "/Volumes/GetTube/Get Tube.app" "/Applications/Get Tube.app"
echo "Installerer Google Earth"
cp -R "/Volumes/GoogleEarth-Mac/Google Earth.app" "/Applications/Google Earth.app"
#installer -dumplog -pkg "/Volumes/iWork '09/Packages/iWork09Trial.mpkg" -verboseR -target /
echo "Installerer Xcode 3.2.1 og iPhone SDK"
installer -dumplog -pkg "/Volumes/iPhone SDK/iPhone SDK and Tools for Snow Leopard.mpkg" -target /
echo "Installerer MacFUSE"
installer -dumplog -pkg "/Volumes/MacFUSE 2.0/MacFUSE.pkg" -target /
echo "Installerer MacPorts"
installer -dumplog -pkg "/Volumes/MacPorts-1.8.0/MacPorts-1.8.0.pkg" -target /
echo "Installerer MacScan"
installer -dumplog -pkg "/Volumes/MacScan Installer/MacScan Installer.pkg" -target /
echo "Installerer MSN"
cp -R "/Volumes/Microsoft Messenger/Microsoft Messenger.app" "/Applications/Microsoft Messenger.app"
echo "Installerer MySQL"
installer -dumplog -pkg "/Volumes/mysql-5.1.42-osx10.6-x86_64/mysql-5.1.42-osx10.6-x86_64.pkg" -target / 
installer -dumplog -pkg "/Volumes/mysql-5.1.42-osx10.6-x86_64/MySQLStartupItem.pkg" -target /
/Library/StartupItems/MySQLCOM/MySQLCOM start
echo "Kopierer biblioteksfilene fra /usr/local/mysql/include til /usr/include "
cp -R /usr/local/mysql/include/ /usr/include/
echo "Installerer NetBeans"
installer -dumplog -pkg "/Volumes/NetBeans 6.8/NetBeans 6.8.mpkg" -target /
echo "Installerer NTFS 3-G"
installer -dumplog -pkg "/Volumes/NTFS-3G 2009.4.4/Install NTFS-3G.mpkg" -target /
echo "Installerer OnyX"
installer -dumplog -pkg "/Volumes/OnyX 2.0.5/OnyX.pkg" -target /
echo "Installerer nettleseren Opera"
cp -R "/Volumes/Opera/Opera.app" "/Applications/Opera.app"
echo "Installerer Paralells Desktop"
installer -dumplog -pkg "/Volumes/Parallels Desktop 4/Install.mpkg" -target /
#installer -dumplog -pkg "/Volumes/Silverlight.2.0/Silverlight.2.0.pkg" -verboseR -target /
echo "Installerer Silverlight"
installer -dumplog -pkg "$HOME/Downloads/Silverlight.3.0.pkg" -target /
echo "Installerer Skype"
cp -R "/Volumes/Skype/Skype.app" "/Applications/Skype.app"
echo "Installerer Spotify"
cp -R "/Volumes/Spotify/Spotify.app" "/Applications/Spotify.app"
echo "Installerer Subversion"
installer -dumplog -pkg "/Volumes/Subversion 1.5.1-2 Universal/Subversion-1.5.1-2.pkg" -target /
echo "Installerer TextMate"
cp -R "/Volumes/TextMate 1.5.7/TextMate.app" "/Applications/TextMate.app"
echo "Installerer VLC"
cp -r "/Volumes/vlc-1.0.3/VLC.app" "/Applications/VLC.app"
#installer -dumplog -pkg "/Volumes/Mac OS X Install DVD/Optional Installs.localized/Xcode.mpkg" -verboseR -target /


if [ "$installall" = "1" ]
then
#    installer -dumplog -pkg "/Volumes/iLife '09 Install DVD/iLife '09.mpkg" -verboseR -target /
    installer -dumplog -pkg "/Volumes/OLYMPUS Master 2 Setup/Setup.mpkg" -target /
    echo "Restarter datamaskinen"
    reboot
else
    echo avslutter installasjonen...
    hdiutil detach "/Volumes/AppCleaner"
    hdiutil detach "/Volumes/Firefox"
    hdiutil detach "/Volumes/GetTube"
    hdiutil detach "/Volumes/GoogleEarth-Mac-Plus"
    hdiutil detach "/Volumes/iPhone SDK"
#    hdiutil detach "/Volumes/iWork '09"
    hdiutil detach "/Volumes/MacFUSE 2.0"
    hdiutil detach "/Volumes/MacScan Installer"
    hdiutil detach "/Volumes/Microsoft Messenger"
    hdiutil detach "/Volumes/NetBeans 6.8"
    hdiutil detach "/Volumes/NTFS-3G 2009.4.4"
    hdiutil detach "/Volumes/OnyX 2.0.3"
    hdiutil detach "/Volumes/Opera"
    hdiutil detach "/Volumes/Parallels Desktop 4"
#    hdiutil detach "/Volumes/Silverlight.2.0"
    hdiutil detach "/Volumes/Skype"
    hdiutil detach "/Volumes/Spotify"
    hdiutil detach "/Volumes/Subversion 1.5.1-2 Universal"
    hdiutil detach "/Volumes/TextMate 1.5.7"
    hdiutil detach "/Volumes/vlc-1.0.3/"
fi