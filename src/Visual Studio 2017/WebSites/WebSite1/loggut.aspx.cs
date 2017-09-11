using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class loggut : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        try
        {
            HttpCookie mycookie = new HttpCookie("auth");
            mycookie.Expires = DateTime.Now.AddDays(-1d);
            Response.Cookies.Add(mycookie);
            labelInfo.Text = "Du er nå logget ut.";
            HyperLink1.Text = "Klikk her for å logge deg inn igjen.";
        }
        catch(Exception ex)
        {
            labelInfo.Text = "En feil har oppstått: " + ex.Message;
            HyperLink1.Visible = false;
        }
    }
}