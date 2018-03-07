using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;

namespace JobbWebAppForms
{
    public partial class newApplication : Page
    {
        psql p;
        HttpCookie hc;
        //int max, c = 0;
        List<string> cityList, statusList;
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
        private void GetCities()
        {
            cityList = p.GetData("SELECT stedid FROM sted", 0);
            int i = 0;
            while (i < cityList.Count)
            {
                dropDownCityList.Items.Add(cityList.ElementAt(i));
                i++;
            }
        }
        private void GetStatuses()
        {
            statusList = p.GetData("SELECT statusID FROM status", 0);
            int i = 0;
            while (i < statusList.Count)
            {
                dropDownStatusList.Items.Add(statusList.ElementAt(i));
                i++;
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
                    labelInfo.Text = "Informasjonen på denne siden hentes fra en PostgreSQL-database på Windows " + p.getString();
                    try
                    {
                        p.SetUsername(hc.Values["brukernavn"]); // Legger inn det brukernavnet brukeren anga under innlogging
                        p.SetPassword(hc.Values["passord"]); // Legger inn passordet brukeren oppga under innlogging
                        p.SetServer("localhost");
                        GetCities();
                        GetStatuses();
                    }
                    catch (Exception ex)
                    {
                        errorLabel.Visible = true;
                        errorLabel.Text = "Noe er feil: " + ex.Message;
                        /*labelApplicationID.Visible = false;
                        labelApplicationDeadline.Visible = false;
                        labelCompany.Visible = false;
                        labelCountry.Visible = false;
                        labelCountryID.Visible = false;
                        labelStatus.Visible = false;
                        labelStatusID.Visible = false;
                        labelTitle.Visible = false;
                        labelTownID.Visible = false;
                        labelTownName.Visible = false;
                        applicationDeadlineValue.Visible = false;
                        companyValue.Visible = false;
                        titleValue.Visible = false;
                        dropDownApplicationID.Visible = false;
                        townIDValue.Visible = false;
                        townNameValue.Visible = false;
                        countryIDValue.Visible = false;
                        countryValue.Visible = false;
                        statusIDValue.Visible = false;
                        statusValue.Visible = false;*/
                    }
                }
            }
        }

        protected void btnClear_Click(object sender, EventArgs e)
        {
            title.Text = "";
            company.Text = "";
            deadline.Text = "";
            motivation.Text = "";
        }
        bool checkData()
        {
            if (title.Text.Length == 0)
            {
                successLabel.Visible = false;
                errorLabel.Visible = true;
                errorLabel.Text = "Vennligst angi en tittel.";
                return false;
            }

            if (company.Text.Length == 0)
            {
                successLabel.Visible = false;
                errorLabel.Visible = true;
                errorLabel.Text = "Vennligst angi et bedriftsnavn.";
                return false;
            }
            if (dropDownCityList.Text.Length == 0)
            {
                successLabel.Visible = false;
                errorLabel.Visible = true;
                errorLabel.Text = "Vennligst velg et stednummer fra lista nedenfor.";
                return false;
            }
            if (dropDownStatusList.Text.Length == 0)
            {
                successLabel.Visible = false;
                errorLabel.Visible = true;
                errorLabel.Text = "Vennligst velg en statusid fra listen nedenfor.";
                return false;
            }
            if (deadline.Text.Length == 0)
            {
                successLabel.Visible = false;
                errorLabel.Visible = true;
                errorLabel.Text = "Vennligst angi en sønadsfrist. Står det ingen frist, skriv \"Snarest\" isteden.";
                return false;
            }
            return true;
        }
        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            try
            {
                if (checkData())
                {
                    if (p.InsertApplication(title.Text, company.Text, int.Parse(dropDownCityList.Text), int.Parse(dropDownStatusList.Text), deadline.Text, motivation.Text))
                    {
                        errorLabel.Visible = false;
                        successLabel.Visible = true;
                        successLabel.Text = "Følgende data ble lagt inn:\nTittel: " + title.Text + "\nBedrift: " + company.Text + "\nStedID: " + dropDownCityList.Text + "\n StatusID: " + dropDownStatusList.Text + "\nSøknadsfrist: " + deadline.Text;
                        title.Text = "";
                        company.Text = "";
                        deadline.Text = "";
                    }
                }
            }
            catch (Exception ex)
            {
                errorLabel.Visible = true;
                successLabel.Visible = false;
                errorLabel.Text = ex.Message;
            }
        }

        protected void dropDownCityList_SelectedIndexChanged(object sender, EventArgs e)
        {
            cityNameLabel.Text = p.getCityName(int.Parse(dropDownCityList.Text));
        }

        protected void dropDownStatusList_SelectedIndexChanged(object sender, EventArgs e)
        {
            statusNameLabel.Text = p.getStatusName(int.Parse(dropDownStatusList.Text));
        }
    }
}