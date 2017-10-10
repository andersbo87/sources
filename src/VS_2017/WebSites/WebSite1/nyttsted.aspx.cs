using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class nyttsted : System.Web.UI.Page
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
    protected void Page_Load(object sender, EventArgs e)
    {
        // Sjekke om objektet har en referanseverdi, eller om det er en "tom" peker.
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
                        dropDownCountryID.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(dropDownCountryID.Items[dropDownCountryID.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(dropDownCountryID.Items[0].ToString()));
                        c++;
                    }
                }
                catch (Exception ex)
                {
                    errorLabel.Visible = true;
                    successLabel.Visible = false;
                    errorLabel.Text = "Noe er galt: " + ex.Message;
                    dropDownCountryID.Visible = false;
                }
            }
            else
            {
                Response.Redirect("login.aspx");
            }
        }
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
            labelCountryValue.Text = country.ElementAt(1);
            dropDownCountryID.Text = index.ToString();
        }
        catch (Exception ex)
        {
            successLabel.Visible = false;
            errorLabel.Visible = true;
            errorLabel.Text = ex.ToString();
        }
    }

    protected void dropDownLandID_SelectedIndexChanged(object sender, EventArgs e)
    {
        int index = int.Parse(dropDownCountryID.Text);
        getData(index);
    }

    protected void btnClear_Click(object sender, EventArgs e)
    {
        cityName.Text = "";
    }

    protected void btnSubmit_Click(object sender, EventArgs e)
    {
        try
        {
            if (cityName.Text.Length >= 3)
            {
                if (p.InsertTown(cityName.Text, int.Parse(dropDownCountryID.Text)))
                {
                    successLabel.Visible = true;
                    errorLabel.Visible = false;
                    successLabel.Text = "Byen " + cityName.Text + " ble lagt inn i databasen uten problemer.";
                    cityName.Text = "";
                }
            }
            else
            {
                successLabel.Visible = false;
                errorLabel.Visible = true;
                errorLabel.Text = "Vennlist oppgi et bynavn på minst tre tegn.";
            }
        }
        catch(Exception ex)
        {
            successLabel.Visible = false;
            errorLabel.Visible = true;
            errorLabel.Text = ex.Message;
        }
    }
}