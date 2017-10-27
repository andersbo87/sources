# updatefreebsdsrc
Dette er et QT-basert program som på en enkel måte lar brukeren oppdatere FreeBSD og installerte 3. parters programmer.

## Systemkrav
For å kunne kompilere og installere dette programmet, må nyeste utgave av QT være installert.
Dette programmet er kun ment å fungere på FreeBSD. Linux og andre systemer støttes ikke av dette programmet.

## Kompilering og installering
Du kan kompilere programmet ved å kjøre kommandoen
```
make
```
og deretter
```
make install clean
```
. Den siste av de to kommandoene vil trenge administratorrettigheter.

## Avistallering
Du kan avinstallere programmet ved å kjøre kommandoen
```
make uninstall
```
eller
```
make deinstall
```
som rotbruker.