<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="index.aspx.cs" Inherits="JobbWebAppForms.index" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Jobber</title>
    <link rel="stylesheet" type="text/css" href="/css/main.css" />
    <style type="text/css">
        .auto-style1 {
            width: 200px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
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
                    Hei! Denne siden inneholder data i en PostgreSQL-database med oversikt over jobbsøknader, hvor de skal sendes/er sendt og hvorvidt søknaden er "besvart."<br />
                    Klikk på de ulike lenkene i menyen for å navigere rundt på dette webområdet.
                </td>
            </tr>
        </table>
    </div>
    </form>
</body>
</html>
