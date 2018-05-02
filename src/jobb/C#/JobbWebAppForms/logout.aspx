<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="logout.aspx.cs" Inherits="JobbWebAppForms.logout" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Logget ut</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Label ID="labelInfo" runat="server" Text="$info"></asp:Label><br />
        <asp:HyperLink ID="HyperLink1" runat="server" NavigateUrl="~/login.aspx">HyperLink</asp:HyperLink>
        </div>
    </form>
</body>
</html>
