#!/bin/sh

#program som tar en backup av /Library/WebServer og /Users
if -r /Volumes/MacBackup/Library
then
cp -Rv /Library/WebServer/ /Volumes/MacBackup/Library/WebServer/
else
mkdir /Volumes/MacBackup/Library
cp -Rv /Library/WebServer/ /Volumes/MacBackup/Library/WebServer/
fi
cp -Rv /Users/ /Volumes/MacBackup/Users/