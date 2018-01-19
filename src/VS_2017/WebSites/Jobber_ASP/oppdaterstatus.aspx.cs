using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class oppdaterstatus : System.Web.UI.Page
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
            List<string> status = p.GetStatuses(index);
            textBoxStatusID.Text = status.ElementAt(0);
            textBoxStatusName.Text = status.ElementAt(1);
            statusIDDropDownList.Text = index.ToString();
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
                    l = p.GetData("SELECT * FROM status ORDER BY statusid asc", 0);
                    int i = 0;
                    while (i < l.Count)
                    {
                        statusIDDropDownList.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(statusIDDropDownList.Items[statusIDDropDownList.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(statusIDDropDownList.Items[0].ToString()));
                        c++;
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

    protected void statusIDDropDownList_SelectedIndexChanged(object sender, EventArgs e)
    {
        int index = int.Parse(statusIDDropDownList.Text);
        getData(index);
    }

    private bool checkData()
    {
        bool res = true;
        if (textBoxStatusID.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = "LanID-en må bestå av minst ett siffer.";
            return false;
        }
        if (textBoxStatusName.Text.Length == 0)
        {
            errorLabel.Visible = true;
            successLabel.Visible = false;
            errorLabel.Text = errorLabel.Text + " LanID-en må bestå av minst ett siffer.";
        }
        return res;
    }

    protected void btnUpdate_Click(object sender, EventArgs e)
    {
        if (checkData())
        {
            if (p.updateCountry(int.Parse(statusIDDropDownList.Text), int.Parse(textBoxStatusID.Text), textBoxStatusName.Text))
            {
                errorLabel.Visible = false;
                successLabel.Visible = true;
                successLabel.Text = "Oppdatering vellykket. Nye verdier:\nStatusID: " + textBoxStatusID.Text + "\n: Status: " + textBoxStatusName.Text;
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
        lblStatusID.Visible = false;
        lblStatusName.Visible = false;
        textBoxStatusID.Visible = false;
        textBoxStatusName.Visible = false;
        labelRemoveData.Visible = true;
        labelRemoveData.Text = "Du er i ferd med å fjerne følgende data:<br />StatusID: " + statusIDDropDownList.Text + "<br />Status: " + textBoxStatusName.Text + "<br /><br />Dette kan du ikke angre på. Er du sikker på at du vil fortsette?";
        btnYes.Visible = true;
        btnNo.Visible = true;
    }

    protected void btnNo_Click(object sender, EventArgs e)
    {
        btnCancel.Visible = true;
        btnDelete.Visible = true;
        btnUpdate.Visible = true;
        lblStatusID.Visible = true;
        lblStatusName.Visible = true;
        textBoxStatusID.Visible = true;
        textBoxStatusName.Visible = true;
        statusIDDropDownList.Visible = true;
        labelRemoveData.Visible = false;
        labelRemoveData.Text = "";
        btnYes.Visible = false;
        btnNo.Visible = false;
    }

    protected void btnYes_Click(object sender, EventArgs e)
    {
        if (p.DeleteItem("status", "statusid", int.Parse(statusIDDropDownList.Text)))
        {
            errorLabel.Visible = false;
            successLabel.Visible = true;
            successLabel.Text = "Statusen ble fjernet fra databasen.";
            btnCancel.Visible = true;
            btnDelete.Visible = true;
            btnUpdate.Visible = true;
            lblStatusID.Visible = true;
            lblStatusName.Visible = true;
            textBoxStatusID.Visible = true;
            textBoxStatusName.Visible = true;
            statusIDDropDownList.Visible = true;
            labelRemoveData.Visible = false;
            labelRemoveData.Text = "";
            btnYes.Visible = false;
            btnNo.Visible = false;
        }
        else
        {
            successLabel.Visible = false;
            errorLabel.Visible = true;
            errorLabel.Text = "Noe har gått galt: " + p.getError();
        }
    }

    void refillList()
    {
        statusIDDropDownList.Items.Clear();
        try
        {
            l = p.GetData("SELECT * FROM status ORDER BY statusid asc", 0);
            int i = 0;
            while (i < l.Count)
            {
                statusIDDropDownList.Items.Add(l.ElementAt(i));
                i++;
            }
            max = Int32.Parse(statusIDDropDownList.Items[statusIDDropDownList.Items.Count - 1].ToString());
            if (c == 0)
            {
                getData(Int32.Parse(statusIDDropDownList.Items[0].ToString()));
                c++;
            }
        }
        catch (Exception ex)
        {
            errorLabel.Visible = true;
            errorLabel.Text = "Noe er galt: " + ex.Message;
        }
    }
}