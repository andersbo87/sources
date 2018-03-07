using System;
using System.Web;
using System.Web.UI;

namespace JobbWebAppForms
{
    public partial class newStatus : Page
    {
        psql p;
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
            // Sjekke om objektet har en referanseverdi, eller om det er en "tom" peker.
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
        }

        protected void btnClear_Click(object sender, EventArgs e)
        {
            statusName.Text = ""; // Fjerner teksten
        }

        protected void btnInsertNewStatus_Click(object sender, EventArgs e)
        {
            try
            {
                if (statusName.Text.Length >= 4)
                {
                    // Sjekker om innsettingen gikk som den skulle (Det skal riktignok sies at ved feil, vil nok koden i catch-blokken kjøres...)
                    if (p.InsertStatus(statusName.Text))
                    {
                        // Viser ei melding som sier fra at alt gikk som det skulle.
                        successLabel.Visible = true;
                        errorLabel.Visible = false; // Dersom det først har gått galt, for så å gå som det skulle, skjules den forrige feilmeldinga
                        successLabel.Text = "Den nye statusen ble lagt inn uten problemer.";
                        statusName.Text = "";
                    }
                }
                else
                {
                    successLabel.Visible = false;
                    errorLabel.Visible = true;
                    errorLabel.Text = "Du må sette inn en status på minst fire tegn.";
                }
            }
            catch (Exception ex)
            {
                successLabel.Visible = false;
                errorLabel.Visible = true;
                errorLabel.Text = ex.Message;
            }
        }

        protected void statusName_TextChanged(object sender, EventArgs e)
        {
            // Do nothing.
        }
    }
}