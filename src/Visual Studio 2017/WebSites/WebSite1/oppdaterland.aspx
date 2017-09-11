<%@ Page Language="C#" AutoEventWireup="true" CodeFile="oppdaterland.aspx.cs" Inherits="oppdaterland" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Endre eller slett land</title>
<link rel="stylesheet" type="text/css" href="css/main.css" />
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <h1>Endre eller slett land</h1><br />
        <table border="0">
            <tr>
                <td style="vertical-align:top;" class="auto-style1">
                    <h4>Meny</h4>
                    <a href="loggut.aspx">Logg ut</a><br />
                    <h5>Vise eksisterende data</h5>
                    <a href="visLand.aspx">Registrerte land</a><br />
                    <a href="visStatuser.aspx">Registrerte statuser</a><br />
                    <a href="visSteder.aspx">Registrerte steder</a><br />
                    <a href="visSoknader.aspx">Registrerte søknader</a><br />
                    <h5>Oppdatere eller slette eksisterende data</h5>
                    <a href="oppdaterland.aspx">Endre land</a><br />
                    <a href="oppdaterstatus.aspx">Endre status</a><br />
                    <a href="oppdatersted.aspx">Endre steder</a><br />
                    <a href="oppdatersøknad.aspx">Endre søknad</a><br />
                    <h5>Sett inn nye data</h5>
                    <a href="nyttland.aspx">Nytt land</a><br />
                    <a href="nystatus.aspx">Ny status</a><br />
                    <a href="nyttsted.aspx">Nytt sted</a><br />
                    <a href="nysøknad.aspx">Ny søknad</a><br />
                </td>
                <td style="vertical-align:top;" class="auto-style2">
                    Her vil det etter hvert dukke opp en tekst.
                </td>
            </tr>
            <tr>
                <td style="vertical-align:top;" colspan="2">
                    <asp:Label ID="labelInfo" runat="server" Text="Label"></asp:Label>
                </td>
            </tr>
        </table>
    </div>
    </form>
</body>
</html>
