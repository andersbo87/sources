using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace JobbWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // Oppretter pekere til de ulike klassene:
        private pgsql psql;
        private NewApplication na;
        private NewCountry nc;
        private NewStatus ns;
        private NewTown nt;
        private ViewApplications va;
        private ViewCountries vc;
        private ViewSpecificApplications vsa;
        private ViewStatuses vs;
        private ViewTowns vt;
        private Statistics st;
        string title;
        internal pgsql ps { get => psql; set => psql = value; }

        public MainWindow(string newTitle)
        {
            InitializeComponent();
            title = newTitle;
        }

        private void formLoaded(object sender, RoutedEventArgs e)
        {
            initialize();
        }

        private void initialize()
        {
            /*
             * La oss opprette et nytt objekt som peker på klassen ConnectPgsql.
             * Deretter åpner vi dette vinduet som en dialog.
             */
            ConnectPgsql cp = new ConnectPgsql();
            psql = new pgsql(title);
            cp.ShowDialog();
            // Følgende er da en liten smule merkelig måte å gjøre det på, sammenlignet med "gode, gamle" Windows Forms.
            // Koden i testen under sjekker om brukeren har klikket OK.
            if (cp.DialogResult.HasValue && cp.DialogResult.Value)
            {
                try
                {
                    psql.Init();
                }
                catch(Exception e)
                {
                    MessageBox.Show("Kan ikke koble til databasen: " + e.Message, title, MessageBoxButton.OK, MessageBoxImage.Error);
                    initialize();
                }
                if (!psql.tableCountryExists())
                {
                    MessageBox.Show("Tabellen med oversikt over registrerte land finnes ikke. Den vil nå bli opprettet.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    if (!psql.createTableCountries())
                    {
                        MessageBox.Show("Kunne ikke opprette tabellen land: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        Environment.Exit(-1);
                    }
                    else
                    {
                        if(!psql.createProcedureNewCountryID())
                        {
                            MessageBox.Show("Kunne ikke opprette prosedyren land: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                            Environment.Exit(-1);
                        }
                    }
                }
                if (!psql.tableTownExists())
                {
                    MessageBox.Show("Tabellen med oversikt over registrerte steder finnes ikke. Den vil nå bli opprettet.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    if (!psql.createTableTowns())
                    {
                        MessageBox.Show("Kunne ikke opprette tabellen sted: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        Environment.Exit(-1);
                    }
                    else
                    {
                        if (!psql.createProcedureNewTownID())
                        {
                            MessageBox.Show("Kunne ikke opprette prosedyren sted: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                            Environment.Exit(-1);
                        }
                    }
                }
                if (!psql.tableStatusExists())
                {
                    MessageBox.Show("Tabellen med oversikt over registrerte statuser finnes ikke. Den vil nå bli opprettet.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    if (!psql.createTableStatuses())
                    {
                        MessageBox.Show("Kunne ikke opprette tabellen status: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        Environment.Exit(-1);
                    }
                }
                if (!psql.tableApplicationExists())
                {
                    MessageBox.Show("Tabellen med oversikt over registrerte søknader finnes ikke. Den vil nå bli opprettet.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    if (!psql.createTableApplications())
                    {
                        MessageBox.Show("Kunne ikke opprette tabellen søknad: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        Environment.Exit(-1);
                    }
                    else
                    {
                        if (!psql.createProcedureNewApplicationID())
                        {
                            MessageBox.Show("Kunne ikke opprette prosedyren nysoknadid: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                            Environment.Exit(-1);
                        }
                        if (!psql.createProcedureUpdateApplication())
                        {
                            MessageBox.Show("Kunne ikke opprette prosedyren updatesoknad: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                            Environment.Exit(-1);
                        }
                    }
                }
                if (!psql.viewApplicationExists())
                {
                    MessageBox.Show("'Viewet' med oversikt over registrerte søknader finnes ikke. Den vil nå bli opprettet.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    if (!psql.createViewApplications())
                    {
                        MessageBox.Show("Kunne ikke opprette 'viewet' søknad: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        Environment.Exit(-1);
                    }
                }
                if (!psql.viewTownExists())
                {
                    MessageBox.Show("'Viewet' med oversikt over registrerte steder finnes ikke. Den vil nå bli opprettet.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    if (!psql.createViewTown())
                    {
                        MessageBox.Show("Kunne ikke opprette 'viewet' sted: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        Environment.Exit(-1);
                    }
                }
            }
            else
            {
                Environment.Exit(-1);
            }
        }

        private void newApplication_Click(object sender, RoutedEventArgs e)
        {
            na = new NewApplication(title);
            na.ShowDialog();
            if (na.DialogResult.HasValue && na.DialogResult.Value)
            {
                if (psql.InsertApplication(na.getJobTitle(), na.getCompany(), na.getTownID(), na.getStatusID(), na.getDeadline(), na.getMotivation()))
                {
                    MessageBox.Show("Jobben ble lagret med følgende data:\nTittel: " + na.getJobTitle() + "\nBedrift: " + na.getCompany() + "\nSted: " + na.getTownID() + "\nStatus: " + na.getStatusID() + "\nSøknadsfrist: " + na.getDeadline() + "\nMotivasjon: " + na.getMotivation(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Kunne ikke lagre den nye jobben. Feilmelding: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void newCountry_Click(object sender, RoutedEventHandler e)
        {
            nc = new NewCountry(title);
            nc.ShowDialog();
            if(nc.DialogResult.HasValue && nc.DialogResult.Value)
            {
                if(!psql.InsertCountry(nc.getCountryName()))
                {
                    MessageBox.Show("Kunne ikke lagre landet i databasen. Feilmelding: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
                }
                else
                {
                    MessageBox.Show("Landet " + nc.getCountryName() + " ble lagret i databasen.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                }
            }
        }

        private void btn_ViewSpecificApplications_Click(object sender, RoutedEventArgs e)
        {
            vsa = new ViewSpecificApplications(title);
            vsa.Show();
        }

        private void btn_ViewTowns_Click(object sender, RoutedEventArgs e)
        {
            vt = new ViewTowns(title);
            vt.Show();
        }

        private void btn_ViewStatuses_Click(object sender, RoutedEventArgs e)
        {
            vs = new ViewStatuses(title);
            vs.Show();
        }

        private void btn_ViewCountries_Click(object sender, RoutedEventArgs e)
        {
            vc = new ViewCountries(title);
            vc.Show();
        }

        private void btn_ViewApplications_Click(object sender, RoutedEventArgs e)
        {
            va = new ViewApplications(title);
            va.Show();
            if (va.shouldReopen())
                va.Show();
        }

        private void btn_NewTown_Click(object sender, RoutedEventArgs e)
        {
            nt = new NewTown(title);
            nt.ShowDialog();
            if (nt.DialogResult.HasValue && nt.DialogResult.Value)
            {
                if (psql.InsertTown(nt.getTownName(), nt.getCountryID()))
                {
                    MessageBox.Show("Stedet med navnet " + nt.getTownName() + " ble lagret i databasen.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Kunne ikke lagre stedet. Feilmelding: " + psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void btn_NewStatus_Click(object sender, RoutedEventArgs e)
        {
            ns = new NewStatus(title);
            ns.ShowDialog();
            if(ns.DialogResult.HasValue && ns.DialogResult.Value)
            {
                if(!psql.InsertStatus(ns.getStatus()))
                {
                    MessageBox.Show(psql.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
                }
                else
                {
                    MessageBox.Show("Den nye statusen \"" + ns.getStatus() + "\" ble lagret i databasen.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                }
            }
        }

        private void btn_NewCountry_Click(object sender, RoutedEventArgs e)
        {
            nc = new NewCountry(title);
            nc.ShowDialog();
        }

        private void btn_Statistics_Click(object sender, RoutedEventArgs e)
        {
            st = new Statistics(title);
            st.Show();
        }

        private void btn_SaveFile_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
                dlg.DefaultExt = ".sql";
                dlg.Filter = "SQL file (.sql)|*.sql";

                // Hindre en feil i å bli kastet om filen som skal lagres ikke finnes:
                dlg.CheckFileExists = false;
                dlg.CheckPathExists = false;
                if (dlg.ShowDialog() == true)
                {
                    string filename = dlg.FileName;
                    var database = "jobber";
                    var arguments = String.Format(@" -h localhost -d{0} -U{1} -f {2} -w", database, psql.GetUsername(), filename);
                    Process process = new Process();
                    process.StartInfo.UseShellExecute = false;
                    process.StartInfo.EnvironmentVariables["PGPASSWORD"] = psql.GetPassword();
                    process.StartInfo.Arguments = arguments;
                    // Linjen under forutsetter at pg_dump.exe finnes i systemvariabelen PATH
                    process.StartInfo.FileName = "pg_dump.exe";
                    process.Start();
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("Kan ikke starte pg_dump.exe: " + ex.ToString(), title, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
