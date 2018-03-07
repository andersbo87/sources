using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;

namespace JobbWebAppForms
{
    public partial class viewCountries : Page
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
                        l = p.GetData("SELECT * FROM land ORDER BY landid asc", 0);
                        int i = 0;
                        while (i < l.Count)
                        {
                            dropDownLandID.Items.Add(l.ElementAt(i));
                            i++;
                        }
                        max = Int32.Parse(dropDownLandID.Items[dropDownLandID.Items.Count - 1].ToString());
                        if (c == 0)
                        {
                            getData(Int32.Parse(dropDownLandID.Items[0].ToString()));
                            c++;
                        }
                    }
                    catch (Exception ex)
                    {
                        errorLabel.Visible = true;
                        errorLabel.Text = "Noe er galt: " + ex.Message;
                        labelCountry.Visible = false;
                        labelCountryValue.Visible = false;
                        labelLandID.Visible = false;
                        dropDownLandID.Visible = false;
                    }
                }
                else
                {
                    Response.Redirect("login.aspx");
                }
            }
            /*try
            {
                p = new psql();
                p.SetUsername("a-bol");
                p.SetPassword("mPecGt87!");
                p.SetServer("localhost");
                l = p.GetData("SELECT * FROM land ORDER BY landid asc", 0);
                if (!IsPostBack)
                {
                    int i = 0;
                    while (i < l.Count)
                    {
                        dropDownLandID.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(dropDownLandID.Items[dropDownLandID.Items.Count - 1].ToString());
                    //comboBoxTownID.Text = "1";
                    if (c == 0)
                    {
                        getData(Int32.Parse(dropDownLandID.Items[0].ToString()));
                        c++;
                    }
                }
            }
            catch(Exception ex)
            {
                errorLabel.Visible = true;
                errorLabel.Text = "Noe er galt: " + ex.Message;
                labelCountry.Visible = false;
                labelCountryValue.Visible = false;
                labelLandID.Visible = false;
                dropDownLandID.Visible = false;
            }*/
        }
        void getData(int index)
        {
            try
            {
                checkCookies();
                errorLabel.Text = p.getServer();
                List<string> country = p.GetCountries(index);
                labelCountryValue.Text = country.ElementAt(1);
                dropDownLandID.Text = index.ToString();
            }
            catch (Exception ex)
            {
                errorLabel.Visible = true;
                errorLabel.Text = ex.ToString();
            }
        }
        protected void dropDownLandID_SelectedIndexChanged(object sender, EventArgs e)
        {
            int index = int.Parse(dropDownLandID.Text);
            getData(index);
        }
    }
}