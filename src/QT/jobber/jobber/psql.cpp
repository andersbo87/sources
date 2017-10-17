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

/**
  @file psql.cpp
*/

#include "psql.h"

psql::psql(QString windowTitle)
{
    winTitle = windowTitle;
}

/**
 * @brief psql::getUsername: Gets the username
 * @return the username
 */
QString psql::getUsername()
{
    return username;
}

/**
 * @brief psql::getPassword: Gets the user password
 * @return The user's password
 */
QString psql::getPassword()
{
    return password;
}

/**
 * @brief psql::getHost: Gets the IP address of the host
 * @return The host's IP address
 */
QString psql::getHost()
{
    return host;
}

/**
 * @brief psql::setUsername: Sets the new username
 * @param newUser: The new username
 */
void psql::setUsername(QString newUser)
{
    username = newUser;
}
/**
 * @brief psql::setPassword: Sets the new password
 * @param newPassword: The new password
 */
void psql::setPassword(QString newPassword)
{
    password = newPassword;
}

/**
 * @brief psql::setHost: Sets the IP address of the new host
 * @param newHost: The new IP address
 */
void psql::setHost(QString newHost)
{
    host = newHost;
}

/*
 * Metoder som setter data inn i databasen:
*/

/**
 * @brief psql::insertApplication Inserts a new job application to the database.
 * @param title The title of the new job.
 * @param company The employer company
 * @param cityID The ID of the city where the job is located.
 * @param statusID The status of the new job. Can be (in Norwegian) 1 (registrert), 2 (sendt), 3 (interessert, mulig intervju), 4 (avvist)
 * @param date The deadline of the new job application
 * @return True on success and false on failure.
 */
bool psql::insertApplication(QString title, QString company, int cityID, int statusID, QString date)
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "INSERT INTO soknad (tittel, bedrift, stedid, statusid, soknadsfrist) VALUES('";
        ostringstream oss;
        oss << statement << insertStatement.toStdString();
        oss << statement << title.toStdString();
        oss << statement << "', '";
        oss << statement << company.toStdString();
        oss << statement << "', ";
        oss << statement << cityID;
        oss << statement << ", ";
        oss << statement << statusID;
        oss << statement << ", '";
        oss << statement << date.toStdString();
        oss << statement << "')";

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Information);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
        return false;
    }
}

/**
 * @brief psql::insertCity Inserts a new city to the database
 * @param cityName The name of the new city
 * @param countryID The ID of the country in which the city is located
 * @return True if the insertion is successful and false otherwise
 */
bool psql::insertCity(QString cityName, int countryID)
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "INSERT INTO sted (stedsnavn, landid) VALUES('";
        ostringstream oss;
        oss << statement << insertStatement.toStdString();
        oss << statement << cityName.toStdString();
        oss << statement << "', ";
        oss << statement << countryID;
        oss << statement << ")";
        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Information);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
        return false;
    }
}

/**
 * @brief psql::insertCountry Inserts a new country into the database
 * @param countryName The name of the new country.
 * @return True on success and false on failure.
 */
bool psql::insertCountry(QString countryName)
{
    try
    {
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string stmt = "";
        QString insertStmt = "INSERT INTO land (land) VALUES('";
        ostringstream oss;
        oss << stmt << insertStmt.toStdString();
        oss << stmt << countryName.toStdString();
        oss << stmt << "')";
        pqxx::work wk(conn);
        wk.exec(oss.str());
        wk.commit();
        conn.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Information);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe er galt: " + QString::fromStdString(e.what()));
        msg.exec();
        return false;
    }
}

/**
 * @brief psql::insertStatus Inserts a new status to the database.
 * @param statusName The new status name
 * @return True on success and false on failure
 */
bool psql::insertStatus(QString statusName)
{
    try
    {
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "INSERT INTO status (status) values('";
        ostringstream oss;
        oss << statement << insertStatement.toStdString(); // Konverterer teksten i $insertStatement fra QString til std::string
        oss << statement << statusName.toStdString();
        oss << statement << "')";
        pqxx::work wk(conn);
        wk.exec(oss.str());
        wk.commit();
        conn.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe har gått galt: " + QString::fromStdString(e.what()));
        msg.exec();
        return false;
    }
}

/*
 * Metoder som oppdaterer data i databasen:
*/

/**
 * @brief psql::updateApplication: Updates the current job application
 * @param title: The new title
 * @param company: The new job company
 * @param cityID: The ID of the new city where the job is located
 * @param statusID: The status of the new job
 * @param date: The new job application deadline
 * @param id: The job ID to be updated.
 * @return True on success and false otherwise.
 */
bool psql::updateApplication(QString title, QString company, int cityID, int statusID, QString date, int id)
{
    try
    {
        // La oss først "skru sammen" SQL-spørringen:
        string statement = "";
        QString updateString = "UPDATE soknad SET ";
        ostringstream oss;
        oss << statement << updateString.toStdString();
        oss << statement << "tittel='";
        oss << statement << title.toStdString();
        oss << statement << "', bedrift='";
        oss << statement << company.toStdString();
        oss << statement << "', stedid=";
        oss << statement << cityID;
        oss << statement << ", statusid=";
        oss << statement << statusID;
        oss << statement << ", soknadsfrist='";
        oss << statement << date.toStdString();
        oss << statement << "' where soknadid=";
        oss << statement << id;
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(exception &e){
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe har gått galt: " + QString::fromStdString(e.what()));
        msg.exec();
        return false;
    }
}

bool psql::updateCity(QString cityName, int countryID, int id)
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "UPDATE sted SET stedsnavn = '";
        ostringstream oss;
        oss << statement << insertStatement.toStdString();
        oss << statement << cityName.toStdString();
        oss << statement << "', landid = ";
        oss << statement << countryID;
        oss << statement << " where stedid = ";
        oss << statement << id;
        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(exception &e){
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe har gått galt: " + QString::fromStdString(e.what()));
        msg.exec();
        return false;
    }
}

/**
 * @brief psql::updateCountry Updates an existing country.
 * @param countryName The new country name.
 * @param countryID The ID of the country to be updated.
 * @return True on success and false on failure.
 */
bool psql::updateCountry(QString countryName, int countryID)
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "UPDATE land SET land = '";
        ostringstream oss;
        oss << statement << insertStatement.toStdString();
        oss << statement << countryName.toStdString();
        oss << statement << "' where landid = ";
        oss << statement << countryID;
        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(exception &e){
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe har gått galt: " + QString::fromStdString(e.what()));
        msg.exec();
        return false;
    }
}

/**
 * @brief psql::updateStatus Updates an existing status.
 * @param statusname The new status name.
 * @param statusID The ID of the status to be updated.
 * @return True on success and false on failure.
 */
bool psql::updateStatus(QString statusname, int statusID)
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "UPDATE status SET status = '";
        ostringstream oss;
        oss << statement << insertStatement.toStdString();
        oss << statement << statusname.toStdString();
        oss << statement << "' where statusid = ";
        oss << statement << statusID;
        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(exception &e){
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe har gått galt: " + QString::fromStdString(e.what()));
        msg.exec();
        return false;
    }
}

/*
 * Meotder som sletter data fra databasen.
*/

/**
 * @brief psql::deleteApplication Removes an application from the database.
 * @param applicationID The ID of the application to be removed.
 * @return True on successful removal and false otherwise.
 */
bool psql::deleteApplication(int applicationID)
{
    try
    {
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string SQL;
        QString stmt="DELETE FROM soknad WHERE soknadid=";
        ostringstream oss;
        oss << SQL << stmt.toStdString();
        oss << SQL << applicationID;
        pqxx::work wk(conn);
        wk.exec(oss.str());
        wk.commit();
        conn.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox error;
        error.setIcon(error.Warning);
        error.setWindowTitle(winTitle);
        error.setText(e.what());
        error.exec();
        return false;
    }
}

/**
 * @brief psql::deleteCity Deletes an existing city from the database.
 * @param cityID The unique identification number of the city to be removed.
 * @return True on successful removal and false otherwise.
 */
bool psql::deleteCity(int cityID)
{
    try
    {
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string SQL;
        QString stmt = "DELETE FROM sted WHERE stedid=";
        ostringstream oss;
        oss << SQL << stmt.toStdString();
        oss << SQL << cityID;
        pqxx::work wk(conn);
        wk.exec(oss.str());
        wk.commit();
        conn.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox error;
        error.setIcon(error.Warning);
        error.setWindowTitle(winTitle);
        error.setText(e.what());
        error.exec();
        return false;
    }
}

/**
 * @brief psql::deleteCountry Deletes an existing country from the database.
 * @param countryID The unique number of the country in question.
 * @return True on successful removal and false otherwise.
 */
bool psql::deleteCountry(int countryID)
{
    try
    {
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string SQL;
        QString stmt = "DELETE FROM land WHERE landid=";
        ostringstream oss;
        oss << SQL << stmt.toStdString();
        oss << SQL << countryID;
        pqxx::work wk(conn);
        wk.exec(oss.str());
        wk.commit();
        conn.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox error;
        error.setIcon(error.Warning);
        error.setWindowTitle(winTitle);
        error.setText(e.what());
        error.exec();
        return false;
    }
}

/**
 * @brief psql::deleteStatus Deletes an existing status from the database.
 * @param statusID The identification number of the status to be deleted.
 * @return True on successful removal and false otherwise.
 */
bool psql::deleteStatus(int statusID)
{
    try
    {
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string SQL;
        QString stmt = "DELETE FROM status WHERE statusid=";
        ostringstream oss;
        oss << SQL << stmt.toStdString();
        oss << SQL << statusID;
        pqxx::work wk(conn);
        wk.exec(oss.str());
        wk.commit();
        conn.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        QMessageBox error;
        error.setIcon(error.Warning);
        error.setWindowTitle(winTitle);
        error.setText(e.what());
        error.exec();
        return false;
    }
}

/**
 * @brief psql::connectDatabase Connects to the PostgreSQL database.
 * @return True on successful connection and false on failure.
 */
bool psql::connectDatabase()
{
    try
    {
        //printf("user: %s\n", username.toStdString().c_str());
        connectionString = "dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432";
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        if(C.is_open())
        {
            //C.disconnect();
            return true;
        }
        else
            return false;
    }
    catch(const std::exception &e){
        QMessageBox msg;
        msg.setIcon(msg.Information);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
        return false;
    }
}

/**
 * @brief psql::fillList "Fills" a QLinkedList with integers based on the results of an SQL query.
 * @param sqlSporring The SQL query to be executed.
 * @return
 */
QList<int> psql::fillList(const char *sqlSporring)
{
    try
    {
        QList<int> list;// = new QLinkedList<int>();
        QList<int>::iterator iterator;

        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        if(C.is_open())
        {
            pqxx::nontransaction N(C);
            pqxx::result R(N.exec(sqlSporring));
            int i = 1;
            for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
            {
                for(pqxx::result::tuple::const_iterator field = c.begin(); field != c.end(); ++field)
                {
                    QString s = QString::fromStdString(field.c_str());
                    list.insert(i,s.toInt());
                    i++;
                }
            }
            C.disconnect();
            return list;
        }
        exit(EXIT_FAILURE);
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Information);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
        exit(EXIT_FAILURE);
        //return NULL;
    }
}
int psql::getRows(string query)
{
    int res = 0;
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        //string statement = "SELECT status FROM status WHERE statusid = ";
        ostringstream oss;
        oss << query;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res++;
        }
    }
    return res;
}

/**
 * @brief psql::getStatusName Returns the current status name
 * @param s the status ID to be used in an SQL query within the method
 * @return the status name on success and "Error" on failure.
 */
QString psql::getStatusName(int s)
{
    QString res = "";
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT status FROM status WHERE statusid = ";
        ostringstream oss;
        oss << statement << s;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str());
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    return "Error";
}

/**
 * @brief psql::getTitle Returns the application title based on the ID provided by the user
 * @param applicationID The application ID to be provided by the user.
 * @return the application title on success and "Error" on failure.
 */
QString psql::getTitle(int applicationID)
{
    QString res = "";
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT tittel FROM soknad WHERE soknadid = ";
        ostringstream oss;
        oss << statement << applicationID;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str());
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    return "Error";
}

/**
 * @brief psql::getCompany Gets the company name based on the application ID provided by the user.
 * @param applicationID The application ID provided by the user.
 * @return the company name on success and "Error" on failure.
 */
QString psql::getCompany(int applicationID)
{
    QString res = "";
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT bedrift FROM soknad WHERE soknadid = ";
        ostringstream oss;
        oss << statement << applicationID;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str());
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    return "Error";
}

/**
 * @brief psql::getCityID Gets the city ID of the application based on the application ID prvoided by the user.
 * @param applicationID The application ID
 * @return The city ID on success and 0 on failure.
 */
int psql::getCityID(int applicationID)
{
    int res = 0;
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT stedid FROM soknad WHERE soknadid = ";
        ostringstream oss;
        oss << statement << applicationID;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    return res;
}



int psql::getCountryID(int countryID)
{
    int res = 0;
    pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(conn.is_open())
    {
        pqxx::nontransaction nt(conn);
        string statement = "SELECT landid FROM sted WHERE stedid = ";
        ostringstream oss;
        oss << statement << countryID;
        pqxx::result re(nt.exec(oss.str()));
        for (pqxx::result::const_iterator ci = re.begin(); ci != re.end(); ++ci)
        {
            res = QString::fromUtf8(ci[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        conn.disconnect();
        return res;
    }
    return res;
}

/**
 * @brief psql::getStatusID Returns the status ID of the application based on the application ID provided by the user.
 * @param applicationID The application ID provided by the user.
 * @return the application ID on success and 0 on failure.
 */
int psql::getStatusID(int applicationID)
{
    int res = 0;
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT statusid FROM soknad WHERE soknadid = ";
        ostringstream oss;
        oss << statement << applicationID;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    return res;
}

/**
 * @brief psql::getDate Gets the application deadline based on the application ID provided by the user.
 * @param applicationID The application ID.
 * @return the application ID on success and 0 on failure.
 */
QString psql::getDate(int applicationID)
{
    QString res = "";
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT soknadsfrist FROM soknad WHERE soknadid = ";
        ostringstream oss;
        oss << statement << applicationID;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str());
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    return "Error";
}

QString psql::getCountryName(int countryID)
{
    QString res = "";
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT land FROM land WHERE landid = ";
        ostringstream oss;
        oss << statement << countryID; // Legger verdien av $countryID til i slutten av tekststrengen $statement.
        pqxx::result R(N.exec(oss.str())); // Utfører spørringen SELECT land FROM land WHERE landid = $countryID.
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
        {
            res = QString::fromUtf8(c[0].as<string>().c_str());
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    else
    {
        return "Error. Connection not open.";
    }
}

/**
 * @brief psql::getCityName Gets the name of the city based on the city number.
 * @param cityNumber the number of the city to be returned.
 * @return The city name on success and "Error" on failure.
 */
QString psql::getCityName(int cityNumber)
{
    QString res = "";
    pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
    if(C.is_open())
    {
        pqxx::nontransaction N(C);
        string statement = "SELECT stedsnavn FROM sted WHERE stedid = ";
        ostringstream oss;
        oss << statement << cityNumber;
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str());
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    return "Error";
}
