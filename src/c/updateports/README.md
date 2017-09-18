Updateports er et C-program som oppdaterer både operativsystemet og installerte programmer.
Dette er et program som på mange måter oppfører seg som et skallprogram/shell script i det at den starter opp andre programmer som gjennomfører den faktiske oppdateringen. Hovedpoenget med dette programmet, var å leke meg litt med signaler (SIGINT, SIGSEGV, SIGINFO (sistnevnte fungerer kun på BSD)) og forsøke å lære meg hvilke funksjoner et skall "kjører" når man starter opp ulike programmer og verktøy via kommandolinja.

Updateports fungerer på FreeBSD, OpenBSD (via Pkgsrc), NetBSD (via Pkgsrc), macOS (via MacPorts), Linux og SunOS (Solaris samt "åpne" systemer som OpenIndiana som bygger på OpenSolaris).

Man installerer dette programmet ved å kjøre kommandoene 
make
make install clean
