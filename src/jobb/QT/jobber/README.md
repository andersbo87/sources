# Jobber
Dette er et QT5-proram som viser en front-end av PostgreSQL-databasen "jobber".
Kildekoden ligger i mappen "jobber".


## Installasjon
### Linux
```
cd jobber/linux
sudo ./install.sh
```

### FreeBSD
```
cd jobber/freebsd
sudo ./install.sh
```

### MacOS
Dersom QT er installert til /opt/local/Qt/5.9.2:
```
cd jobber/darwin
./install.sh
```
Dersom du har installert en annen utgave av QT eller installert QT til et annet sted på disken:
```
cd jobber/darwin
qmake -o Makefile ../jobber.pro -spec macx-clang
make
cp -R jobber.app/ /Applications/jobber.app/
```
Programmet vil da bli installert til /Applications/jobber.app.

Skriptet install.sh generer Makefile automatisk og kjører deretter kommandoen make eller make install clean avhengig av operativsystem.

## Avhengighet og kompilering:
For å kunne kompilere dette programmet, må QT5 være installert. Det samme gjelder for biblioteket libpqxx er installert.
På Linux kan man kjøre kommandoen `apt install libpqxx-dev` (eller en tilsvarene kommando) for å installere dette biblioteket. På FreeBSD kan man gjøre det samme ved å kjøre `pkg install postgresql-pqxx`.

Programmet krever libpqxx versjon 6 som kan lastes ned slik:
```
git clone https://github.com/jtv/libpqxx.git
./configure --disable-documentation
make
make install clean
```

### Linux
For å kunne kompilere dette programmet på Linux må følgende programmer også installeres i tillegg til libpqxx:

- clang
- qt4-qmake
- qt5-default

### Mac
For å kunne kompilere dette programmet på Mac, må du installere QT. Dette kan gjøres via QTs offisielle installasjonsprogram for Mac, eller via for eksempel MacPorts. I tillegg må du også installere libpqxx (se avsnitt over).

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

Systemet vil da automatisk installere nødvendige programmer. Når dette er gjort, kan du følge instruksjonene over i avsnittet FreeBSD.

## Avinstallering
For å avinstallere programmet, gjør du følgende:
### FreeBSD
```
cd freebsd
sudo ./install.sh uninstall
```
### Linux
```
cd linux
sudo ./install.sh uninstall
```
### macOS
```
cd darwin
./install.sh uninstall
```