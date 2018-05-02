using System;
using System.Web;
using System.Web.UI;

namespace JobbWebAppForms
{
    public partial class index : Page
    {
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
            if (!checkCookies())
            {
                Response.Redirect("~/login.aspx");
            }
        }
    }
}