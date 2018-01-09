using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;

namespace JobbWPF
{
    /// <summary>
    /// Interaction logic for NewJob.xaml
    /// </summary>
    public partial class NewApplication : Window
    {
        private MainWindow mw = App.mw;
        private pgsql p;
        private string title, jobTitle, company, deadline, motivation;
        private int townID, statusid;
        private bool textChanged = false, btnSavedClicked = false, btnCancelClicked = false;
        private List<string> statusList, townList;

        /*
         * Hent og sett verdier som er essensielle for å kunne legge inn en ny søknad
         */
        public void setJobTitle(string newTitle)
        {
            jobTitle = newTitle;
        }

        public void setCompany(string newCompany)
        {
            company = newCompany;
        }

        public void setTownID(int newID)
        {
            townID = newID;
        }

        public void setStatusID(int newID)
        {
            statusid = newID;
        }

        public void setDeadline(string newDeadline)
        {
            deadline = newDeadline;
        }

        public void setMotivation(string newMotivation)
        {
            motivation = newMotivation;
        }

        public string getJobTitle()
        {
            return jobTitle;
        }

        public string getCompany()
        {
            return company;
        }

        public int getTownID()
        {
            return townID;
        }

        public int getStatusID()
        {
            return statusid;
        }

        public string getDeadline()
        {
            return deadline;
        }

        public string getMotivation()
        {
            return motivation;
        }
        // Slutt på offentlige metoder som henter og setter verdier.

        private void setChanged(bool changed)
        {
            textChanged = changed;
        }
        private void comboBox_statusID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            setStatusID(int.Parse(comboBox_statusID.SelectedValue.ToString()));
            lbl_statusName.Content = p.getStatusName(int.Parse(comboBox_statusID.SelectedValue.ToString()));
            setChanged(true);
        }
        
        private void comboBox_townID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            setTownID(int.Parse(comboBox_townID.SelectedValue.ToString()));
            lbl_townName.Content = p.getCityName(int.Parse(comboBox_townID.SelectedValue.ToString()));
            setChanged(true);
        }
        
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="newTitle">The title to be used with message boxes.</param>
        public NewApplication(string newTitle)
        {
            title = newTitle;
            p = mw.ps;
            InitializeComponent();
        }

        // Private "drivermetoder"
        void getTownIDList()
        {
            townList = p.GetData("SELECT stedid FROM sted ORDER BY stedid ASC", 0);
            int i = 0;
            while (i < townList.Count)
            {
                comboBox_townID.Items.Add(townList.ElementAt(i));
                i++;
            }
        }

        void getStatusIDList()
        {
            statusList = p.GetData("SELECT statusid FROM status ORDER BY statusid ASC", 0);
            for(int i = 0; i < statusList.Count; ++i)
            {
                comboBox_statusID.Items.Add(statusList.ElementAt(i));
            }
        }

        bool isChanged()
        {
            return textChanged;
        }

        void prepareToSave()
        {
            if (canSave())
            {
                DialogResult = true;
                Close();
            }
            else
                btnSavedClicked = false;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                getTownIDList();
                getStatusIDList();
                btnSavedClicked = false;
                btnCancelClicked = false;
                applicationValue.Focus();
            }
            catch (TimeoutException te)
            {
                MessageBox.Show("Det ser ut som at operasjonen med å hente landID fra databasen timet ut. Er serveren fortsatt online? Feilmeldingen lyder: " + te.Message, title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch (System.Net.Sockets.SocketException se)
            {
                MessageBox.Show("Kan ikke opprette forbindelse med den eksterne serveren. Feilmeldingen lyder: " + se.Message, title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch (Npgsql.NpgsqlException ne)
            {
                MessageBox.Show("Kan ikke hente data. Feilmelding: " + ne.Message, title, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void motivationValue_TextChanged(object sender, TextChangedEventArgs e)
        {
            setMotivation(motivationValue.Text);
            setChanged(true);
        }

        /// <summary>
        /// Sjekke om alle felt er fyllt ut.
        /// </summary>
        /// <returns>True/sann om alle felt er utfylte og vi kan lagre dataen og false/usann ellers.</returns>
        bool canSave()
        {
            // Sjekke om alle felt er fylt inn og består av minst ett tegn.
            try
            {
                if (getJobTitle().Length == 0)
                {
                    MessageBox.Show("Du må angi en jobbtittel med ett eller flere tegn.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return false;
                }
                if (getCompany().Length == 0)
                {
                    MessageBox.Show("Du må angi et bedriftsnavn med én eller flere bokstaver", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return false;
                }
                if (getTownID() == 0)
                {
                    MessageBox.Show("Vennligst velg et stedsnummer fra lista.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return false;
                }
                if (getStatusID() == 0)
                {
                    MessageBox.Show("Vennligst velg et statusnummer fra lista.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return false;
                }
                if (getDeadline().Length == 0)
                {
                    MessageBox.Show("Vennligst angi en søknadsfrist. Dersom det ikke er oppgitt noen frist, kan du skrive \"Snarest\" eller noe tilsvarende i steden.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return false;
                }
            }
            catch(NullReferenceException)
            {
                MessageBox.Show("Alle felt må fylles ut.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return false;
            }
            return true;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(!btnCancelClicked)
            {
                if (btnSavedClicked)
                {
                    if (!canSave())
                    {
                        e.Cancel = true;
                        btnSavedClicked = false;
                    }
                }
                else
                {
                    if (isChanged())
                    {
                        if (canSave())
                        {
                            MessageBoxResult msr = MessageBox.Show("Du har ikke lagret den siste endringa. Vil du gjøre det nå før du lukker vinduet?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                            if (msr == MessageBoxResult.Yes)
                                prepareToSave();
                            else
                                e.Cancel = true;
                        }
                        else
                        {
                            e.Cancel = true;
                        }
                    }
                }
            }
        }

        private void applicationValue_TextChanged(object sender, TextChangedEventArgs e)
        {
            setJobTitle(applicationValue.Text);
            setChanged(true);
        }

        private void deadlineValue_TextChanged(object sender, TextChangedEventArgs e)
        {
            setDeadline(deadlineValue.Text);
            setChanged(true);
        }

        private void companyValue_TextChanged(object sender, TextChangedEventArgs e)
        {
            setCompany(companyValue.Text);
            setChanged(true);
        }

        private void btnSave_Clicked(object sender, RoutedEventArgs e)
        {
            btnSavedClicked = true;
            prepareToSave();
        }

        private void btnCancel_Clicked(object sender, RoutedEventArgs e)
        {
            btnCancelClicked = true;
            Close();
        }
    }
}
