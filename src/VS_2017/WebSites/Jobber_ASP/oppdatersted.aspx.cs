using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class oppdatersted : System.Web.UI.Page
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
            List<string> city = p.GetCities(index);
            textBoxTownID.Text = city.ElementAt(0);
            textBoxTownName.Text = city.ElementAt(1);
            townIDDropDownList.Text = index.ToString();
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
                    l = p.GetData("SELECT * FROM sted ORDER BY stedid asc", 0);
                    int i = 0;
                    while (i < l.Count)
                    {
                        townIDDropDownList.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(townIDDropDownList.Items[townIDDropDownList.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(townIDDropDownList.Items[0].ToString()));
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

    protected void townIDDropDownList_SelectedIndexChanged(object sender, EventArgs e)
    {
        int index = int.Parse(townIDDropDownList.Text);
        getData(index);
    }

    private bool checkData()
    {
        bool res = true;
        if (textBoxTownID.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = "StedID-en må bestå av minst ett siffer.";
            return false;
        }
        if (textBoxTownName.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = errorLabel.Text + "Stedsnavnet må bestå av minst ett siffer.";
        }
        return res;
    }

    protected void btnUpdate_Click(object sender, EventArgs e)
    {
        if (checkData())
        {
            if(p.updateStatus(int.Parse(townIDDropDownList.Text), int.Parse(textBoxTownID.Text), textBoxTownName.Text))
            {
                errorLabel.Visible = false;
                successLabel.Visible = true;
                successLabel.Text = "Oppdatering vellykket. Nye verdier:\nStedID: " + textBoxTownID.Text + "\nLandnavn: " + textBoxTownName.Text;
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
        lblTownID.Visible = false;
        lblTownName.Visible = false;
        successLabel.Visible = false;
        errorLabel.Visible = false;
        textBoxTownID.Visible = false;
        textBoxTownName.Visible = false;
        townIDDropDownList.Visible = false;
        labelRemoveData.Visible = true;
        labelRemoveData.Text = "Du er i ferd med å fjerne følgende data:<br />StedID: " + townIDDropDownList.Text + "<br />Status: " + textBoxTownName.Text + "<br /><br />Dette kan du ikke angre på. Er du sikker på at du vil fortsette?";
        btnYes.Visible = true;
        btnNo.Visible = true;
    }

    protected void btnNo_Click(object sender, EventArgs e)
    {
        btnCancel.Visible = true;
        btnDelete.Visible = true;
        btnUpdate.Visible = true;
        lblTownID.Visible = true;
        lblTownName.Visible = true;
        textBoxTownID.Visible = true;
        textBoxTownName.Visible = true;
        townIDDropDownList.Visible = true;
        labelRemoveData.Visible = false;
        labelRemoveData.Text = "";
        btnYes.Enabled = true;
        btnNo.Text = "Nei";
        btnYes.Visible = false;
        btnNo.Visible = false;
    }

    protected void btnYes_Click(object sender, EventArgs e)
    {
        labelRemoveData.Visible = false;
        labelRemoveData.Text = "";
        if (p.DeleteItem("sted", "stedid", int.Parse(townIDDropDownList.Text)))
        {
            errorLabel.Visible = false;
            successLabel.Visible = true;
            successLabel.Text = "Stedet ble fjernet fra databasen.";
            btnCancel.Visible = true;
            btnDelete.Visible = true;
            btnUpdate.Visible = true;
            lblTownID.Visible = true;
            lblTownName.Visible = true;
            textBoxTownID.Visible = true;
            textBoxTownName.Visible = true;
            townIDDropDownList.Visible = true;
            btnYes.Visible = false;
            btnNo.Visible = false;
        }
        else
        {
            successLabel.Visible = false;
            errorLabel.Visible = true;
            errorLabel.Text = "Noe har gått galt: " + p.getError();
            btnNo.Text = "OK";
            btnYes.Enabled = false;
        }
    }

    void refillList()
    {
        townIDDropDownList.Items.Clear();
        try
        {
            l = p.GetData("SELECT * FROM sted ORDER BY stedid asc", 0);
            int i = 0;
            while (i < l.Count)
            {
                townIDDropDownList.Items.Add(l.ElementAt(i));
                i++;
            }
            max = Int32.Parse(townIDDropDownList.Items[townIDDropDownList.Items.Count - 1].ToString());
            if (c == 0)
            {
                getData(Int32.Parse(townIDDropDownList.Items[0].ToString()));
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