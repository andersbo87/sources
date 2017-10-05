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
    void setUsername(QString newUser);
    void setPassword(QString newPassword);
    void setHost(QString newHost);
    bool insertCity(QString cityName, int countryID);
    bool updateApplication(QString title, QString company, int cityID, int statusID, QString date, int id);
    bool insertApplication(QString title, QString company, int cityID, int statusID, QString date);
    bool insertStatus(QString statusName);
    bool connectDatabase();
    QLinkedList<int> fillList(const char *sqlSporring);
    QString getStatusName(int s);
    QString getTitle(int applicationID);
    QString getCompany(int applicationID);
    int getCityID(int applicationID);
    int getStatusID(int applicationID);
    QString getDate(int applicationID);
    QString getCityName(int cityNumber);
    QString getCountryName(int countryID);

private:
    QString username, host, password;
    std::string connectionString;
};

#endif // PSQL_H
