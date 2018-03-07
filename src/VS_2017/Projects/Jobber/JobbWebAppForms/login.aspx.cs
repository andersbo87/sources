using System;
using System.Web;
using System.Web.UI;

namespace JobbWebAppForms
{
    public partial class login : Page
    {
        psql p;
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnSignIn_Click(object sender, EventArgs e)
        {
            p = new psql();
            p.SetUsername(textBoxUsername.Text);
            p.SetPassword(textBoxPassword.Text);
            p.SetServer("localhost");
            try
            {
                if (p.Init())
                {
                    HttpCookie hc = new HttpCookie("auth");
                    hc.Values["brukernavn"] = textBoxUsername.Text;
                    hc.Values["passord"] = textBoxPassword.Text;
                    hc.Expires = DateTime.Now.AddDays(1);
                    Response.Cookies.Add(hc);
                    Response.Redirect("index.aspx");
                }
                else
                {
                    errorLabel.Visible = true;
                    errorLabel.Text = "Noe er galt: " + p.getError();
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