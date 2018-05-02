using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;

namespace JobbWebAppForms
{
    public partial class viewStatuses : Page
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
                        l = p.GetData("SELECT * FROM status ORDER BY statusid asc", 0);
                        int i = 0;
                        while (i < l.Count)
                        {
                            statusIDList.Items.Add(l.ElementAt(i));
                            i++;
                        }
                        max = Int32.Parse(statusIDList.Items[statusIDList.Items.Count - 1].ToString());
                        if (c == 0)
                        {
                            getData(Int32.Parse(statusIDList.Items[0].ToString()));
                            c++;
                        }
                    }
                    catch (Exception ex)
                    {
                        labelStatus.Visible = false;
                        labelStatusID.Visible = false;
                        labelStatusValue.Visible = false;
                        statusIDList.Visible = false;
                        errorLabel.Text = "Noe er feil: " + ex.ToString();
                        errorLabel.Visible = true;
                    }
                }
                else
                {
                    Response.Redirect("~/login.aspx");
                }
            }
        }
        public void getData(int index)
        {
            try
            {
                List<string> status = p.GetStatuses(index);
                labelStatusValue.Text = status.ElementAt(1);
                statusIDList.Text = index.ToString();
            }
            catch (Exception ex)
            {
                errorLabel.Visible = true;
                errorLabel.Text = ex.Message;
            }
        }

        protected void statusIDList_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                int idx = Int32.Parse(statusIDList.Text);
                getData(idx);
            }
            catch (Exception ex)
            {
                errorLabel.Visible = true;
                errorLabel.Text = "Noe er galt: " + ex.Message;
            }
        }
    }
}