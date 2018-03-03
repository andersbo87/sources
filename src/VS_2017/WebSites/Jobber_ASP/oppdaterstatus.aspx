﻿<%@ Page Language="C#" AutoEventWireup="true" CodeFile="oppdaterstatus.aspx.cs" Inherits="oppdaterstatus" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Endre eller slett status</title>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <h1>Endre eller slett status</h1><br />
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
                    Her kan du oppdatere landene som er registrert i databasen.
                    <br />
                    <br />
                    <asp:Label ID="successLabel" Visible="false" runat="server" ForeColor="Green" Font-Bold="true"></asp:Label>
                    <asp:Label ID="errorLabel" runat="server" Visible="false" ForeColor="Red" Font-Bold="true"></asp:Label>
                    <table border="0">
                        <tr>
                            <td style="vertical-align:top">
                                <asp:DropDownList ID="statusIDDropDownList" runat="server" AutoPostBack="true" OnSelectedIndexChanged="statusIDDropDownList_SelectedIndexChanged"></asp:DropDownList>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="lblStatusID" runat="server" Text="StatusID"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="textBoxStatusID" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td style="vertical-align:top">
                                <asp:Label ID="lblStatusName" runat="server" Text="Status"></asp:Label>
                            </td>
                            <td style="vertical-align:top">
                                <asp:TextBox ID="textBoxStatusName" runat="server"></asp:TextBox>
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
                    <asp:Button ID="btnYes" runat="server" OnClick="btnYes_Click" Text="Ja" Visible="False" />
                    <asp:Button ID="btnNo" runat="server" OnClick="btnNo_Click" Text="Nei" Visible="False" />
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