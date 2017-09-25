﻿<%@ Page Language="C#" AutoEventWireup="true" CodeFile="visLand.aspx.cs" Inherits="registrerteLand" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <link rel="stylesheet" type="text/css" href="/css/main.css" />
    <style type="text/css">
        .auto-style1 {
            width: 200px;
        }
    </style>
    <title>Vis land</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <h1>Registrerte land</h1>
        <br />
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
                    Her finner du ei liste over land som er registrert i databasen. Merk at du ikke kan endre på disse dataene.<br />
                    <asp:Label ID="errorLabel" runat="server" ForeColor="Red" Text="Feil"></asp:Label>
&nbsp;<table border="0">
                        <tr>
                            <td style="vertical-align:top;">
                                <asp:Label ID="labelLandID" runat="server" Text="LandID"></asp:Label>
                            </td>
                            <td style="vertical-align:top;">
                                <asp:DropDownList ID="dropDownLandID" runat="server" AutoPostBack="true" OnSelectedIndexChanged="dropDownLandID_SelectedIndexChanged"></asp:DropDownList>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top;">
                                <asp:Label ID="labelCountry" runat="server" Text="Land"></asp:Label>
                            </td>
                            <td style="vertical-align:top;">
                                <asp:Label ID="labelCountryValue" runat="server" Text="$land"></asp:Label>
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
