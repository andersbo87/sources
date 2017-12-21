/*
 * Copyright (c) 2017, Anders Bolt-Evensen
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Anders Bolt-Evensen BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


using System;
using System.Collections.Generic;
using System.Text;
using Npgsql;
using System.Threading;
using System.Data;
using System.Net.Sockets;
using System.IO;

namespace JobbWPF
{
    class pgsql
    {
        private NpgsqlConnection conn;
        private NpgsqlCommand cmd;
        private NpgsqlDataReader reader;
        private String username, password;
        private List<string> data;
        private string server, database = "jobber";
        private int record;
        //public string[] colNames;
        private string title;
        public pgsql(string newTitle)
        {
            title = newTitle;
        }

        /// <summary>
        /// Initializes the database
        /// </summary>
        public bool Init()
        {
            try
            {
                conn = new NpgsqlConnection("Host=" + server + ";Username=" + username + ";Password=" + password + ";Database=" + database);
                conn.Open();
                cmd = new NpgsqlCommand();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                throw ne; // Kaster unntaket videre. Normalt sett vil dette kun påvirke koden i connectPgsql.cs
            }
            catch (SocketException se)
            {
                setError(se.Message);
                throw se; // Kaster unntaket videre. Normalt sett vil dette kun påvirke koden i connectPgsql.cs, med mindre den eksterne serveren kobles fra.
            }
            catch(TimeoutException te)
            {
                throw te;
            }
            catch (Exception e)
            {
                setError(e.Message);
                throw e; // Kaster unntaket videre. Normalt sett vil dette kun påvirke koden i connectPgsql.cs, med mindre den eksterne serveren kobles fra.
            }
        }
        public void setRecord(int newRecord)
        {
            record = newRecord;
        }
        public int getRecord()
        {
            return record;
        }
        string errMsg;
        public string getError()
        {
            return errMsg;
        }
        public void setError(string newErrMsg)
        {
            errMsg = newErrMsg;
        }

        public string[] GetTitle(string sqlQuery)
        {
            string[] res = null;
            Init();
            cmd = new NpgsqlCommand(sqlQuery);
            cmd.Connection = conn;
            NpgsqlDataAdapter nad = new NpgsqlDataAdapter(cmd);
            DataTable dt = new DataTable();
            int rows = nad.Fill(dt);
            if (sqlQuery.ToLower().StartsWith("select"))
            {
                reader = cmd.ExecuteReader();
                int j = 0;
                while (reader.Read())
                {
                    int i = 0;
                    res = new string[reader.FieldCount];
                    while (i < reader.FieldCount)
                    {
                        if (j == 0)
                        {
                            if (i == reader.FieldCount - 1)
                            {
                                res[i] = reader.GetName(i) + "\n";
                                j++;
                            }
                            else
                            {
                                res[i] = reader.GetName(i) + "\t";
                            }

                        }
                        i++;
                    }
                    return res;
                }
            }
            return res;
        }

        public string[] Exec(string sqlQuery)
        {
            StringBuilder sb = new StringBuilder();
            string[] res = null;
            Init();
            cmd = new NpgsqlCommand(sqlQuery);
            cmd.Connection = conn;
            NpgsqlDataAdapter nad = new NpgsqlDataAdapter(cmd);
            DataTable dt = new DataTable();
            int rows = nad.Fill(dt);
            if (sqlQuery.ToLower().StartsWith("select"))
            {
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    res = new string[rows];
                    int i = 0, j = 0;
                    while (i < reader.FieldCount)
                    {
                        if (j == 0)
                        {
                            if (i == reader.FieldCount - 1)
                            {
                                sb.Append(reader.GetName(i) + "\n");
                                j++;
                            }
                            else
                            {
                                sb.Append(reader.GetName(i) + "\t");
                            }
                        }
                        i++;
                    }
                    i = 0;
                    while (i < reader.FieldCount)
                    {

                        if (i == reader.FieldCount - 1)
                        {
                            res[i] = reader.GetString(i) + "\n";
                        }
                        else
                        {
                            res[i] = reader.GetString(i) + "\t";
                        }
                        i++;
                    }
                    return res;
                }
            }
            return res;
        }

        /// <summary>
        /// Executes an SQL query. This is only intended to be run from SQLCommands.cs.
        /// </summary>
        /// <param name="sqlQuery">The query to be executed.</param>
        /// <returns></returns>
        public string ExecQry(string sqlQuery)
        {
            try
            {
                string res = "";
                StringBuilder sb = new StringBuilder();
                Init();
                cmd = new NpgsqlCommand(sqlQuery);
                cmd.Connection = conn;
                NpgsqlDataAdapter nad = new NpgsqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                int rows = nad.Fill(dt);
                if (sqlQuery.StartsWith("select"))
                {
                    int j = 0;
                    reader = cmd.ExecuteReader();
                    while (reader.Read())
                    {
                        int i = 0;
                        while (i < reader.FieldCount)
                        {
                            if (j == 0)
                            {
                                if (i == reader.FieldCount - 1)
                                {
                                    sb.AppendLine(reader.GetName(i) + "\n");
                                    j++;
                                }
                                else
                                {
                                    sb.Append(reader.GetName(i) + " \t | ");
                                }
                            }
                            i++;
                        }
                        i = 0;
                        while (i < reader.FieldCount)
                        {

                            if (i == reader.FieldCount - 1)
                                sb.AppendLine(reader.GetString(i) + "\n");
                            else
                                sb.Append(reader.GetString(i) + " \t | ");
                            i++;
                        }
                    }
                    res = sb.ToString() + "\n(" + rows.ToString() + " rader)";
                }
                else if (sqlQuery.StartsWith("explain"))
                {
                    int j = 0;
                    reader = cmd.ExecuteReader();
                    while (reader.Read())
                    {
                        int i = 0;
                        while (i < reader.FieldCount)
                        {
                            if (j == 0)
                            {
                                if (i == reader.FieldCount - 1)
                                {
                                    sb.AppendLine(reader.GetName(i) + "\n");
                                    j++;
                                }
                                else
                                {
                                    sb.Append(reader.GetName(i) + "\t");
                                }
                            }
                            i++;
                        }
                        i = 0;
                        while (i < reader.FieldCount)
                        {

                            if (i == reader.FieldCount - 1)
                                sb.AppendLine(reader.GetString(i) + "\n");
                            else
                                sb.Append(reader.GetString(i) + "\t");
                            i++;
                        }
                    }
                    res = sb.ToString() + "\n(" + rows.ToString() + " rader)";
                }
                else
                {
                    sb.AppendLine(cmd.ExecuteNonQuery() + " rader ble endret.");
                }
                res = sb.ToString();
                return res;
            }
            catch (NpgsqlException npe)
            {
                return npe.Message;
            }

            finally
            {
                conn.Close();
            }
        }


        /// <summary>
        /// Returns the username.
        /// </summary>
        /// <returns>The PostgreSQL username</returns>
        public String GetUsername()
        {
            return username;
        }
        /// <summary>
        /// Returns the PostgreSQL password
        /// </summary>
        /// <returns>The PostgreSQL password</returns>
        public String GetPassword()
        {
            return password;
        }
        /// <summary>
        /// Sets the password to be used when attempting to connect to the PostgreSQL server.
        /// </summary>
        /// <param name="newPassword"></param>
        public void SetPassword(String newPassword)
        {
            password = newPassword;
        }

        /// <summary>
        /// Sets the username to be used when attempting to connect to the PostgreSQL server.
        /// </summary>
        /// <param name="newUsername"></param>
        public void SetUsername(String newUsername)
        {
            username = newUsername;
        }
        public void SetServer(string newServer)
        {
            server = newServer;
        }

        /// <summary>
        /// Inserts a new status to the database.
        /// </summary>
        /// <param name="status">The new status</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertStatus(string status)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand("INSERT INTO status (status) VALUES('" + status + "');", conn);
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke sette inn den nye statusen. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn den nye statusen. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn den nye statusen. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Inserts a new town to the database
        /// </summary>
        /// <param name="townName">The name of the town</param>
        /// <param name="countryID">The ID of the country where the town is located</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertTown(string townName, int countryID)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand("INSERT INTO sted (stedsnavn, landid) VALUES('" + townName + "', " + countryID + ");", conn);
                cmd.ExecuteNonQuery();
                return true;
            }
            catch(SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch(TimeoutException te)
            {
                setError("Kan ikke sette inn den nye byen/stedet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn den nye byen/stedet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn den nye byen/stedet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Setter inn et nytt navn i databasen.
        /// </summary>
        /// <param name="countryName">Navnet på det nye landet. Må være unikt.</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertCountry(string countryName)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand("INSERT INTO land (land) VALUES('" + countryName + "');", conn);
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke sette inn det nye landet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn det nye landet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn det nye landet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Inserts a new job "application" into the database.
        /// </summary>
        /// <param name="title">The title of the job</param>
        /// <param name="company">The company that offers the job</param>
        /// <param name="placeID">int: The ID of the city where the job is located.</param>
        /// <param name="countryID">int: The ID of the country where the job is located.</param>
        /// <param name="statusID">int: The status of the job application</param>
        /// <param name="date">The deadline for when the application has to be sent.</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertApplication(string title, string company, int townID, int statusID, string date)
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand("INSERT INTO soknad (tittel, bedrift, stedid, statusid, soknadsfrist) VALUES('" + title + "', '" + company + "'," + townID + ", " + statusID + ", '" + date + "');", conn);
                cmd.ExecuteNonQuery();

                return true;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke sette inn den nye søknaden. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn den nye søknaden. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn den nye søknaden. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Builds a list of strings containing all data about a given job application.
        /// </summary>
        /// <param name="index">The application ID</param>
        /// <returns>A list of string that contains all information about the current job.</returns>
        public List<string> GetApplications(int index)
        {
            Init();
            cmd = new NpgsqlCommand();
            List<string> data = new List<string>();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT tittel, bedrift, stedid, stedsnavn, landid, land, statusid, status, soknadsfrist FROM view_soknad WHERE soknadid = " + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                data.Add(reader.GetString(0)); // Title
                data.Add(reader.GetString(1)); // Bedrift
                data.Add(reader.GetString(2)); // Stedid
                data.Add(reader.GetString(3)); // Sted (by)
                data.Add(reader.GetString(4)); // LandID
                data.Add(reader.GetString(5)); // Land
                data.Add(reader.GetString(6)); // StatusID
                data.Add(reader.GetString(7)); // Status
                data.Add(reader.GetString(8)); // Soknadsfrist
            }
            conn.Close();
            return data;
        }

        /// <summary>
        /// Fetches the company name based on the application ID.
        /// </summary>
        /// <param name="appID">The ID of the application in question.</param>
        /// <returns>A string with the company name.</returns>
        public string getCompany(int appID)
        {
            string res = "";
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT bedrift FROM soknad WHERE soknadid = " + appID + "ORDER BY statusid asc";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res = reader.GetString(0);
            return res;
        }

        /// <summary>
        /// Builds a list of statuses based on the status ID.
        /// </summary>
        /// <param name="index">The Status ID.</param>
        /// <returns>A list of strings with all information about the status.</returns>
        public List<string> GetStatuses(int index)
        {
            Init();
            List<string> data = new List<string>();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT * FROM status WHERE statusid = " + index + "ORDER BY statusid asc";
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                data.Add(reader.GetString(0));
                data.Add(reader.GetString(1));
            }
            conn.Close();
            return data;
        }

        /// <summary>
        /// Builds a list with all data about a city based of the ID.
        /// </summary>
        /// <param name="index">The city/town ID.</param>
        /// <returns>A list with all information about the city.</returns>
        public List<string> GetCities(int index)
        {
            try
            {
                Init();
                List<string> data = new List<string>();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT * FROM view_sted WHERE stedid = " + index;
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    data.Add(reader.GetString(0));
                    data.Add(reader.GetString(1));
                    data.Add(reader.GetString(2));
                    data.Add(reader.GetString(3));
                }
                conn.Close();
                return data;
            }
            catch(NpgsqlException ne)
            {
                setError(ne.Message);
                throw ne;
            }
            catch(Exception e)
            {
                setError(e.ToString());
                throw e;
            }
        }

        /// <summary>
        /// Builds a list with all information about the country based on its ID.
        /// </summary>
        /// <param name="index">The ID of the country in question</param>
        /// <returns>The list with the country data.</returns>
        public List<string> GetCountries(int index)
        {
            Init();
            List<string> data = new List<string>();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT * FROM land WHERE landid = " + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                data.Add(reader.GetString(0));
                data.Add(reader.GetString(1));
            }
            conn.Close();
            return data;
        }

        /// <summary>
        /// Get the ID of a city based on the application ID
        /// </summary>
        /// <param name="index">The ID of the application in question.</param>
        /// <returns>The town ID</returns>
        public int GetCityID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT stedid FROM view_soknad WHERE soknadid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the name of a city based on the qunique city ID.
        /// </summary>
        /// <param name="index">The index of the city in question</param>
        /// <returns>The name of the city as a string.</returns>
        public string getCityName(int index)
        {
            string res = "";
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT stedsnavn FROM STED where stedid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res = reader.GetString(0);
            conn.Close();
            return res;
        }

        /// <summary>
        /// Gets the country ID of a given application.
        /// </summary>
        /// <param name="index">The ID of the application in question.</param>
        /// <returns>The ID of the country.</returns>
        public int GetApplicationCountryID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM view_soknad WHERE soknadid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the ID of the country from the view "sted" (=town/place) based on the town ID.
        /// </summary>
        /// <param name="index">The ID of the town in question.</param>
        /// <returns>A number with the ID of the country.</returns>
        public int GetCityCountryID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM view_sted WHERE stedid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the name of a country based on the provided ID.
        /// </summary>
        /// <param name="index">The ID of the country.</param>
        /// <returns>A string with the name of the country</returns>
        public string GetCountryName(int index)
        {
            string res = "";
            try
            {
                Init();
                cmd = new NpgsqlCommand("SELECT land FROM land WHERE landid=" + index + ";", conn);
                reader = cmd.ExecuteReader();
                while (reader.Read())
                    res = reader.GetString(0);
                return res;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return null;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Gets the status ID based on the given parameter
        /// </summary>
        /// <param name="index">The application ID where the required status ID exists.</param>
        /// <returns>The required status ID.</returns>
        public int GetStatusID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT statusID from view_soknad WHERE soknadid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                ans = reader.GetInt32(0);
            }
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the name of a status based on the parameter provided by the user.
        /// </summary>
        /// <param name="idx">The ID of the status in question.</param>
        /// <returns>A string containing the status name.</returns>
        public string getStatusName(int idx)
        {
            string res = "";
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT status FROM status WHERE statusid=" + idx;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res = reader.GetString(0);
            conn.Close();
            return res;
        }
        
        /// <summary>
        /// Updates an existing job application.
        /// </summary>
        /// <param name="appID">The ID of the job application to be updated.</param>
        /// <param name="newAppTitle">The new application title.</param>
        /// <param name="newCompany">The new company name.</param>
        /// <param name="newTownID">The new ID of the town where the job is located.</param>
        /// <param name="newStatusID">The new status ID. 1=Registered, 2=Sent, 3=Interested, possible interview, 4=Declined/Rejected, 5=Application written but not sent, 6=Job accepted.</param>
        /// <param name="newDeadline">The new application deadline.</param>
        /// <returns>True on success and false on failure.</returns>
        public bool updateApplication(int appID, string newAppTitle, string newCompany, int newTownID, int newStatusID, string newDeadline)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE soknad SET tittel='" + newAppTitle + "', bedrift='" +newCompany + "', stedID=" + newTownID + ", statusID=" + newStatusID + ", soknadsfrist='" + newDeadline + "' where soknadid=" + appID + ";";
                cmd.ExecuteNonQuery();
                
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Updates an element in the table country
        /// </summary>
        /// <param name="countryID">The ID of the country to be updated.</param>
        /// <param name="newCountryName">The new name of the country.</param>
        /// <returns>True on success and false on failure.</returns>
        public bool updateCountry(int countryID, string newCountryName)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE land SET landnavn='" + newCountryName + "' where landid=" + countryID + ";";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Updates an existing status in the database.
        /// </summary>
        /// <param name="statusID">The unique identification number of the status to be updated</param>
        /// <param name="newStatusName">The new status name.</param>
        /// <returns>True on success and false on failure.</returns>
        public bool updateStatus(int statusID, string newStatusName)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE status SET status='" + newStatusName + "' where statusid=" + statusID + ";";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Updates a town that already exists in the database.
        /// </summary>
        /// <param name="townID">The ID of the town to be updated.</param>
        /// <param name="newTownName">The new name of the town/city.</param>
        /// <returns></returns>
        public bool updateTown(int townID, string newTownName)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE sted SET stedsnavn='" + newTownName + "' where stedid=" + townID + ";";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Deletes an item from the database
        /// </summary>
        /// <param name="table">The table where the item is located</param>
        /// <param name="columnName">The name of the column where the item to be deleted is located</param>
        /// <param name="index">The index (number) of the item to be deleted.</param>
        public bool DeleteItem(string table, string columnName, int index)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "DELETE FROM " + table + " WHERE " + columnName + " = " + index;
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                //MessageBox.Show("Kan ikke fjerne elementet: " + noipe.ToString(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                setError(noipe.Message);
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke fjerne elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke fjerne elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke fjerne elementet. Feilmelding: " + e.Message);
                return false;
            }

            finally
            {
                conn.Close();
            }
        }

        public List<string> GetData(string sqlQuery, int index)
        {
            Init();
            cmd = new NpgsqlCommand();
            try
            {
                data = new List<string>();
                cmd.Connection = conn;
                cmd.CommandText = sqlQuery;
                using (var rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        data.Add(rdr.GetString(index));
                    }
                }
                return data;
            }
            catch (NpgsqlOperationInProgressException)
            {
                Thread.Sleep(1000);
                GetData(sqlQuery, index);
                return null;
            }
            catch(Npgsql.NpgsqlException npe)
            {
                setError(npe.Message);
                throw npe;
            }

            finally
            {
                conn.Close();
            }
        }

        /*
         * Følgende kode er hentet fra QT-utgaven av samme program.
         * Funksjonen under brukes til å generere data om spesifikke søknader.
         * Koden i QT-utgaven brukes til å generere én kolonne per metode, men her bygges hele lista opp i én metode.
         */
        
        public List<jobb> getSpecificJobs(string jobTitle, string companyName, string cityName, string status, string deadline)
        {
            List<jobb> data = new List<jobb>();
            try
            {
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                int i = 0;
                string s = "SELECT soknadid, tittel, bedrift, stedsnavn, status, soknadsfrist FROM view_soknad WHERE tittel like '%" + jobTitle + "%' and bedrift like '%" + companyName + "%' ";
                if (string.Compare(cityName, "", false) != 0)
                    s = s + "and stedsnavn like '%" + cityName + "%' ";
                if (string.Compare(status, "", false) != 0)
                    s = s + "and status like '%" + status + "%' ";
                s = s + "and soknadsfrist like '%" + deadline + "%' order by soknadid;";
                cmd.CommandText = s;
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    data.Add(new jobb() { applicationID = reader.GetInt32(0), jobTitle = reader.GetString(1), company = reader.GetString(2), cityName = reader.GetString(3), statusName = reader.GetString(4), deadline = reader.GetString(5) });
                    i++;
                }
                setRecord(i);
                conn.Close();
                return data;
            }
            catch(TimeoutException te)
            {
                throw te;
            }
            catch(SocketException se)
            {
                throw se;
            }
            catch(NpgsqlException ne)
            {
                throw ne;
            }
            catch(Exception e)
            {
                throw e; // Kaster bare feilen videre.
            }
        }
    }
}
