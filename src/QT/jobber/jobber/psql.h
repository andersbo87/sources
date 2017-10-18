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
#include <QMessageBox>
#include <QException>
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
    int getRows(string query);
    // Funksjoner som angir parametere for å koble til databasen:
    void setHost(QString newHost);
    void setPassword(QString newPassword);
    void setUsername(QString newUser);

    // Koble til databasen:
    bool connectDatabase();

    // Metoder som setter inn ny data i databasen:
    bool insertApplication(QString title, QString company, int cityID, int statusID, QString date);
    bool insertCity(QString cityName, int countryID);
    bool insertCountry(QString countryName);
    bool insertStatus(QString statusName);

    // Metoder som oppdaterer eksisterende data
    bool updateApplication(QString title, QString company, int cityID, int statusID, QString date, int id);
    bool updateCity(QString cityName, int countryID, int id);
    bool updateCountry(QString countryName, int countryID);
    bool updateStatus(QString statusname, int statusID);

    // Metoder som sletter data fra databasen
    bool deleteApplication(int applicationID);
    bool deleteCity(int cityID);
    bool deleteCountry(int countryID);
    bool deleteStatus(int statusID);

    // Hente resultater. Rangert alfabetisk etter datatype og objekt/peker, deretter alfabetisk etter metodenavn
    int getApplicationID(QString qry);
    int getCityID(int applicationID);
    int getCountryID(int cityID);
    int getStatusID(int applicationID);
    QList<int> fillList(const char *sqlSporring);
    QList<int> getSpecificApplicationIDs(string jobTitle, string companyName, string cityName, string status, string deadline);
    QList<QString> getSpecificJobNames(string jobTitle, string companyName, string cityName, string status, string deadline);
    QList<QString> getSpecificCompanyNames(string jobTitle, string companyName, string cityName, string status, string deadline);
    QList<QString> getSpecificCityNames(string jobTitle, string companyName, string cityName, string status, string deadline);
    QList<QString> getSpecificStatuses(string jobTitle, string companyName, string cityName, string status, string deadline);
    QList<QString> getSpecificDeadlines(string jobTitle, string companyName, string cityName, string status, string deadline);
    QList<QString> getCityNames();
    QList<QString> getStatuses();
    QString getCityName(int cityNumber);
    QString getCompany(int applicationID);
    QString getCountryName(int countryID);
    QString getDate(int applicationID);
    QString getStatusName(int s);
    QString getTitle(int applicationID);
    //int getSpecificApplications(); // Returnerer antall søknader

private:
    QString username, host, password, winTitle; // winTitle: Tittelen på meldinger i meldingsbokser
    std::string connectionString;
};

#endif // PSQL_H
