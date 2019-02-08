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
#include <stdio.h>

/**
 * @brief psql::psql Class constructor
 * @param windowTitle The title of the window to be used in message boxes.
 */
psql::psql(QString windowTitle)
{
    winTitle = windowTitle;
}

/**
 * @brief psql::getError If an operation goes wrong, this method can be used to get the returned error message.
 * @return The error message.
 */
QString psql::getError()
{
    return errMsg;
}

/**
 * @brief psql::setError If an operation goes wrong, this method saves the contents of the error message.
 * @param msg The error message to be saved.
 */
void psql::setError(QString msg)
{
    qDebug("Noe har gått galt og et unntak har blitt kastet. Feilmelding: %s", msg.toStdString().c_str());
    errMsg = msg;
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
 * @param motivation The reasons and motivation for applying for this job
 * @return True on success and false on failure.
 */
bool psql::insertApplication(QString title, QString company, int cityID, int statusID, QString date, QString motivation)
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "INSERT INTO soknad (tittel, bedrift, stedid, statusid, soknadsfrist, motivasjon) VALUES('";
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
        oss << statement << "', '";
        oss << statement << motivation.toStdString();
        oss << statement << "')";

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
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
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @param id: The job ID to be updated.
 * @return True on success and false otherwise.
 */
bool psql::updateApplication(QString title, QString company, int cityID, int statusID, QString date, QString motivation, int id)
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
        oss << statement << "', motivasjon='";
        oss << statement << motivation.toStdString();
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
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::updateCity Updates information of an existing city.
 * @param oldCityName The old name of the city to be updated
 * @param newCityName The new name of the city
 * @param countryID The new country ID, the ID of the country where the city is located.
 * @return
 */
bool psql::updateCity(QString oldCityName, QString newCityName, int countryID)
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString insertStatement = "UPDATE sted SET stedsnavn = '";
        ostringstream oss;
        oss << statement << insertStatement.toStdString();
        oss << statement << newCityName.toStdString();
        oss << statement << "', landid = ";
        oss << statement << countryID;
        oss << statement << " where stedsnavn = '";
        oss << statement << oldCityName.toStdString();
        oss << statement << "' and landid= ";
        oss << statement << countryID;
        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(exception &e){
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
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
        setError(e.what());
        return false;
    }
}

/*
 * Metoder som bygger opp en liste med QStrings eller heltall basert på ulike søkekriterier:
*/
/**
 * @brief psql::getSpecificJobNames Builds list of job titles based on search criteria.
 * @param jobTitle The job title to be included in the search
 * @param companyName The name of the company to be included
 * @param cityName The name of the city where the job is located.
 * @param status The status of the application(s) in question.
 * @param deadline The deadline of the application(s) in question.
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @return A list of strings containing the job names that matched the search.
 */
QList<QString> psql::getSpecificJobNames(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
{
    try
    {
        QList<QString> list;
        //QList<int>::iterator iterator;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        QString stmt = "SELECT tittel FROM view_soknad WHERE tittel like '%";
        string sql;
        stringstream oss;
        oss << sql << stmt.toStdString();
        oss << sql << jobTitle;
        oss << sql << "%' and bedrift like '%";
        oss << sql << companyName;
        if(QString::compare(QString::fromStdString(cityName), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and stedsnavn like '%";
            oss << sql << cityName;
        }
        if(QString::compare(QString::fromStdString(status), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and status like '%";
            oss << sql << status;
        }
        oss << sql << "%' and soknadsfrist like '%";
        oss << sql << deadline;
        oss << sql << "%' and motivasjon like '%";
        oss << sql << motivation;
        oss << sql << "%';";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(oss.str()));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        conn.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}
/**
 * @brief psql::getSpecificCompanyNames Builds a list with name of job company/companies based on search criteria.
 * @param jobTitle The job title to be included in the search
 * @param companyName The name of the company to be included
 * @param cityName The name of the city where the job is located.
 * @param status The status of the application(s) in question.
 * @param deadline The deadline of the application(s) in question.
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @return A list of strings containing the job companies that matched the search.
 */
QList<QString> psql::getSpecificCompanyNames(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
{
    try
    {
        QList<QString> list;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        QString stmt = "SELECT bedrift FROM view_soknad WHERE tittel like '%";
        string sql;
        stringstream oss;
        oss << sql << stmt.toStdString();
        oss << sql << jobTitle;
        oss << sql << "%' and bedrift like '%";
        oss << sql << companyName;
        if(QString::compare(QString::fromStdString(cityName), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and stedsnavn like '%";
            oss << sql << cityName;
        }
        if(QString::compare(QString::fromStdString(status), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and status like '%";
            oss << sql << status;
        }
        oss << sql << "%' and soknadsfrist like '%";
        oss << sql << deadline;
        oss << sql << "%' and motivasjon like '%";
        oss << sql << motivation;
        oss << sql << "%';";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(oss.str()));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        conn.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}
/**
 * @brief psql::getSpecificDeadlines Builds a list of application deadlines based on search criteria
 * @param jobTitle The job title to be included in the search
 * @param companyName The name of the company to be included
 * @param cityName The name of the city where the job is located.
 * @param status The status of the application(s) in question.
 * @param deadline The deadline of the application(s) in question.
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @return A list of strings containing the application deadlines that matched the search.
 */
QList<QString> psql::getSpecificDeadlines(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
{
    try
    {
        QList<QString> list;
        //QList<int>::iterator iterator;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        QString stmt = "SELECT soknadsfrist FROM view_soknad WHERE tittel like '%";
        string sql;
        stringstream oss;
        oss << sql << stmt.toStdString();
        oss << sql << jobTitle;
        oss << sql << "%' and bedrift like '%";
        oss << sql << companyName;
        if(QString::compare(QString::fromStdString(cityName), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and stedsnavn like '%";
            oss << sql << cityName;
        }
        if(QString::compare(QString::fromStdString(status), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and status like '%";
            oss << sql << status;
        }
        oss << sql << "%' and soknadsfrist like '%";
        oss << sql << deadline;
        oss << sql << "%' and motivasjon like '%";
        oss << sql << motivation;
        oss << sql << "%';";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(oss.str()));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        conn.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}
/**
 * @brief psql::getSpecificCityNames Builds a list of city names in one or more applications based on search criteria.
 * @param jobTitle The job title to be included in the search
 * @param companyName The name of the company to be included
 * @param cityName The name of the city where the job is located.
 * @param status The status of the application(s) in question.
 * @param deadline The deadline of the application(s) in question.
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @return A list of strings containing the city name(s) that matched the search.
 */
QList<QString> psql::getSpecificCityNames(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
{
    try
    {
        QList<QString> list;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        QString stmt = "SELECT stedsnavn FROM view_soknad WHERE tittel like '%";
        string sql;
        stringstream oss;
        oss << sql << stmt.toStdString();
        oss << sql << jobTitle;
        oss << sql << "%' and bedrift like '%";
        oss << sql << companyName;
        if(QString::compare(QString::fromStdString(cityName), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and stedsnavn like '%";
            oss << sql << cityName;
        }
        if(QString::compare(QString::fromStdString(status), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and status like '%";
            oss << sql << status;
        }
        oss << sql << "%' and soknadsfrist like '%";
        oss << sql << deadline;
        oss << sql << "%' and motivasjon like '%";
        oss << sql << motivation;
        oss << sql << "%';";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(oss.str()));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        conn.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}
/**
 * @brief psql::getSpecificStatuses Builds a list of statuses based on the search criteria.
 * @param jobTitle The job title to be included in the search
 * @param companyName The name of the company to be included
 * @param cityName The name of the city where the job is located.
 * @param status The status of the application(s) in question.
 * @param deadline The deadline of the application(s) in question.
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @return A list of strings containing the status names that matched the search.
 */
QList<QString> psql::getSpecificStatuses(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
{
    try
    {
        QList<QString> list;
        //QList<int>::iterator iterator;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        QString stmt = "SELECT status FROM view_soknad WHERE tittel like '%";
        string sql;
        stringstream oss;
        oss << sql << stmt.toStdString();
        oss << sql << jobTitle;
        oss << sql << "%' and bedrift like '%";
        oss << sql << companyName;
        if(QString::compare(QString::fromStdString(cityName), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and stedsnavn like '%";
            oss << sql << cityName;
        }
        if(QString::compare(QString::fromStdString(status), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and status like '%";
            oss << sql << status;
        }
        oss << sql << "%' and soknadsfrist like '%";
        oss << sql << deadline;
        oss << sql << "%' and motivasjon like '%";
        oss << sql << motivation;
        oss << sql << "%';";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(oss.str()));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        conn.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}
/**
 * @brief psql::getSpecificApplicationIDs Builds a list of application IDs based on search criteria.
 * @param jobTitle The job title to be included in the search
 * @param companyName The name of the company to be included
 * @param cityName The name of the city where the job is located.
 * @param status The status of the application(s) in question.
 * @param deadline The deadline of the application(s) in question.
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @return A list of integers containing the application ID(s).
 */
QList<int> psql::getSpecificApplicationIDs(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
{
    try
    {
        QList<int> list;
        QList<int>::iterator iterator;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        QString stmt = "SELECT soknadid FROM view_soknad WHERE tittel like '%";
        string sql;
        stringstream oss;
        oss << sql << stmt.toStdString();
        oss << sql << jobTitle;
        oss << sql << "%' and bedrift like '%";
        oss << sql << companyName;
        if(QString::compare(QString::fromStdString(cityName), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and stedsnavn like '%";
            oss << sql << cityName;
        }
        if(QString::compare(QString::fromStdString(status), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and status like '%";
            oss << sql << status;
        }
        oss << sql << "%' and soknadsfrist like '%";
        oss << sql << deadline;
        oss << sql << "%' and motivasjon like '%";
        oss << sql << motivation;
        oss << sql << "%';";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(oss.str()));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s.toInt());
                i++;
            }
        }
        conn.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}

/**
 * @brief psql::getSpecificMotivations Builds a list of motivations based on search criteria.
 * @param jobTitle The job title to be included in the search
 * @param companyName The name of the company to be included
 * @param cityName The name of the city where the job is located.
 * @param status The status of the application(s) in question.
 * @param deadline The deadline of the application(s) in question.
 * @param motivation An optional text containing the reasons and motivation why the user applied for this job
 * @return A list of strings containing the motivations and reasons for applying for those jobs.
 */
QList<QString> psql::getSpecificMotivations(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
{
    try
    {
        QList<QString> list;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        QString stmt = "SELECT motivasjon FROM view_soknad WHERE tittel like '%";
        string sql;
        stringstream oss;
        oss << sql << stmt.toStdString();
        oss << sql << jobTitle;
        oss << sql << "%' and bedrift like '%";
        oss << sql << companyName;
        if(QString::compare(QString::fromStdString(cityName), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and stedsnavn like '%";
            oss << sql << cityName;
        }
        if(QString::compare(QString::fromStdString(status), "", Qt::CaseSensitive) != 0)
        {
            oss << sql << "%' and status like '%";
            oss << sql << status;
        }
        oss << sql << "%' and soknadsfrist like '%";
        oss << sql << deadline;
        oss << sql << "%' and motivasjon like '%";
        oss << sql << motivation;
        oss << sql << "%';";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(oss.str()));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        conn.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}

/*
 * Metoder som brukes for å føre statistikk over totalt antall-, registrerte-, sendte-, avviste-, skrevet men ikke sendte- og godtatte søknader.
*/

/**
 * @brief psql::countTotalApplications Counts the total registered applications (registered, sent, interested in interview, declined, etc.
 * @return The total number of job applications in the database.
 */
double psql::countTotalApplications()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::countRegisteredApplications Counts the number of registered job applications that have not yet been sent (status id 1)
 * @return The number of registered job applications.
 */
double psql::countRegisteredApplications()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad group by statusid having statusid=1";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::countSentApplications Counts the number of sent applications (status id 2)
 * @return The number of sent applications.
 */
double psql::countSentApplications()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad group by statusid having statusid=2";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::countInterviews Counts the number of applications which the emplyer found interesting and called for an interview
 * @return The number of applications that "led" to an interview.
 */
double psql::countInterviews()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad group by statusid having statusid=3";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::countDeclinedApplications Counts the number of applications that have been declined/rejected by the employer.
 * @return The number of declined/rejected applications
 */
double psql::countDeclinedApplications()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad group by statusid having statusid=4";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::countDeclinedAfterInterview Counts the number of applications that has lead to an interview and then got rejected.
 * @return The number of applications that have been declined after an interview
 */
double psql::countDeclinedAfterInterview()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad group by statusid having statusid=6";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::countWrittenButNotSent Counts the number of applications that have been written, but not yet sent.
 * @return The number of applications that have been written, but not yet sent.
 */
double psql::countWrittenButNotSent()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad group by statusid having statusid=5";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::countAccepted Counts the number of applications that have been accepted and has lead to an employment.
 * @return The number of accepted applications.
 */
double psql::countAccepted()
{
    double res = 0;
    string stmt;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "select count(statusid) from soknad group by statusid having statusid=7";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception e)
    {
        setError(e.what());
        throw;
    }
}

// Andre metoder:

/**
 * @brief psql::getStatusID Gets the status ID based on the status name
 * @param name The name of the status
 * @return The ID of the status in question.
 */
int psql::getStatusID(string name)
{
    int res = 0;
    string stmt;// = name.toStdString();
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "SELECT statusid FROM status WHERE status = '";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        oss << stmt << name;
        oss << stmt << "'";
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::getCityID Gets the ID of a city based on its name
 * @param name The city name
 * @return The city ID
 */
int psql::getCityID(string name)
{
    int res = 0;
    string stmt;// = name.toStdString();
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        QString statement = "SELECT stedid FROM sted WHERE stedsnavn = '";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        oss << stmt << name;
        oss << stmt << "'";
        pqxx::result R(N.exec(oss.str()));
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}


/**
 * @brief psql::getCityNames Builds a list of strings that cointain name of all cities in the database.
 * @return On success, return the mentioned list of strings.
 */
QList<QString> psql::getCityNames()
{
    try
    {
        QList<QString> list;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string query = "SELECT stedsnavn FROM sted ORDER BY stedsnavn ASC";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(query));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}

/**
 * @brief psql::getStatuses Builds a list of all statuses registered in the database.
 * @return On success, return the mentioned list of strings.
 */
QList<QString> psql::getStatuses()
{
    try
    {
        QList<QString> list;
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string query = "SELECT status FROM status ORDER BY status ASC";
        pqxx::nontransaction nt(conn);
        pqxx::result res(nt.exec(query));
        int i = 1;
        for(pqxx::result::const_iterator ci = res.begin(); ci != res.end(); ci++)
        {
            for(pqxx::row::const_iterator tci = ci.begin(); tci != ci.end(); tci++)
            {
                QString s = QString::fromStdString(tci.c_str());
                list.insert(i, s);
                i++;
            }
        }
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}

/**
 * @brief psql::fillList "Fills" a QList with integers based on the results of an SQL query.
 * @param sqlSporring The SQL query to be executed.
 * @return A list of ints based on the results of the query in "sqlSporring"
 */
QList<QString> psql::fillList(const char *sqlSporring)
{
    try
    {
        QList<QString> list;// = new QLinkedList<int>();
        QList<QString>::iterator iterator;

        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        pqxx::result R(N.exec(sqlSporring));
        int i = 1;
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
        {
            for(pqxx::row::const_iterator field = c.begin(); field != c.end(); ++field)
            {
                QString s = QString::fromStdString(field.c_str());
                list.insert(i,QString::fromStdString(s.toStdString()));
                i++;
            }
        }
        C.disconnect();
        return list;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}

/**
 * @brief psql::getStatusName Returns the current status name
 * @param s the status ID to be used in an SQL query within the method
 * @return the status name on success and "Error" on failure.
 */
QString psql::getStatusName(int s)
{
    QString res = "";
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw; // Kaster unntaket videre.
    }
}

/**
 * @brief psql::getMotivation The the motivation for the job application based on the application ID.
 * @param applicationID The ID of the application in question
 * @return A string explaing what motivated the user to apply for this job.
 */
QString psql::getMotivation(int applicationID)
{
    QString res = "";
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        string statement = "SELECT motivasjon FROM soknad WHERE soknadid = ";
        ostringstream oss;
        oss << statement << applicationID;
        pqxx::result R(N.exec(oss.str()));
        if(R.empty())
            return "";
        else {
            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
                res = QString::fromUtf8(c[0].as<string>().c_str());
            }
        }
        oss.clear();
        C.disconnect();
        return res;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        qDebug() << e.what();
        return "";
    }
}

/**
 * @brief psql::getTitle Returns the application title based on the ID provided by the user
 * @param applicationID The application ID to be provided by the user.
 * @return the application title on success and "Error" on failure.
 */
QString psql::getTitle(int applicationID)
{
    QString res = "";
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::getCompany Gets the company name based on the application ID provided by the user.
 * @param applicationID The application ID provided by the user.
 * @return the company name on success and "Error" on failure.
 */
QString psql::getCompany(int applicationID)
{
    QString res = "";
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}


/**
 * @brief psql::getCityID Gets the city ID of the application based on the application ID prvoided by the user.
 * @param applicationID The application ID
 * @return The city ID on success and 0 on failure.
 */
int psql::getCityID(int applicationID)
{
    int res = 0;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::getCountryID Get the country ID of table sted based on given stedid.
 * @param cityID The ID of the city in question.
 * @return The country ID of the city in question.
 */
int psql::getCountryID(int cityID)
{
    int res = 0;
    try
    {
        pqxx::connection conn("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction nt(conn);
        string statement = "SELECT landid FROM sted WHERE stedid = ";
        ostringstream oss;
        oss << statement << cityID;
        pqxx::result re(nt.exec(oss.str()));
        for (pqxx::result::const_iterator ci = re.begin(); ci != re.end(); ++ci)
        {
            res = QString::fromUtf8(ci[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        conn.disconnect();
        return res;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::getStatusID Returns the status ID of the application based on the application ID provided by the user.
 * @param applicationID The application ID provided by the user.
 * @return the application ID on success and 0 on failure.
 */
int psql::getStatusID(int applicationID)
{
    int res = 0;
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::getDate Gets the application deadline based on the application ID provided by the user.
 * @param applicationID The application ID.
 * @return the application ID on success and 0 on failure.
 */
QString psql::getDate(int applicationID)
{
    QString res = "";
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::getCountryName Gets the name of a country based on its ID.
 * @param countryID The ID of the country in question.
 * @return On success, return the name of the country.
 */
QString psql::getCountryName(int countryID)
{
    QString res = "";
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
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
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
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
    catch(std::exception &e)
    {
        setError(e.what());
        throw;
    }
}

/**
 * @brief psql::tableApplicationExists Checks if the table "soknad" exists in the database by attempting to fetch data from it.
 * @return True if the table exists in the database and false if it does not.
 */
bool psql::tableApplicationExists()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        string stmt = "";
        QString res, statement = "select soknadid from soknad where soknadid=1";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}

/**
 * @brief psql::tableCountryExists Checks if the table "land" exists in the database by attempting to fetch data fram the table.
 * @return True if the table exists in the database and false if it does not.
 */
bool psql::tableCountryExists()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        string stmt = "";
        QString res, statement = "select landid from land where landid=1";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}

/**
 * @brief psql::tableStatusExists Checks if the table "status" exists in the database py attempting to pull data from the table.
 * @return True if the table exists and false if it does not.
 */
bool psql::tableStatusExists()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        string stmt = "";
        QString res, statement = "select statusid from status where statusid=1";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}

/**
 * @brief psql::tableTownExists Checks if the table "sted" (town) exists by attempting to fetch data from it
 * @return True if the table exists and false if it does'nt
 */
bool psql::tableTownExists()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        string stmt = "";
        QString res, statement = "select stedid from sted where stedid=1";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}

/**
 * @brief psql::viewApplicationExists Checks if any job applications exists in the database by looking up index 1 in the application table.
 * @return True if the application exists, false otherwise
 */
bool psql::viewApplicationExists()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        string stmt = "";
        QString res, statement = "select soknadid from view_soknad where soknadid=1";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}

/**
 * @brief psql::viewTownExists Checks if there are any towns in the database by looking up a town with ID=1
 * @return True if the town with index 1 is found, false otherwise
 */
bool psql::viewTownExists()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        pqxx::nontransaction N(C);
        string stmt = "";
        QString res, statement = "select stedid from view_sted where stedid=1";
        ostringstream oss;
        oss << stmt << statement.toStdString();
        pqxx::result R(N.exec(oss.str()));
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c){
            res = QString::fromUtf8(c[0].as<string>().c_str()).toInt();
        }
        oss.clear();
        C.disconnect();
        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}

/**
 * @brief psql::createTableApplication Creates the table "soknad"
 * @return True on success and false on failure
 */
bool psql::createTableApplication()
{
    try
    {
        createSequenceApplicationIDSeq();
        createFunctionEmptyText();
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TABLE public.soknad(soknadid integer NOT NULL DEFAULT nextval('soknadid_seq'::regclass),tittel text COLLATE pg_catalog.\"default\" NOT NULL, bedrift text COLLATE pg_catalog.\"default\" NOT NULL, stedid integer NOT NULL, statusid integer NOT NULL, soknadsfrist text COLLATE pg_catalog.\"default\" NOT NULL, motivasjon text COLLATE pg_catalog.\"default\", CONSTRAINT soknad_pkey PRIMARY KEY (soknadid), CONSTRAINT unik_soknad UNIQUE (tittel, bedrift, stedid), CONSTRAINT soknad_statusid_fkey FOREIGN KEY (statusid) REFERENCES public.status (statusid) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION, CONSTRAINT soknad_stedid_fkey FOREIGN KEY (stedid) REFERENCES public.sted (stedid) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION, CONSTRAINT chk CHECK (NOT empty(tittel)), CONSTRAINT chkbedriftnotempty CHECK (NOT empty(bedrift)), CONSTRAINT chksoknadsfristnotempty CHECK (NOT empty(soknadsfrist))) WITH (OIDS = FALSE) TABLESPACE pg_default;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return createProcedureNewApplicationID() && createProcedureUpdateApplication();
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createTableCountry Creates the table "land".
 * @return True on success and false on failure
 */
bool psql::createTableCountry()
{
    try
    {
        createSequenceCountryIDSeq();
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TABLE public.land(landid integer NOT NULL DEFAULT nextval('landid_seq'::regclass), land text COLLATE pg_catalog.\"default\" NOT NULL, CONSTRAINT land_pkey PRIMARY KEY (landid), CONSTRAINT unikt_land UNIQUE (land))WITH (OIDS = FALSE) TABLESPACE pg_default;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return createProcedureNewCountryID();
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createTableStatus Creates the table "status"
 * @return True on success and false on failure
 */
bool psql::createTableStatus()
{
    try
    {
        createSequenceStatusIDSeq();
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TABLE public.status(statusid integer NOT NULL DEFAULT nextval('statusid_seq'::regclass), status character varying(30) COLLATE pg_catalog.\"default\" NOT NULL, CONSTRAINT status_pkey PRIMARY KEY (statusid), CONSTRAINT unik_status UNIQUE (status)) WITH (OIDS = FALSE) TABLESPACE pg_default;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createTableTown Creates the table "sted"
 * @return True on success and false on failure
 */
bool psql::createTableTown()
{
    try
    {
        createSequenceTownIDSeq();
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TABLE public.sted (stedid integer NOT NULL DEFAULT nextval('stedid_seq'::regclass), stedsnavn text COLLATE pg_catalog.\"default\" NOT NULL, landid integer NOT NULL, CONSTRAINT sted_pkey PRIMARY KEY (stedid), CONSTRAINT unikt_sted UNIQUE (stedsnavn), CONSTRAINT sted_landid_fkey FOREIGN KEY (landid) REFERENCES public.land (landid) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION) WITH (OIDS = FALSE) TABLESPACE pg_default;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return createProcedureNewTownID();
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createViewApplication Creates the view "view_soknad" This requieres the table "soknad" (application) to be present.
 * @return True on success and false on failure
 */
bool psql::createViewApplication()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE OR REPLACE VIEW public.view_soknad AS SELECT soknad.soknadid, soknad.tittel, soknad.bedrift, soknad.soknadsfrist, soknad.stedid, sted.stedsnavn, sted.landid, land.land, soknad.statusid, status.status, soknad.motivasjon FROM soknad JOIN sted ON sted.stedid = soknad.stedid JOIN land ON land.landid = sted.landid JOIN status ON status.statusid = soknad.statusid ORDER BY soknad.soknadid;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createViewTowns Creates the view_sted. This requires the table "sted" (Town, City, place) to be present in the database.
 * @return True on success and false otherwise.
 */
bool psql::createViewTowns()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE OR REPLACE VIEW public.view_sted AS SELECT sted.stedid, sted.stedsnavn, sted.landid, land.land FROM sted JOIN land ON land.landid = sted.landid;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createSequenceApplicationIDSeq Creates the seqence for incrementing the application ID
 * @return True on success and false on failure
 */
bool psql::createSequenceApplicationIDSeq()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE SEQUENCE soknadid_seq";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createSequenceCountryIDSeq Creates the sequence for incrementing the country ID
 * @return True on success and false on failure
 */
bool psql::createSequenceCountryIDSeq()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE SEQUENCE landid_seq";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createSequenceStatusIDSeq Creates a sequence for increasing the status ID.
 * @return True on success and false on failure
 */
bool psql::createSequenceStatusIDSeq()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE SEQUENCE statusid_seq";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createSequenceTownIDSeq Creates the sequence for incrementing the town ID
 * @return True on success and false on failure
 */
bool psql::createSequenceTownIDSeq()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE SEQUENCE stedid_seq";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createFunctionEmptyText Creates a function that checks if iput is empty
 * @return True on success and false on failure
 */
bool psql::createFunctionEmptyText()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE OR REPLACE FUNCTION public.empty(text) RETURNS boolean LANGUAGE 'sql' COST 100 IMMUTABLE AS $BODY$ SELECT $1 ~ '^[[:space:]]*$'; $BODY$; COMMENT ON FUNCTION public.empty(text) IS 'Sjekke innholdet i en streng. Returnerer sann om strengen er tom eller bare inneholder mellomrom, og falsk ellers.';";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createProcedureNewApplicationID Creates a stored procedure that returns which is run when a new row is inserted in the application table
 * @return True on success and false otherwise
 */
bool psql::createProcedureNewApplicationID()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE FUNCTION public.nysoknadid() RETURNS trigger LANGUAGE 'plpgsql' COST 100 VOLATILE NOT LEAKPROOF AS $BODY$ BEGIN RAISE NOTICE 'Søknad med ID % ble lagt inn i databasen.', NEW.soknadid; RETURN NEW; END; $BODY$;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return createTriggerNewApplicationID();
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createProcedureUpdateApplication Creates a stored procedure that returns which is run when data in the application table is updated
 * @return True if the creation succeeds and false on failure
 */
bool psql::createProcedureUpdateApplication()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt =
                "CREATE FUNCTION updatesoknad() RETURNS trigger \n"
                "LANGUAGE plpgsql \n"
                "AS $$DECLARE \n"
            "counter_ integer := 0; \n"
            "tablename_ text := 'temptable'; \n"
            "oldStatus text; \n"
            "newStatus text; \n"
            "max int; \n"
            "updated boolean := false; \n"
            "BEGIN \n"
            "begin \n"
            "        --raise notice 'Creating table %', tablename_; \n"
            "        execute 'create temporary table ' || tablename_ || ' (counter integer) on commit drop'; \n"
            "        execute 'insert into ' || tablename_ || ' (counter) values(0)'; \n"
            "        execute 'select counter from ' || tablename_ into counter_; \n"
            "        --raise notice 'Actual value for counter= [%]', counter_; \n"
            "    exception \n"
            "        when duplicate_table then \n"
            "        null; \n"
            "    end; \n"
            "execute 'select counter from ' || tablename_ into counter_; \n"
            "    execute 'update ' || tablename_ || ' set counter = counter + 1'; \n"
            "   --raise notice 'updating'; \n"
            "    execute 'select counter from ' || tablename_ into counter_; \n"
            "    --raise notice 'Actual value for counter= [%]', counter_; \n"
            "    max := count(soknadid) from soknad; \n"
            "    if counter_ = max then \n"
            "        raise exception 'Kan ikke oppdatere mer enn én rad om gangen.'; \n"
            "    end if; \n"
            "if NEW.soknadid != OLD.soknadid \n"
            "then \n"
            "raise notice 'Søknadid-en ble endret fra % til %.', OLD.soknadid, NEW.soknadid; \n"
            "updated = true; \n"
            "end if; \n"
            "if NEW.tittel != OLD.tittel \n"
            "then \n"
            "raise notice 'Søknaden med ID % har fått endret tittel fra % til %.', OLD.soknadid, OLD.tittel, NEW.tittel; \n"
            "updated=true; \n"
            "end if; \n"
            "if NEW.bedrift != OLD.bedrift \n"
            "then \n"
            "raise notice 'Søknaden med ID % har fått endret bedrift fra % til %.', OLD.soknadid, OLD.bedrift, NEW.bedrift; \n"
            "updated=true; \n"
            "end if; \n"
            "if NEW.stedid != OLD.stedid \n"
            "then \n"
            "raise notice 'Søknaden med ID % har fått endret stedid fra % til %.', OLD.soknadid, OLD.stedid, NEW.stedid; \n"
            "updated=true; \n"
            "end if; \n"
            "if NEW.soknadsfrist != OLD.soknadsfrist \n"
            "then \n"
            "raise notice 'Søknaden med ID % har fått endret søknadsfrist fra % til %.', OLD.soknadid, OLD.soknadsfrist, NEW.soknadsfrist; \n"
            "updated = true; \n"
            "end if; \n"
            "if NEW.motivasjon != OLD.motivasjon \n"
            "then \n"
            "raise notice 'Søknaden med ID % har fått endret motivasjon fra % til %.', OLD.soknadid, OLD.motivasjon, NEW.motivasjon; \n"
            "updated = true; \n"
            "end if; \n"
            "if NEW.statusid != OLD.statusid \n"
            "then \n"
            "if OLD.statusid = 1 \n"
            "then \n"
            "oldStatus = 'Registrert'; \n"
            "elsif OLD.statusid = 2 \n"
            "then \n"
            "oldStatus = 'Sendt'; \n"
            "elsif OLD.statusid = 3 \n"
            "then \n"
            "oldStatus = 'Interessert, mulig intervju'; \n"
            "elsif OLD.statusid = 4 \n"
            "then \n"
            "oldStatus = 'Avvist'; \n"
            "elsif OLD.statusid = 5 \n"
            "then \n"
            "oldStatus = 'Søknad skrevet, men ikke sendt'; \n"
            "elsif OLD.statusid = 6 \n"
            "then \n"
            "oldStatus = 'Avvist etter intervju'; \n"
            "elsif OLD.statusid = 7 \n"
            "then \n"
            "oldStatus = 'Godtatt, klar for jobb'; \n"
            "end if; \n"
            "if NEW.statusid = 1 \n"
            "then \n"
            "newStatus = 'Registrert'; \n"
            "elsif NEW.statusid = 2 \n"
            "then \n"
            "newStatus = 'Sendt'; \n"
            "elsif NEW.statusid = 3 \n"
            "then \n"
            "newStatus = 'Interessert, mulig intervju'; \n"
            "elsif NEW.statusid = 4 \n"
            "then \n"
            "newStatus = 'Avvist'; \n"
            "elsif NEW.statusid = 5 \n"
            "then \n"
            "newStatus = 'Søknad skrevet, men ikke sendt'; \n"
            "elsif NEW.statusid = 6 \n"
            "then \n"
            "newStatus = 'Avvist etter intervju'; \n"
            "elsif NEW.statusid = 7 \n"
            "then \n"
            "newStatus = 'Godtatt, klar for jobb'; \n"
            "end if; \n"
            "raise notice 'Søknaden med ID % har fått endret statusid fra % (%) til % (%).', OLD.soknadid, OLD.statusid, oldStatus, NEW.statusid, newStatus; \n"
            "elsif NEW.statusid = OLD.statusid \n"
            "then \n"
            "if updated = false \n"
            "then \n"
            "if OLD.statusid = 1 \n"
            "then \n"
            "oldStatus = 'Registrert'; \n"
            "elsif OLD.statusid = 2 \n"
            "then \n"
            "oldStatus = 'Sendt'; \n"
            "elsif OLD.statusid = 3 \n"
            "then \n"
            "oldStatus = 'Interessert, mulig intervju'; \n"
            "elsif OLD.statusid = 4 \n"
            "then \n"
            "oldStatus = 'Avvist'; \n"
            "elsif OLD.statusid = 5 \n"
            "then \n"
            "oldStatus = 'Søknad skrevet, men ikke sendt'; \n"
            "elsif OLD.statusid = 6 \n"
            "then \n"
            "oldStatus = 'Avvist etter intervju'; \n"
            "elsif OLD.statusid = 7 \n"
            "then \n"
            "oldStatus = 'Godtatt, klar for jobb'; \n"
            "end if; \n"
            "raise notice 'Søknaden med ID % har IKKE fått endret status. Statusen forblir % (%).', OLD.soknadid, OLD.statusid, oldStatus; \n"
            "end if; \n"
            "end if; \n"
            "RETURN NEW; \n"
            "END; \n"
            "$$;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return createTriggerUpdateApplication();
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createProcedureNewCountryID Creates a stored procedure that returns which is run when a new row is inserted in the country table
 * @return True on success and false on failure
 */
bool psql::createProcedureNewCountryID()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE FUNCTION public.nylandid() RETURNS trigger LANGUAGE 'plpgsql' COST 100 VOLATILE NOT LEAKPROOF AS $BODY$ BEGIN RAISE NOTICE 'Landet % med ID % ble lagt inn i databasen.', NEW.land, NEW.landid;  RETURN NEW; END; $BODY$;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return createTriggerNewCountryID();
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createProcedureNewTownID Creates a stored procedure that returns which is run when a new row is inserted in the town table
 * @return True on success and false on failure
 */
bool psql::createProcedureNewTownID()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE FUNCTION public.nystedid() RETURNS trigger LANGUAGE 'plpgsql' COST 100 VOLATILE NOT LEAKPROOF AS $BODY$ BEGIN RAISE NOTICE 'Sted % med ID % ble lagt inn i databasen.', NEW.stedsnavn, NEW.stedid; RETURN NEW; END; $BODY$;";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return createTriggerNewTownID();
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createTriggerNewApplicationID Creates the trigger that executes the procedure "nysoknadid();"
 * @return True on success and false on failure
 */
bool psql::createTriggerNewApplicationID()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TRIGGER trg_nysoknad AFTER INSERT ON public.soknad FOR EACH ROW EXECUTE PROCEDURE public.nysoknadid();";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createTriggerUpdateApplication Creates the trigger that executes the procedure "updatesoknad();"
 * @return True on success and false on failure
 */
bool psql::createTriggerUpdateApplication()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TRIGGER trg_oppdatersoknad AFTER UPDATE  ON public.soknad FOR EACH ROW EXECUTE PROCEDURE public.updatesoknad();";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createTriggerNewCountryID Creates the trigger that executes the procedure "nylandid();"
 * @return True on success and false on failure
 */
bool psql::createTriggerNewCountryID()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TRIGGER trg_nyttland AFTER INSERT ON public.land FOR EACH ROW EXECUTE PROCEDURE public.nylandid();";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}

/**
 * @brief psql::createTriggerNewTownID Creates the trigger that executes the procedure "nystedid();"
 * @return True on success and false on failure
 */
bool psql::createTriggerNewTownID()
{
    try
    {
        pqxx::connection C("dbname = jobber user = " + username.toStdString() + " password = " + password.toStdString() + " hostaddr = " + host.toStdString() + " port = 5432");
        string statement = "";
        QString stmt = "CREATE TRIGGER trg_nyttsted AFTER INSERT ON public.sted FOR EACH ROW EXECUTE PROCEDURE public.nystedid();";
        ostringstream oss;
        oss << statement << stmt.toStdString();

        pqxx::work W(C);
        W.exec(oss.str());
        W.commit();
        C.disconnect();
        return true;
    }
    catch(std::exception &e)
    {
        setError(e.what());
        return false;
    }
}
