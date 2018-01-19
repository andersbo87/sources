using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Npgsql;

public partial class visSoknader : System.Web.UI.Page
{
    psql p;
    int max;
    int c = 0;
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
        if (p == null)
        {
            if (checkCookies())
            {
                p = new psql();
                p.SetUsername(hc.Values["brukernavn"]);
                p.SetPassword(hc.Values["passord"]);
                p.SetServer("localhost");
            }
            else
            {
                Response.Redirect("~/login.aspx");
            }
        }
        if (!IsPostBack)
        {
            if (checkCookies())
            {
                p.SetUsername(hc.Values["brukernavn"]);
                p.SetPassword(hc.Values["passord"]);
                p.SetServer("localhost");
                labelInfo.Text = "Informasjonen på denne siden hentes fra en PostgreSQL-database på Windows " + p.getString();
                try
                {
                    List<string> l = p.GetData("SELECT soknadid FROM view_soknad ORDER BY soknadid asc", 0);
                    int i = 0;
                    while (i < l.Count)
                    {
                        dropDownApplicationID.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(dropDownApplicationID.Items[dropDownApplicationID.Items.Count - 1].ToString());
                    //comboBoxApplicationID.Text = "1";
                    if (c == 0)
                    {
                        getData(Int32.Parse(dropDownApplicationID.Items[0].ToString()));
                        c++;
                    }
                }
                catch (Exception ex)
                {
                    errorLabel.Visible = true;
                    errorLabel.Text = "Noe er feil: " + ex.Message;
                    labelApplicationID.Visible = false;
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
                    statusValue.Visible = false;
                }
            }
            else
            {
                Response.Redirect("~/login.aspx");
            }
        }
    }
    private void getData(int index)
    {
        try
        {
            List<string> applicationData = p.GetApplications(index);
            titleValue.Text = applicationData.ElementAt(0);
            companyValue.Text = applicationData.ElementAt(1);
            applicationDeadlineValue.Text = applicationData.ElementAt(2);
            townIDValue.Text = applicationData.ElementAt(3);
            townNameValue.Text = applicationData.ElementAt(4);
            countryIDValue.Text = applicationData.ElementAt(5);
            countryValue.Text = applicationData.ElementAt(6);
            statusIDValue.Text = applicationData.ElementAt(7);
            statusValue.Text = applicationData.ElementAt(8);
            dropDownApplicationID.Text = index.ToString();
            //comboBoxApplicationID.Text = index.ToString();
        }
        catch (InvalidOperationException)
        {
            //MessageBox.Show(e.Message);
            //getData(index+1);
            return;
        }
        catch (System.FormatException)
        {

        }
    }


    protected void dropDownApplicationID_SelectedIndexChanged(object sender, EventArgs e)
    {
        int idx = Int32.Parse(dropDownApplicationID.Text);
        getData(idx);
    }
}