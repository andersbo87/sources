<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="updateCountry.aspx.cs" Inherits="JobbWebAppForms.updateCountry" %>

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
                    Her kan du oppdatere landene som er registrert i databasen.
                    <br />
                    <br />
                    <asp:Label ID="successLabel" Visible="false" runat="server" ForeColor="Green" Font-Bold="true"></asp:Label>
                    <asp:Label ID="errorLabel" runat="server" Visible="false" ForeColor="Red" Font-Bold="true"></asp:Label>
                    <table border="0">
                        <tr>
                            <td style="vertical-align:top">
                                <asp:DropDownList ID="countryDropDownList" runat="server" AutoPostBack="true" OnSelectedIndexChanged="countryDropDownList_SelectedIndexChanged"></asp:DropDownList>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="countryIDLabel" runat="server" Text="LandID"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="countryID" runat="server" ></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="countryNameLabel" runat="server" Text="Navn"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="countryName" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Button ID="btnUpdate" runat="server" Text="Oppdater" OnClick="btnUpdate_Click" />
                                <asp:Button ID="btnDelete" runat="server" Text="Slett" OnClick="btnDelete_Click" />
                                <asp:Button ID="btnCancel" runat="server" Text="Avbryt" />
                            </td>
                        </tr>
                    </table>

                    <br />
                    <br />
                    <asp:Label ID="labelRemoveData" runat="server" Text="Label" Visible="False"></asp:Label>
                    <br />
                    <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="Ja" Visible="False" />
                    <asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="Nei" Visible="False" />

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
