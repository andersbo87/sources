using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class oppdaterland : System.Web.UI.Page
{
    psql p;
    int max, c;
    List<string> l;
    HttpCookie hc;
    bool checkCookies()
    {
        bool res = false;
        if (Request.Cookies["auth"] != null)
        {
            hc = Request.Cookies["auth"];
            res = true;
        }
        return res;
    }
    void getData(int index)
    {
        try
        {
            checkCookies();
            /*p.SetUsername(hc.Values["brukernavn"]);
            p.SetPassword(hc.Values["passord"]);
            p.SetServer("localhost");*/
            errorLabel.Text = p.getServer();
            List<string> country = p.GetCountries(index);
            countryID.Text = country.ElementAt(0);
            countryName.Text = country.ElementAt(1);
            countryDropDownList.Text = index.ToString();
        }
        catch (Exception ex)
        {
            errorLabel.Visible = true;
            errorLabel.Text = ex.ToString();
        }
    }
    protected void Page_Load(object sender, EventArgs e)
    {
        if (p == null)
        {
            // Sjekke og se om brukeren forsøker å få tilgang til denne siden uten å logge seg inn.
            // Dersom alt er i sin skjønneste orden:
            if (checkCookies())
            {
                p = new psql(); // Oppretter en ny peker til objektet
                p.SetUsername(hc.Values["brukernavn"]); // Legger inn det brukernavnet brukeren anga under innlogging
                p.SetPassword(hc.Values["passord"]); // Legger inn passordet brukeren oppga under innlogging
                p.SetServer("localhost");
            }
            else // Hvis det viser seg at brukeren ikke er innlogget eller at "kakebiten" er slettet, ...
                Response.Redirect("~/login.aspx"); // ... la oss redirigere brukeren til innloggingssiden
            labelInfo.Text = "Informasjonen på denne siden hentes fra en PostgreSQL-database på Windows " + p.getString();
        }
        if (!IsPostBack)
        {
            if (checkCookies())
            {
                p = new psql();
                p.SetUsername(hc.Values["brukernavn"]);
                p.SetPassword(hc.Values["passord"]);
                p.SetServer("localhost");
                labelInfo.Text = "Informasjonen på denne siden hentes fra en PostgreSQL-database på Windows " + p.getString();
                try
                {
                    l = p.GetData("SELECT * FROM land ORDER BY landid asc", 0);
                    int i = 0;
                    while (i < l.Count)
                    {
                        countryDropDownList.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(countryDropDownList.Items[countryDropDownList.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(countryDropDownList.Items[0].ToString()));
                        c++;
                    }
                }
                catch (Exception ex)
                {
                    errorLabel.Visible = true;
                    errorLabel.Text = "Noe er galt: " + ex.Message;
                }
            }
        }
    }

    protected void countryDropDownList_SelectedIndexChanged(object sender, EventArgs e)
    {
        int index = int.Parse(countryDropDownList.Text);
        getData(index);
    }

    private bool checkData()
    {
        bool res = true;
        if(countryID.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = "LandID-en må bestå av minst ett siffer.";
            return false;
        }
        if(countryName.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = errorLabel.Text + "Landnavnet må bestå av minst ett siffer.";
        }
        return res;
    }

    protected void btnUpdate_Click(object sender, EventArgs e)
    {
        if(checkData())
        {
            if(p.updateCountry(int.Parse(countryDropDownList.Text), int.Parse(countryID.Text), countryName.Text))
            {
                errorLabel.Visible = false;
                successLabel.Visible = true;
                successLabel.Text = "Oppdatering vellykket. Nye verdier:\nLandID: " + countryID.Text + "\n: Landnavn: " + countryName.Text;
            }
            else
            {
                errorLabel.Visible = true;
                successLabel.Visible = false;
                errorLabel.Text = "Noe har gått galt: " + p.getError();
            }
        }
    }
    [WebMethod]
    public static string YesModClick(object sender, EventArgs e)
    {
        string strToRtn = "";
        // The code that you want to execute when the user clicked yes goes here
        return strToRtn;
    }

    protected void btnDelete_Click(object sender, EventArgs e)
    {
        btnCancel.Visible = false;
        btnDelete.Visible = false;
        btnUpdate.Visible = false;
        countryIDLabel.Visible = false;
        countryNameLabel.Visible = false;
        countryID.Visible = false;
        countryName.Visible = false;
        countryDropDownList.Visible = false;
        labelRemoveData.Visible = true;
        labelRemoveData.Text = "Du er i ferd med å fjerne følgende data:<br />LandID: " + countryDropDownList.Text + "<br />Land: " + countryName.Text + "<br /><br />Dette kan du ikke angre på. Er du sikker på at du vil fortsette?";
        Button1.Visible = true;
        Button2.Visible = true;
    }

    protected void Button2_Click(object sender, EventArgs e)
    {
        btnCancel.Visible = true;
        btnDelete.Visible = true;
        btnUpdate.Visible = true;
        countryIDLabel.Visible = true;
        countryNameLabel.Visible = true;
        countryID.Visible = true;
        countryName.Visible = true;
        countryDropDownList.Visible = true;
        labelRemoveData.Visible = false;
        labelRemoveData.Text = "";
        Button1.Visible = false;
        Button2.Visible = false;
    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        if(p.DeleteItem("land","landid",int.Parse(countryDropDownList.Text)))
        {
            errorLabel.Visible = false;
            successLabel.Visible = true;
            successLabel.Text = "Landet ble fjernet fra databasen.";
            btnCancel.Visible = true;
            btnDelete.Visible = true;
            btnUpdate.Visible = true;
            countryIDLabel.Visible = true;
            countryNameLabel.Visible = true;
            countryID.Visible = true;
            countryName.Visible = true;
            countryDropDownList.Visible = true;
            labelRemoveData.Visible = false;
            labelRemoveData.Text = "";
            Button1.Visible = false;
            Button2.Visible = false;
        }
        else
        {
            successLabel.Visible = false;
            errorLabel.Visible = true;
            errorLabel.Text = "Noe har gått galt: " + p.getError();
        }
    }
    void refillList()
    {
        countryDropDownList.Items.Clear();
        try
        {
            l = p.GetData("SELECT * FROM land ORDER BY landid asc", 0);
            int i = 0;
            while (i < l.Count)
            {
                countryDropDownList.Items.Add(l.ElementAt(i));
                i++;
            }
            max = Int32.Parse(countryDropDownList.Items[countryDropDownList.Items.Count - 1].ToString());
            if (c == 0)
            {
                getData(Int32.Parse(countryDropDownList.Items[0].ToString()));
                c++;
            }
        }
        catch (Exception ex)
        {
            errorLabel.Visible = true;
            errorLabel.Text = "Noe er galt: " + ex.Message;
        }
    }
}