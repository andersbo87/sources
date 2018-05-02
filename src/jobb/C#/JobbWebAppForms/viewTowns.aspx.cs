using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;

namespace JobbWebAppForms
{
    public partial class viewTowns : Page
    {
        psql p;
        int max, c = 0;
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
                    p = new psql();
                    p.SetUsername(hc.Values["brukernavn"]);
                    p.SetPassword(hc.Values["passord"]);
                    p.SetServer("localhost");
                    labelInfo.Text = "Informasjonen på denne siden hentes fra en PostgreSQL-database på Windows " + p.getString();
                    try
                    {
                        l = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
                        int i = 0;
                        while (i < l.Count)
                        {
                            StedID.Items.Add(l.ElementAt(i));
                            i++;
                        }
                        max = Int32.Parse(StedID.Items[StedID.Items.Count - 1].ToString());
                        if (c == 0)
                        {
                            getData(Int32.Parse(StedID.Items[0].ToString()));
                            c++;
                        }
                    }
                    catch (Exception ex)
                    {
                        LandidLabel.Visible = false;
                        StedIDLabel.Visible = false;
                        StedsnavnLabel.Visible = false;
                        StedID.Visible = false;
                        stedsnavnValue.Visible = false;
                        LandidLabel.Visible = false;
                        landidValue.Visible = false;
                        labelLandnavn.Visible = false;
                        landnavnValue.Visible = false;
                        errorLabel.Text = "Noe er feil: " + ex.Message;
                        errorLabel.Visible = true;
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
            List<string> cityData = p.GetCities(index);
            stedsnavnValue.Text = cityData.ElementAt(1);
            landidValue.Text = cityData.ElementAt(2);
            landnavnValue.Text = cityData.ElementAt(3);
            StedID.Text = index.ToString();
        }

        protected void StedID_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                int idx = Int32.Parse(StedID.Text);
                getData(idx);
            }
            catch (Exception ex)
            {
                errorLabel.Visible = true;
                errorLabel.Text = "Noe er feil: " + ex.Message;
            }
        }
    }
}