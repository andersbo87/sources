using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Npgsql;
using System.Threading;
using System.Net.Sockets;
using System.Data;
using System.Text;

/// <summary>
/// Summary description for psql
/// </summary>
/// <summary>
/// A class intended to store all SQL related commands
/// </summary>
public class psql
{
    private NpgsqlConnection conn;
    private NpgsqlCommand cmd;
    private NpgsqlDataReader reader;
    private String username, password;
    private HttpCookie hc;
    private List<string> data;
    private string server, database = "jobber";
    public string[] colNames;
    public psql()
    {
        // Do nothing
    }

    public string getString()
    {
        OperatingSystem os = Environment.OSVersion;
        Version version = os.Version;
        if (version.Major == 10)
            return "10";
        else
            return "versjon " + version.ToString();
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
        catch (NpgsqlException)
        {
            //MessageBox.Show("En PostgreSQL-feil har oppstått: " + ne.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            return false;
        }
        catch (SocketException )
        {
            //MessageBox.Show("En feil har oppstått under oppkobling mot en ekstern server: " + se.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            //Application.Exit(); // Avslutter programmet (det er jo ikke noen forbindelse med serveren lenger, så hvorfor fortsette?)
            return false;
        }
        catch (Exception )
        {
            //MessageBox.Show("En feil har oppstått: " + e.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            return false;
        }
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
                            //sb.Append(reader.GetName(i) + "\n");
                            res[i] = reader.GetName(i) + "\n";
                            j++;
                        }
                        else
                        {
                            res[i] = reader.GetName(i) + "\t";
                            //sb.Append(reader.GetName(i) + "\t");
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
        //ArrayList al = new ArrayList();
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
            //int i = 0;
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
                        //sb.AppendLine(reader.GetString(i) + "\n");
                        //i++;
                    }
                    else
                    {
                        res[i] = reader.GetString(i) + "\t";
                        //sb.Append(reader.GetString(i) + "\t");
                    }
                    //res[i] = sb.ToString();
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
            return npe.Message; // Just return the error message (it gets printed to the text box in SQLCommands.cs anyway)...
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
    public string getServer()
    {
        return server;
    }

    /// <summary>
    /// Inserts a new status to the database.
    /// </summary>
    /// <param name="status">The new status</param>
    /// <returns>True if the insert succeeds and false if it fails</returns>
    public bool InsertStatus(string status)
    {
        //try
        //{
            Init();
            cmd = new NpgsqlCommand("INSERT INTO status (status) VALUES('" + status + "');", conn);
            cmd.ExecuteNonQuery();
            
            return true;
        /*}
        catch (NpgsqlException ne)
        {
            setError(ne.Message);
            return false;
        }
        catch (Exception e)
        {
            setError(e.Message);
            return false;
        }
        finally
        {
            conn.Close();
        }*/
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
        catch (NpgsqlException ne)
        {
            setError(ne.Message);
            return false;
        }
        catch (Exception e)
        {
            setError(e.Message);
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
        catch (NpgsqlException ne)
        {
            setError(ne.Message);
            return false;
        }
        catch (Exception e)
        {
            setError(e.Message);
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
    public bool InsertApplication(string title, string company, int placeID, int statusID, string date)
    {
        Init();
        try
        {
            cmd = new NpgsqlCommand("INSERT INTO soknad (tittel, bedrift, stedid, statusid, soknadsfrist) VALUES('" + title + "', '" + company + "'," + placeID + ", " + statusID + ", '" + date + "');", conn);
            cmd.ExecuteNonQuery();

            return true;
        }
        catch (NpgsqlException ne)
        {
            setError(ne.Message);
            return false;
        }
        catch (Exception e)
        {
            setError(e.Message);
            return false;
        }
        finally
        {
            conn.Close();
        }
    }
    public List<string> GetApplications(int index)
    {
        //try
        //{
        Init();
        cmd = new NpgsqlCommand();
        List<string> data = new List<string>();
        cmd.Connection = conn;
        //cmd.CommandText = "SELECT tittel, bedrift, soknadsfrist, stedid, stedsnavn, landid, land, statusid, status FROM view_soknad WHERE soknadid = " + index;
        cmd.CommandText = "SELECT tittel, bedrift, stedid, sted, landid, land, statusid, status, soknadsfrist, motivasjon FROM view_soknad WHERE soknadid=" + index;
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
            data.Add(reader.GetString(9)); // Motivasjon
        }
        conn.Close();
        return data;
        /*}
        catch(NpgsqlException)
        {
            return null;
        }*/
    }

    /// <summary>
    /// Henter alle registrerte statuser i databasen basert på statusid.
    /// </summary>
    /// <param name="index">ID-en til den aktuelle statusen.</param>
    /// <returns>Informasjon om den aktuelle statusen: StatusID og navnet på statusen.</returns>
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
    /// Henter all data om en innlagt by i databasen basert på stedid.
    /// </summary>
    /// <param name="index">ID-en til det aktuelle stedet.</param>
    /// <returns>Informasjon om den aktuelle byen, stedid, navn, landid og landnavn i liste.</returns>
    public List<string> GetCities(int index)
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

    /// <summary>
    /// Henter en liste over land som er innlagt i databasen
    /// </summary>
    /// <param name="index"></param>
    /// <returns>Liste over alle land i databasen</string></returns>
    public List<string> GetCountries(int index)
    {
        List<string> data = new List<string>();
        using(NpgsqlConnection loconn = new NpgsqlConnection("Host=localhost;Username=" + username + ";Password=" + password + ";Database=" + database))
        {
            loconn.Open();
            NpgsqlCommand nc = new NpgsqlCommand("SELECT * FROM land WHERE landid = " + index, loconn);
            //cmd.CommandText = "SELECT * FROM land WHERE landid = " + index;
            reader = nc.ExecuteReader();
            while (reader.Read())
            {
                data.Add(reader.GetString(0));
                data.Add(reader.GetString(1));
            }
            reader.Close();
        }
        /*Init();
        List<string> data = new List<string>();
        cmd = new NpgsqlCommand("SELECT * FROM land WHERE landid = " + index, conn);
        /*cmd.Connection = conn;
        cmd.CommandText = "SELECT * FROM land WHERE landid = " + index;*/
        /*reader = cmd.ExecuteReader();
        while (reader.Read())
        {
            data.Add(reader.GetString(0));
            data.Add(reader.GetString(1));
        }
        conn.Close();*/
        return data;
    }

    /// <summary>
    /// Henter StedID basert på angitt søknadid.
    /// </summary>
    /// <param name="index">ID-en til søknaden som inneholder den korrekte StedID.</param>
    /// <returns>StedID (heltall) basert på angitt søknadid.</returns>
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
    /// Henter bynavnet basert på angitt stedid.
    /// </summary>
    /// <param name="index">ID-en til det aktuelle stedet.</param>
    /// <returns>Bynavnet basert på den angitte ID-en</returns>
    public string getCityName(int index)
    {
        string res = "";
        Init();
        cmd = new NpgsqlCommand("SELECT stedsnavn FROM sted WHERE stedid=" + index + " ORDER BY stedid asc;", conn);
        reader = cmd.ExecuteReader();
        while (reader.Read())
            res = reader.GetString(0);
        return res;
    }
    /// <summary>
    /// Henter statusen basert på angitt statusid
    /// </summary>
    /// <param name="index">ID-en til statusen brukeren er ute etter</param>
    /// <returns>Statusnavnet basert på statusID-en</returns>
    public string getStatusName(int index)
    {
        string res = "";
        Init();
        cmd = new NpgsqlCommand("SELECT status FROM status WHERE statusid=" + index + " ORDER BY statusid asc;", conn);
        reader = cmd.ExecuteReader();
        while (reader.Read())
            res = reader.GetString(0);
        return res;
    }

    /// <summary>
    /// Henter ID-en til det aktuelle landet.
    /// </summary>
    /// <param name="index">ID-en til søknaden som inneholder LandID-en</param>
    /// <returns>LandID-en basert på søknadsID-en</returns>
    public int GetCountryID(int index)
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
    /// Henter navnet til det aktuelle landet
    /// </summary>
    /// <param name="index">ID-en til landet brukeren er ute etter</param>
    /// <returns>Navnet til det aktuelle landet.</returns>
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
    /// Henter statusID-en for gjeldende søknad.
    /// </summary>
    /// <param name="index">Gjeldende søknadID.</param>
    /// <returns>StatusID-for gjeldende søknad</returns>
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
    /// Updates a record in the database
    /// </summary>
    /// <param name="table">Name of the table where the update is to take place</param>
    /// <param name="columnToBeUpdated">Name of the column where the update is to take place</param>
    /// <param name="value">The new value</param>
    /// <param name="tableID">The column with the primary key of the table (stedid, landid, statusid)</param>
    /// <param name="index">The primary key index where the update is to take place</param>
    public bool UpdateDatabase(string table, string columnToBeUpdated, int value, string tableID, int index)
    {
        try
        {
            Init();
            cmd.Connection = conn;
            cmd.CommandText = "UPDATE " + table + " SET " + columnToBeUpdated + " = " + value + " WHERE " + tableID + " = " + index;
            cmd.ExecuteNonQuery();
            return true;
        }
        catch (NpgsqlOperationInProgressException)
        {
            return false;
        }
        catch (NpgsqlException )
        {
            return false;
        }
        catch (Exception)
        {
            return false;
        }

        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Updates a record in the database
    /// </summary>
    /// <param name="table">Name of the table where the update is to take place</param>
    /// <param name="columnToBeUpdated">Name of the column where the update is to take place</param>
    /// <param name="value">The new value</param>
    /// <param name="tableID">The column with primary key of the table (stedid, landid, statusid)</param>
    /// <param name="index">The primary index where the update is to take place</param>
    public bool UpdateDatabase(string table, string columnToBeUpdated, string value, string tableID, int index)
    {
        try
        {
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "UPDATE " + table + " SET " + columnToBeUpdated + " = '" + value + "' WHERE " + tableID + " = " + index;
            cmd.ExecuteNonQuery();
            return true;
        }
        catch (NpgsqlOperationInProgressException)
        {
            return false;
        }
        catch (NpgsqlException )
        {
            return false;
        }
        catch (Exception )
        {
            return false;
        }

        finally
        {
            conn.Close();
        }
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
        catch (NpgsqlOperationInProgressException noipex)
        {
            setError(noipex.Message);
            return false;
        }
        catch (NpgsqlException ne)
        {
            setError(ne.Message);
            return false;
        }

        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Updates information about a registered country.
    /// </summary>
    /// <param name="countryID">The old ID of the country to be updated</param>
    /// <param name="newCountryID">The new ID of the country to be updated. Must be unique.</param>
    /// <param name="countryName">The new country name</param>
    /// <returns>True on success and false on failure</returns>
    public bool updateCountry(int countryID, int newCountryID, string countryName)
    {
        try
        {
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "UPDATE land SET landid=" + newCountryID + ", land='" + countryName + "' WHERE landid=" + countryID;
            cmd.ExecuteNonQuery();
            return true;
        }
        catch(Exception ex)
        {
            setError(ex.Message);
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

        finally
        {
            conn.Close();
        }
    }
}