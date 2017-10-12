<%@ Page Language="C#" AutoEventWireup="true" CodeFile="visSteder.aspx.cs" Inherits="visSteder" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <link rel="stylesheet" type="text/css" href="/css/main.css" />
    <title>Innlagte steder</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h1>Registrerte steder</h1>
            <br />
            <table border="0">
                <tr>
                    <td style="vertical-align:top;">
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
                    <td style="vertical-align:top">
                        Her kan du se en oversikt over byene som er registrert i databasen:<br />
                        <asp:Label ID="errorLabel" runat="server" Text="Feil" Visible="False" ForeColor="Red"></asp:Label>
                        <br />
                        <table border="0">
                            <tr>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="StedIDLabel" runat="server" Text="StedID"></asp:Label>
                                </td>
                                <td style="vertical-align:top;">
                                    <asp:DropDownList ID="StedID" runat="server" AutoPostBack="True" OnSelectedIndexChanged="StedID_SelectedIndexChanged"></asp:DropDownList>
                                </td>
                            </tr>
                            <tr>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="StedsnavnLabel" runat="server" Text="Stedsnavn"></asp:Label>
                                </td>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="stedsnavnValue" runat="server" Text="$stedsnavn"></asp:Label>
                                </td>
                            </tr>
                            <tr>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="LandidLabel" runat="server" Text="Landid"></asp:Label>
                                </td>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="landidValue" runat="server" Text="$landid"></asp:Label> &nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="labelLandnavn" runat="server" Text="Landnavn"></asp:Label>
                                </td>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="landnavnValue" runat="server" Text="$landnavn"></asp:Label>
                                </td>
                            </tr>
                        </table>
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
