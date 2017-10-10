<%@ Page Language="C#" AutoEventWireup="true" CodeFile="login.aspx.cs" Inherits="login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Logg inn</title>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
</head>
<body>
    <form id="form1" runat="server">
        <div>
            For å bruke dette, webområdet, må du logge deg inn med PostgreSQL-brukernavnet og passordet ditt. Dette gjør du ved å fylle inn skjemaet nedenfor.
            <br />
            Når du har fylt inn skjemaet, vil du bli ført tilbake til indekssiden.
            <br />
            <br />
            <table border="0">
                <tr>
                    <td style="vertical-align:top;">
                        <asp:Label ID="labelUsername" runat="server" Text="Brukernavn"></asp:Label>
                    </td>
                    <td style="vertical-align:top;">
                        <asp:TextBox ID="textBoxUsername" runat="server"></asp:TextBox><br />
                    </td>
                </tr>
                <tr>
                    <td style="vertical-align:top;">
                        <asp:Label ID="labelPassword" runat="server" Text="Passord"></asp:Label>
                    </td>
                    <td style="vertical-align:top;">
                        <asp:TextBox ID="textBoxPassword" runat="server" TextMode="Password"></asp:TextBox><br />
                    </td>
                </tr>
            </table>
            <asp:Label ID="errorLabel" runat="server" ForeColor="Red" Visible="false" Text="Feil"></asp:Label><br />
            <asp:Button ID="btnSignIn" runat="server" Text="Logg inn" OnClick="btnSignIn_Click" />
        </div>
    </form>
</body>
</html>
