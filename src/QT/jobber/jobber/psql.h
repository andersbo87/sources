#ifndef PSQL_H
#define PSQL_H
#include <sstream>
#include <QApplication>
#include <QLinkedList>
#include <QMessageBox>
#include <QException>
#include <pqxx/pqxx>
#include <pqxx/result>
using namespace std;
using namespace pqxx;

/**
 * @brief The psql class
 */
class psql
{
public:
    psql();
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
    bool insertApplication(QString title, QString company, int cityID, int statusID, QString date);
    bool insertCity(QString cityName, int countryID);
    bool insertCountry(QString countryName);
    bool insertStatus(QString statusName);

    // Metoder som oppdaterer eksisterende data
    bool updateApplication(QString title, QString company, int cityID, int statusID, QString date, int id);
    bool updateCity(QString cityName, int countryID, int id);
    bool updateCountry(QString countryName, int countryID);
    bool updateStatus(QString statusname, int statusID);

    // Hente resultater. Rangert alfabetisk etter datatype og objekt/peker, deretter alfabetisk etter metodenavn
    int getCityID(int applicationID);
    int getCountryID(int countryID);
    int getStatusID(int applicationID);
    QLinkedList<int> fillList(const char *sqlSporring);
    QString getCityName(int cityNumber);
    QString getCompany(int applicationID);
    QString getCountryName(int countryID);
    QString getDate(int applicationID);
    QString getStatusName(int s);
    QString getTitle(int applicationID);


private:
    QString username, host, password;
    std::string connectionString;
};

#endif // PSQL_H
