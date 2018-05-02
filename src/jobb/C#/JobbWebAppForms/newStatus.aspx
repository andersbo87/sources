<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="newStatus.aspx.cs" Inherits="JobbWebAppForms.newStatus" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Sett inn en ny status</title>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <h1>Ny status</h1><br />
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
                    Her kan du legge inn en ny status i databasen. Merk at de fleste mulige statuser allerede er lagt inn i systemet.<br />
                    <br />
                    <asp:Label ID="errorLabel" runat="server" Visible="false" ForeColor="Red" Text="Feil" Font-Bold="true"></asp:Label>
                    <asp:Label ID="successLabel" runat="server" Visible="false" ForeColor="Green" Font-Bold="true"></asp:Label>
                    <table border="0">
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="statusNameLabel" runat="server" Text="Status"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="statusName" runat="server" OnTextChanged="statusName_TextChanged"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Button ID="btnInsertNewStatus" runat="server" Text="Sett inn" OnClick="btnInsertNewStatus_Click"/>
                                <asp:Button ID="btnClear" runat="server" Text="Angre" OnClick="btnClear_Click"/>
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
