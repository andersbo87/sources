using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class oppdatersøknad : System.Web.UI.Page
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
            errorLabel.Text = p.getServer();
            List<string> application = p.GetApplications(index);
            textBoxApplicationID.Text = application.ElementAt(0);
            textBoxJobTitle.Text = application.ElementAt(1);
            textBoxCompany.Text = application.ElementAt(2);
            townIDDropDownList.Text = application.ElementAt(3);
            lblTownNameValue.Text = application.ElementAt(4);
            lblCountryIDvalue.Text = application.ElementAt(5);
            lblCountryNameValue.Text = "(" + application.ElementAt(6) + ")";
            statusIDDropDownList.Text = application.ElementAt(7);
            lblStatusValue.Text = application.ElementAt(8);
            textBoxDeadline.Text = application.ElementAt(9);
            textBoxMotivation.Text = application.ElementAt(10);
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
                    l = p.GetData("SELECT soknadid FROM soknad ORDER BY soknadid asc", 0);
                    int i = 0;
                    while (i < l.Count)
                    {
                        applicationIDDropDownList.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(applicationIDDropDownList.Items[applicationIDDropDownList.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(applicationIDDropDownList.Items[0].ToString()));
                        c++;
                    }
                    getCities(Int32.Parse(applicationIDDropDownList.Items[0].ToString()));
                    getStatuses(Int32.Parse(applicationIDDropDownList.Items[0].ToString()));
                }
                catch (Exception ex)
                {
                    errorLabel.Visible = true;
                    errorLabel.Text = "Noe er galt: " + ex.ToString();
                }
            }
        }
    }

    private void getCities(int index)
    {
        List<string> cityList = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
        int i = 0;
        if (townIDDropDownList.Items.Count == 0)
        {
            while (i < cityList.Count)
            {
                townIDDropDownList.Items.Add(cityList.ElementAt(i));
                i++;
            }
        }
        townIDDropDownList.Text = p.GetCityID(index).ToString();
    }

    private void getStatuses(int index)
    {
        List<string> statusList = p.GetData("SELECT statusid FROM status order by statusid asc", 0);
        int i = 0;
        if (statusIDDropDownList.Items.Count == 0)
        {
            while (i < statusList.Count)
            {
                statusIDDropDownList.Items.Add(statusList.ElementAt(i));
                i++;
            }
        }
        statusIDDropDownList.Text = p.GetStatusID(index).ToString();
    }

    protected void applicationIDDropDownList_SelectedIndexChanged(object sender, EventArgs e)
    {
        int index = int.Parse(applicationIDDropDownList.Text);
        getData(index);
    }

    private bool checkData()
    {
        bool res = true;
        if (textBoxJobTitle.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = errorLabel.Text + "Jobbtittelen må bestå av minst ett siffer.";
            res = false;
        }
        if(textBoxCompany.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = errorLabel.Text + "Bedriftsnavnet må bestå av minst ett siffer.";
            res = false;
        }
        if(textBoxDeadline.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = errorLabel.Text + "Søknadsfristen må bestå av minst ett siffer.";
            res = false;
        }
        return res;
    }

    protected void btnYes_Click(object sender, EventArgs e)
    {
        labelRemoveData.Visible = false;
        labelRemoveData.Text = "";
        if (p.DeleteItem("soknad", "soknadid", int.Parse(applicationIDDropDownList.Text)))
        {
            errorLabel.Visible = false;
            successLabel.Visible = true;
            successLabel.Text = "Søknaden ble fjernet fra databasen.";
            btnCancel.Visible = true;
            btnDelete.Visible = true;
            btnUpdate.Visible = true;

            applicationIDDropDownList.Visible = true;
            lblApplicationID.Visible = true;
            textBoxApplicationID.Visible = true;
            lblCompany.Visible = true;
            textBoxCompany.Visible = true;
            lblTownID.Visible = true;
            townIDDropDownList.Visible = true;
            lblCountryID.Visible = true;
            lblCountryIDvalue.Visible = true;
            lblCountryNameValue.Visible = true;
            lblStatusID.Visible = true;
            statusIDDropDownList.Visible = true;
            lblStatusValue.Visible = true;
            lblDeadline.Visible = true;
            textBoxDeadline.Visible = true;
            lblMotivation.Visible = true;
            textBoxMotivation.Visible = true;

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

    protected void btnNo_Click(object sender, EventArgs e)
    {
        btnCancel.Visible = true;
        btnDelete.Visible = true;
        btnUpdate.Visible = true;

        applicationIDDropDownList.Visible = true;
        lblApplicationID.Visible = true;
        textBoxApplicationID.Visible = true;
        lblCompany.Visible = true;
        textBoxCompany.Visible = true;
        lblTownID.Visible = true;
        townIDDropDownList.Visible = true;
        lblCountryID.Visible = true;
        lblCountryIDvalue.Visible = true;
        lblCountryNameValue.Visible = true;
        lblStatusID.Visible = true;
        statusIDDropDownList.Visible = true;
        lblStatusValue.Visible = true;
        lblDeadline.Visible = true;
        textBoxDeadline.Visible = true;
        lblMotivation.Visible = true;
        textBoxMotivation.Visible = true;

        labelRemoveData.Visible = false;
        labelRemoveData.Text = "";
        btnYes.Enabled = true;
        btnNo.Text = "Nei";
        btnYes.Visible = false;
        btnNo.Visible = false;
    }

    protected void btnUpdate_Click(object sender, EventArgs e)
    {
        if (checkData())
        {
            if(p.updateAppliction(int.Parse(applicationIDDropDownList.SelectedItem.Text), int.Parse(textBoxApplicationID.Text), textBoxJobTitle.Text, textBoxCompany.Text, int.Parse(townIDDropDownList.SelectedItem.Text), int.Parse(statusIDDropDownList.SelectedItem.Text), textBoxDeadline.Text, textBoxMotivation.Text))
            {
                errorLabel.Visible = false;
                successLabel.Visible = true;
                successLabel.Text = "Oppdatering vellykket. Nye verdier:<br />StedID: " + textBoxApplicationID.Text + "<br />Tittel: " + textBoxJobTitle.Text + "<br />Bedrift:" + textBoxCompany.Text + "<br />StedID: " + townIDDropDownList.SelectedItem.Text + "<br />StatusID: " + statusIDDropDownList.SelectedItem.Text + "<br />Søknadsfrist: " + textBoxDeadline.Text + "<br />Motivasjon: " + textBoxMotivation.Text;
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
        /*lblTownID.Visible = false;
        lblTownName.Visible = false;
        successLabel.Visible = false;
        errorLabel.Visible = false;
        textBoxTownID.Visible = false;
        textBoxTownName.Visible = false;
        townIDDropDownList.Visible = false;*/
        applicationIDDropDownList.Visible = false;
        lblApplicationID.Visible = false;
        textBoxApplicationID.Visible = false;
        lblCompany.Visible = false;
        textBoxCompany.Visible = false;
        lblTownID.Visible = false;
        townIDDropDownList.Visible = false;
        lblCountryID.Visible = false;
        lblCountryIDvalue.Visible = false;
        lblCountryNameValue.Visible = false;
        lblStatusID.Visible = false;
        statusIDDropDownList.Visible = false;
        lblStatusValue.Visible = false;
        lblDeadline.Visible = false;
        textBoxDeadline.Visible = false;
        lblMotivation.Visible = false;
        textBoxMotivation.Visible = false;


        labelRemoveData.Visible = true;
        labelRemoveData.Text = "Du er i ferd med å fjerne følgende data:<br />SøknadID: " + applicationIDDropDownList.Text + "<br />Tittel: " + textBoxJobTitle.Text + "<br />Bedrift: " + textBoxCompany.Text + "<br />StedID: " + townIDDropDownList.Text + "<br />StatusID: " + statusIDDropDownList.Text + "<br />Søknadsfrist: " + textBoxDeadline.Text + "<br />Motivasjon" + textBoxMotivation.Text + "<br /><br />Dette kan du ikke angre på. Er du sikker på at du vil fortsette?";
        btnYes.Visible = true;
        btnNo.Visible = true;
    }

    protected void townIDDropDownList_SelectedIndexChanged(object sender, EventArgs e)
    {
        setTownName(Int32.Parse(townIDDropDownList.SelectedItem.ToString()));
    }

    protected void statusIDDropDownList_SelectedIndexChanged(object sender, EventArgs e)
    {
        setStatusName(Int32.Parse(statusIDDropDownList.SelectedItem.ToString()));
    }

    private void setTownName(int index)
    {
        lblTownNameValue.Text = p.getCityName(index);
    }

    private void setStatusName(int index)
    {
        lblStatusValue.Text = p.getStatusName(index);
    }
}