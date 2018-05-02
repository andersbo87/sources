<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="viewStatuses.aspx.cs" Inherits="JobbWebAppForms.viewStatuses" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Vis statuser</title>
    <style type="text/css">
        .auto-style1 {
            width: 200px;
        }
    </style>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h1>Registrerte statuser</h1>
            <br />
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
                    <td style="vertical-align:top">
                        Her vil du finne en oversikt over statusene som er registrert i databasen. Du som bruker kommer ikke til å ha mulighet til å gjøre endringer på disse dataene.
                        Velg en søknad fra listeboksen under:<br />
                        <asp:Label ID="errorLabel" runat="server" ForeColor="Red" Visible="false" Text="Feil"></asp:Label>
                        <br />
                        <table border="0">
                            <tr>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="labelStatusID" runat="server" Text="StatusID"></asp:Label>
                                </td>
                                <td style="vertical-align:top;">
                                    <asp:DropDownList ID="statusIDList" runat="server" OnSelectedIndexChanged="statusIDList_SelectedIndexChanged" AutoPostBack="true"></asp:DropDownList>
                                </td>
                            </tr>
                            <tr>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="labelStatus" runat="server" Text="Status"></asp:Label>
                                </td>
                                <td style="vertical-align:top;">
                                    <asp:Label ID="labelStatusValue" runat="server" Text="$verdi"></asp:Label>
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
