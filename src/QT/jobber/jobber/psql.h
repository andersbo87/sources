/*
Copyright (c) 2017, Anders Bolt-Evensen
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ANDERS BOLT-EVENSEN BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef PSQL_H
#define PSQL_H
#include <sstream>
#include <QApplication>
#include <QLinkedList>
#include <QException>
#include <QDebug>
#include <pqxx/pqxx>
#include <pqxx/result>
#include <QtGui>
using namespace std;
using namespace pqxx;

/**
 * @brief The psql class
 */
class psql
{
public:
    psql(QString windowTitle);
    QString getUsername();
    QString getPassword();
    QString getHost();
    // Funksjoner som angir parametere for å koble til databasen:
    void setHost(QString newHost);
    void setPassword(QString newPassword);
    void setUsername(QString newUser);

    // Koble til databasen:
    bool connectDatabase();

    // Metoder som setter inn ny data i databasen:
    bool insertApplication(QString title, QString company, int cityID, int statusID, QString date, QString motivation);
    bool insertCity(QString cityName, int countryID);
    bool insertCountry(QString countryName);
    bool insertStatus(QString statusName);

    // Metoder som oppdaterer eksisterende data
    bool updateApplication(QString title, QString company, int cityID, int statusID, QString date, QString motivation, int id);
    bool updateCity(QString cityName, int countryID, int id);
    bool updateCountry(QString countryName, int countryID);
    bool updateStatus(QString statusname, int statusID);

    // Metoder som sletter data fra databasen
    bool deleteApplication(int applicationID);
    bool deleteCity(int cityID);
    bool deleteCountry(int countryID);
    bool deleteStatus(int statusID);

    // Metoder som sjekker om tabellene eksisterer i databasen. Det er 4 tabeller og 2 "views"
    bool tableApplicationExists();
    bool tableCountryExists();
    bool tableStatusExists();
    bool tableTownExists();
    bool viewApplicationExists();
    bool viewTownExists();

    // Metoder som oppretter tabellene nevnt over om de ikke eksisterer
    bool createTableApplication();
    bool createTableCountry();
    bool createTableStatus();
    bool createTableTown();
    bool createViewApplication();
    bool createViewTowns();

    // Metoder som oppretter lagrede prosedyrer som returnerer en trigger. Denne triggeren brukes i egne funksjoner.
    bool createProcedureNewApplicationID();
    bool createProcedureUpdateApplication();
    bool createProcedureNewCountryID();
    bool createProcedureNewTownID();

    // Metoder som oppretter sekvenser som brukes til å øke ID-tellerne med 1
    bool createSequenceApplicationIDSeq();
    bool createSequenceCountryIDSeq();
    bool createSequenceStatusIDSeq();
    bool createSequenceTownIDSeq();

    // Metoder som henter og setter feilmeldinger.
    QString getError();
    void setError(QString msg);

    // Metoder som henter antall søknader i hver kategori (status):
    double countTotalApplications();
    double countRegisteredApplications(); // Applications that have been added to the database but not sent. StatusID 1
    double countSentApplications(); // Get applications that have been sent and not answered. StatusID 2
    double countInterviews(); // Get applications employers are interested in and have called in for an interviews. StatusID 3
    double countDeclinedApplications(); // Applications that have been declined. StatusID 4
    double countWrittenButNotSent(); // Applications that have been written but not sent to the employer. StatusID 5
    double countDeclinedAfterInterview(); // Application declined after interview. StatusID 6
    double countAccepted(); // Application accepted and ready to start the job. StatusID 7

    // Hente resultater. Rangert alfabetisk etter datatype og objekt/peker, deretter alfabetisk etter metodenavn
    int getCityID(int applicationID);
    int getCityID(string name);
    int getCountryID(int cityID);
    int getStatusID(int applicationID);
    QList<QString> fillList(const char *sqlSporring);
    //QList<QString> psql::fillList(const char *sqlSporring);
    QList<int> getSpecificApplicationIDs(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation);
    QList<QString> getSpecificJobNames(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation);
    QList<QString> getSpecificCompanyNames(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation);
    QList<QString> getSpecificCityNames(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation);
    QList<QString> getSpecificStatuses(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation);
    QList<QString> getSpecificDeadlines(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation);
    QList<QString> getSpecificMotivations(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation);
    QList<QString> getCityNames();
    QList<QString> getStatuses();
    QString getCityName(int cityNumber);
    QString getCompany(int applicationID);
    QString getCountryName(int countryID);
    QString getDate(int applicationID);
    QString getStatusName(int s);
    QString getTitle(int applicationID);
    QString getMotivation(int applicationID);
    //int getSpecificApplications(); // Returnerer antall søknader

private:
    QString errMsg, username, host, password, winTitle; // winTitle: Tittelen på meldinger i meldingsbokser. errMsg: Feilmelding som settes i metoder som ikke går som de skal.
    std::string connectionString;

    // Metode som brukes til å lage en "stored procedure" som returnerer en boolsk verdi:
    bool createFunctionEmptyText();

    // Metoder som oppretter triggerfunksjoner som hører til tabellene nevnt over:
    bool createTriggerNewApplicationID();
    bool createTriggerUpdateApplication();
    bool createTriggerNewCountryID();
    bool createTriggerNewTownID();
};

#endif // PSQL_H
