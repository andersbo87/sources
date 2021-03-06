﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="newTown.aspx.cs" Inherits="JobbWebAppForms.newTown" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Legg inn et nytt sted</title>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <h1>Nytt sted</h1><br />
        <table border="0">
            <tr>
                <td style="vertical-align:top;" class="auto-style1">
                    <h4>Meny</h4>
                    <a href="logout.aspx">Logg ut</a><br />
                    <h5>Vise eksisterende data</h5>
                    <a href="viewCountries.aspx">Registrerte land</a><br />
                    <a href="viewStatuses.aspx">Registrerte statuser</a><br />
                    <a href="viewTowns.aspx">Registrerte steder</a><br />
                    <a href="viewApplications.aspx">Registrerte søknader</a><br />
                    <h5>Oppdatere eller slette eksisterende data</h5>
                    <a href="updateCountry.aspx">Endre land</a><br />
                    <a href="updateStatus.aspx">Endre status</a><br />
                    <a href="updateTown.aspx">Endre steder</a><br />
                    <a href="updateApplication.aspx">Endre søknad</a><br />
                    <h5>Sett inn nye data</h5>
                    <a href="newCountry.aspx">Nytt land</a><br />
                    <a href="newStatus.aspx">Ny status</a><br />
                    <a href="newTown.aspx">Nytt sted</a><br />
                    <a href="newApplication.aspx">Ny søknad</a><br />
                </td>
                <td style="vertical-align:top;" class="auto-style2">
                    Skal du lete etter jobber i en ny by? Legg den nye byen inn i systemet her.
                    <br />
                    <br />
                    <asp:Label ID="successLabel" runat="server" Visible="false" ForeColor="Green" Font-Bold="true"></asp:Label>
                    <asp:Label ID="errorLabel" runat="server" Visible="false" ForeColor="Red" Font-Bold="true"></asp:Label>
                    <table border="0">
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="cityLabel" runat="server" Text="Stedsnavn"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="cityName" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="countryIDLabel" runat="server" Text="LandID"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:DropDownList ID="dropDownCountryID" runat="server" AutoPostBack="true" OnSelectedIndexChanged="dropDownLandID_SelectedIndexChanged"></asp:DropDownList>
                                <asp:Label ID="labelCountryValue" runat="server"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Button ID="btnSubmit" runat="server" Text="Sett inn" OnClick="btnSubmit_Click" />
                                <asp:Button ID="btnClear" runat="server" Text="Fjern tekst" OnClick="btnClear_Click" />
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
