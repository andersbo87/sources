# Jobber
Dette er en QT5-proram som viser en front-end av PostgreSQL-databasen "jobber".
Kildekoden ligger i mappen "jobber".
I mappene build-jobber-Desktop-Release og build-jobber-Desktop-Debug er det to Makefiles: En BSDmakefile som kan kjøres med kommandoen "make" på et BSD-basert system (testet og fungerer på FreeBSD) og en GNUmakefile som kan kjøres med "make" på Linux og Solaris eller med kommandoen "gmake" på BSD-baserte systemer.
Den kjørbare filen som ligger i de to mappene som standard, er kompilert på FreeBSD.

For å kunne kompilere dette programmet, må QT5 være installert. Det samme gjelder for biblioteket libpqxx er installert. Kilden til dette biblioteket kan lastes ned her: http://pqxx.org/download/software/libpqxx/. 