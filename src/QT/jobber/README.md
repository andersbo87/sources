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

### MacOS
Dersom QT er installert til /opt/local/Qt/5.9.2:
```
cd jobber/darwin
make install clean
```
Dersom du har installert en annen utgave av QT eller installert QT til et annet sted på disken:
```
cd jobber/darwin
qmake -o Makefile ../jobber.pro -spec macx-clang
cp -R jobber.app/ /Applications/jobber.app/
```
Programmet vil da bli installert til /Applications/jobber.app.

## Avhengighet og kompilering:
For å kunne kompilere dette programmet, må QT5 være installert. Det samme gjelder for biblioteket libpqxx er installert.
På Linux kan man kjøre kommandoen `apt install libpqxx-dev` (eller en tilsvarene kommando) for å installere dette biblioteket. På FreeBSD kan man gjøre det samme ved å kjøre `pkg install postgresql-pqxx`.

Kilden til dette biblioteket kan lastes ned her: http://pqxx.org/download/software/libpqxx/libpqxx-4.0.1.tar.gz. Merk at jobber ikke lar seg kompilere dersom versjon 5 eller høyere er installert.

### Linux
For å kunne kompilere dette programmet på Linux må følgende programmer også installeres:

- clang
- qt4-qmake
- qt5-default
- libpqxx-dev

### Mac
For å kunne kompilere dette programmet på Mac, må du installere QT. Dette kan gjøres via QTs offisielle installasjonsprogram for Mac, eller via for eksempel MacPorts.

### FreeBSD
For å kunne installere dette programmet på FreeBSD, må du installere

- databases/postgresql-pqxx
- devel/qt5

Dette kan installeres slik:
```
pkg install postgresql-pqxx qt5
```
eller slik:
```
cd /usr/ports/databases/postgresql-pqxx
make install clean
cd /usr/ports/devel/qt5
make install clean
```

Systemet vil da automatisk installere nødvendige programmer. Når dette er gjort, kan du følge instruksjonene over i avsnittet FreeBSD