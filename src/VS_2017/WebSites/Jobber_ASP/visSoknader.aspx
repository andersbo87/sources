<%@ Page Language="C#" AutoEventWireup="true" CodeFile="visSoknader.aspx.cs" Inherits="visSoknader" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <style type="text/css">
        .auto-style1 {
            width: 200px;
        }
    </style>
    <link rel="stylesheet" type="text/css" href="/css/main.css" />
    <title>Søknader som er registrert i databasen</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <h1>Registrerte søknader</h1>
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
                    Her vil du etter hvert få se informasjon om de registrerte søknadene.
                    Velg en søknad fra listeboksen under:<br />
                    <asp:Label ID="errorLabel" runat="server" ForeColor="Red" Visible="false" Text="Feil"></asp:Label>
                    <br />
                    <table border="0">
                        <tr>
                            <td style="vertical-align:top;">
                                <asp:Label ID="labelApplicationID" runat="server" Text="Søknadid "></asp:Label>
                            </td>
                            <td>
                                <asp:DropDownList ID="dropDownApplicationID" runat="server" AutoPostBack="True" OnSelectedIndexChanged="dropDownApplicationID_SelectedIndexChanged"></asp:DropDownList>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <asp:Label ID="labelTitle" runat="server" Text="Tittel"></asp:Label>
                            </td>
                            <td>
                                <asp:Label ID="titleValue" runat="server" Text="$tittel"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <asp:Label ID="labelCompany" runat="server" Text="Bedrift"></asp:Label>
                            </td>
                            <td>
                                <asp:Label ID="companyValue" runat="server" Text="$bedrift"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <asp:Label ID="labelApplicationDeadline" runat="server" Text="Søknadsfrist "></asp:Label>
                            </td>
                            <td>
                                <asp:Label ID="applicationDeadlineValue" runat="server" Text="$søknadsfrist"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <a href="visSteder.aspx"><asp:Label ID="labelTownID" runat="server" Text="StedID"></asp:Label></a>
                            </td>
                            <td>
                                <asp:Label ID="townIDValue" runat="server" Text="$stedid"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <a href="visSteder.aspx"><asp:Label ID="labelTownName" runat="server" Text="Stedsnavn"></asp:Label></a>
                            </td>
                            <td>
                                <asp:Label ID="townNameValue" runat="server" Text="$stedsnavn"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <a href="visLand.aspx"><asp:Label ID="labelCountryID" runat="server" Text="LandID"></asp:Label></a>
                            </td>
                            <td>
                                <asp:Label ID="countryIDValue" runat="server" Text="$landid"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <a href="visLand.aspx"><asp:Label ID="labelCountry" runat="server" Text="Landnavn"></asp:Label></a>
                            </td>
                            <td>
                                <asp:Label ID="countryValue" runat="server" Text="$land"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <a href="visStatuser.aspx"><asp:Label ID="labelStatusID" runat="server" Text="StatusID"></asp:Label></a>
                            </td>
                            <td>
                                <asp:Label ID="statusIDValue" runat="server" Text="$statusid"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <a href="visStatuser.aspx"><asp:Label ID="labelStatus" runat="server" Text="Status"></asp:Label></a>
                            </td>
                            <td>
                               <asp:Label ID="statusValue" runat="server" Text="$status"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="motivationLabel" runat="server" Text="Motivasjon"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:Label ID="motivationValue" runat="server" Text="$motivasjon"></asp:Label>
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
