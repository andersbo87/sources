<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="newApplication.aspx.cs" Inherits="JobbWebAppForms.newApplication" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Sett inn en ny søknad</title>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <h1>Ny søknad</h1><br />
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
                    Her kan du sette inn en ny søknad du måtte finne på nett, i aviser, etc.
                    <br />
                    <br />
                    <asp:Label ID="successLabel" runat="server" Font-Bold="true" ForeColor="Green" Visible="false"></asp:Label>
                    <asp:Label ID="errorLabel" runat="server" Font-Bold="true" ForeColor="Red" Visible="false"></asp:Label>
                    <table border="0">
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="titleLabel" runat="server" Text="Tittel"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="title" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="companyLabel" runat="server" Text="Bedrift"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="company" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="cityIDLabel" runat="server" Text="StedID"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:DropDownList ID="dropDownCityList" runat="server" AutoPostBack="true" OnSelectedIndexChanged="dropDownCityList_SelectedIndexChanged"></asp:DropDownList>
                                <asp:Label ID="cityNameLabel" runat="server"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="statusIDLabel" runat="server" Text="StatusID"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:DropDownList ID="dropDownStatusList" runat="server" AutoPostBack="true" OnSelectedIndexChanged="dropDownStatusList_SelectedIndexChanged"></asp:DropDownList>
                                <asp:Label ID="statusNameLabel" runat="server"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="deadlineLabel" runat="server" Text="Søknadsfrist"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="deadline" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="motivationLabel" runat="server" Text="Motivasjon"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="motivation" runat="server" Height="127px" TextMode="MultiLine"></asp:TextBox>
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
