# Jobber
Dette er et QT5-proram som viser en front-end av PostgreSQL-databasen "jobber".
Kildekoden ligger i mappen "jobber".


## Installasjon
### Linux
```
cd jobber/linux
sudo make install clean
```

### FreeBSD
```
cd jobber
sudo make install clean
```
eller
```
cd jobber
sudo gmake install clean
```

For å kunne kompilere dette programmet, må QT5 være installert. Det samme gjelder for biblioteket libpqxx er installert.
På Linux kan man kjøre kommandoen `apt install libpqxx-dev` (eller en tilsvarene kommando) for å installere dette biblioteket. På FreeBSD kan man gjøre det samme ved å kjøre `pkg install postgresql-pqxx`.

Kilden til dette biblioteket kan lastes ned her: http://pqxx.org/download/software/libpqxx/. 

For å kunne kompilere dette programmet på Linux må følgende programmer også installeres:

- clang
- qt4-qmake
- qt5-default
- libpqxx-dev