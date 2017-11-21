using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
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
    /// Interaction logic for ViewApplications.xaml
    /// </summary>
    public partial class ViewApplications : Window
    {
        private string progTitle, jobTitle, company, deadline;
        private int applicationID, townID, max, statusID, c = 0;
        private pgsql p;
        private MainWindow mw = App.mw;
        private const string table = "soknad", primaryKey = "soknadid";
        private bool opening = false, reopen=false, contentChanged = false;
        public ViewApplications(string newTitle)
        {
            p = mw.ps;
            progTitle = newTitle;
            InitializeComponent();
        }

        /*
         * Metoder som henter og setter verdier
         * etter den objektorienterte tenkemåten.
         * 
         * La oss begynne med metoder som setter verdier:
         */
        public void setApplicationID(int newID)
        {
            applicationID = newID;
        }
        
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
            statusID = newID;
        }

        public void setDeadline(string newDeadline)
        {
            deadline = newDeadline;
        }

        /*
         * Og deretter: Offentlige metoder som henter verdier:
         */
        
        public int getApplicationID()
        {
            return applicationID;
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
            return statusID;
        }

        public string getDeadline()
        {
            return deadline;
        }

        public void setChanged(bool changed)
        {
            contentChanged = changed;
        }

        public bool isChanged()
        {
            return contentChanged;
        }

        public bool shouldReopen()
        {
            return reopen;
        }

        // Private metoder som ikke er generert automatisk:
        private void setTownName(int index)
        {
            lblTownName.Content = p.getCityName(index);
        }

        private void setStatusName(int index)
        {
            lblStatusName.Content = p.getStatusName(index);
        }

        private void getCities(int index)
        {
            List<string> cityList = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
            int i = 0;
            if (comboBoxTownID.Items.Count == 0)
            {
                while (i < cityList.Count)
                {
                    comboBoxTownID.Items.Add(cityList.ElementAt(i));
                    i++;
                }
            }
            comboBoxTownID.Text = p.GetCityID(index).ToString();
        }

        private void getStatuses(int index)
        {
            List<string> statusList = p.GetData("SELECT statusid FROM status order by statusid asc", 0);
            int i = 0;
            if (comboBoxStatusID.Items.Count == 0)
            {
                while (i < statusList.Count)
                {
                    comboBoxStatusID.Items.Add(statusList.ElementAt(i));
                    i++;
                }
            }
            comboBoxStatusID.Text = p.GetStatusID(index).ToString();
        }

        /// <summary>
        /// Fills the labels, comboboxes and text boxes with information about current application based on the application ID.
        /// </summary>
        /// <param name="index">The identification number of the job application in question.</param>
        private bool getData(int index)
        {
            try
            {
                List<string> applicationData = p.GetApplications(index);
                textBoxJobTitle.Text = applicationData.ElementAt(0);
                textBoxCompany.Text = applicationData.ElementAt(1);
                lblTownName.Content = applicationData.ElementAt(3);
                lblCountryID.Content = applicationData.ElementAt(4);
                lblCountryName.Content = applicationData.ElementAt(5);
                lblStatusName.Content = applicationData.ElementAt(7);
                textBoxDeadline.Text = applicationData.ElementAt(8);
                comboBoxApplicationID.Text = index.ToString();
                return true;
            }
            catch (InvalidOperationException)
            {
                return false;
            }
            catch (System.FormatException)
            {
                return false;
            }
            catch(NullReferenceException)
            {
                return false;
            }
            catch(Exception)
            {
                return false;
            }
        }

        private void changeApplicationID(int idx)
        {
            //int idx = Int32.Parse(comboBoxApplicationID.SelectedItem.ToString());
            getData(idx);
            getCities(idx);
            getStatuses(idx);
            if (idx == Int32.Parse(comboBoxApplicationID.Items[0].ToString()))
            {
                btnPrev.IsEnabled = false;
                btnFirst.IsEnabled = false;
                btnNext.IsEnabled = true;
                btnLast.IsEnabled = true;
            }
            else if (idx == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString()))
            {
                btnNext.IsEnabled = false;
                btnLast.IsEnabled = false;
                btnFirst.IsEnabled = true;
                btnPrev.IsEnabled = true;
            }
            else
            {
                // Mulig de fire neste linjene er unødige:
                btnNext.IsEnabled = true;
                btnLast.IsEnabled = true;
                btnPrev.IsEnabled = true;
                btnFirst.IsEnabled = true;
            }
            setChanged(false);
        }

        bool getNext(int index)
        {
            int idx = index+1;
            try
            {
                if (Int32.Parse(comboBoxApplicationID.Text) != Int32.Parse(comboBoxApplicationID.Items[0].ToString()))
                {
                    btnPrev.IsEnabled = true;
                    btnFirst.IsEnabled = true;
                }
                if (idx <= max)
                {
                    int currentApp = getApplicationID(), counter = 1;
                    while(string.Compare(p.getCompany(currentApp + counter), "") == 0)
                    {
                        counter++;
                    }
                    getData(currentApp + counter);
                    getCities(idx);
                    getStatuses(idx);
                    //comboBoxApplicationID.Text = idx.ToString();
                    if (idx == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString()))
                    {
                        btnLast.IsEnabled = false;
                        btnNext.IsEnabled = false;
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (SocketException)
            {
                return false;
            }
            catch (NpgsqlException ne)
            {
                MessageBox.Show("En PostgreSQL-feil har oppstått: " + ne.Message, progTitle, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return false;
            }
        }
        bool getPrev(int index)
        {
            try
            {
                int idx = index;
                btnNext.IsEnabled = true;
                btnLast.IsEnabled = true;
                if (idx >= 1)
                {
                    getData(idx);
                    comboBoxApplicationID.Text = idx.ToString();
                    if (idx == 1 || idx == Int32.Parse(comboBoxApplicationID.Items[0].ToString()))
                    {
                        btnPrev.IsEnabled = false;
                        btnFirst.IsEnabled = false;
                    }
                    else if (idx == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString()))
                    {
                        btnLast.IsEnabled = false;
                        btnNext.IsEnabled = false;
                    }
                    return true;
                }
                else
                    return false;
            }
            catch (SocketException)
            {
                return false;
            }
            catch (Exception)
            {
                return getPrev(index - 1);
            }
        }

        private void viewApplications_Closed(object sender, EventArgs e)
        {
            
        }

        // Automatisk genererte private metoder:
        private void viewApplications_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                opening = true;
                reopen = false;
                List<string> l = p.GetData("SELECT soknadid FROM view_soknad ORDER BY soknadid asc", 0);
                int i = 0;
                while (i < l.Count)
                {
                    comboBoxApplicationID.Items.Add(l.ElementAt(i));
                    i++;
                }
                max = Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString());
                if (c == 0)
                {
                    getData(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
                    c++;
                }
                getCities(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
                getStatuses(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
                if (Int32.Parse(comboBoxApplicationID.Text) == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString()))
                {
                    btnNext.IsEnabled = false;
                    btnLast.IsEnabled = false;
                }
                opening = false;
                setChanged(false);
            }
            catch (TimeoutException te)
            {
                MessageBox.Show("En feil oppstod under henting av data. Er serveren fortsatt online? Feilmeldingen lyder slik: " + te.ToString(), progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("En feil har oppstått under henting av data. Er serveren fortsatt online? Feilmeldinga lyder: " + ex.Message, progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
        }

        private void comboBoxApplicationID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (!opening)
                {
                    int idx = Int32.Parse(comboBoxApplicationID.Text);
                    int nyidx = Int32.Parse(comboBoxApplicationID.SelectedValue.ToString());
                    if (isChanged())
                    {
                        // Spør om endringene skal lagres
                        MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for sønkadID=" + idx + ". Vil du lagre endringa?", progTitle, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                        {
                            // Lagre endringa og gå videre.
                            if (p.updateApplication(idx, getJobTitle(), getCompany(), getTownID(), getStatusID(), getDeadline()))
                            {
                                changeApplicationID(nyidx);
                            }
                            else
                            {
                                MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Vil du forkaste endringene og gå videre?", progTitle, MessageBoxButton.YesNo, MessageBoxImage.Question);
                                if (msgUpdateFailed == MessageBoxResult.Yes)
                                    changeApplicationID(nyidx);
                            }
                        }
                        else if (msr == MessageBoxResult.No)
                        {
                            // Fortsett uten å lagre.
                            changeApplicationID(idx);
                        }
                    }
                    else
                        changeApplicationID(nyidx);
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        private void textBoxJobTitle_TextChanged(object sender, TextChangedEventArgs e)
        {
            setJobTitle(textBoxJobTitle.Text);
            setChanged(true);
        }

        private void textBoxCompany_TextChanged(object sender, TextChangedEventArgs e)
        {
            setCompany(textBoxCompany.Text);
            setChanged(true);
        }

        private void comboBoxTownID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            setTownID(Int32.Parse(comboBoxTownID.SelectedItem.ToString()));
            setChanged(true);
            setTownName(Int32.Parse(comboBoxTownID.SelectedItem.ToString()));
        }

        private void comboBoxStatusID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            setStatusID(Int32.Parse(comboBoxStatusID.SelectedItem.ToString()));
            setChanged(true);
            setStatusName(Int32.Parse(comboBoxStatusID.SelectedItem.ToString()));
        }

        private void textBoxDeadline_TextChanged(object sender, TextChangedEventArgs e)
        {
            setDeadline(textBoxDeadline.Text);
            setChanged(true);
        }

        private void btnFirst_Click(object sender, RoutedEventArgs e)
        {
            comboBoxApplicationID.SelectedIndex = 0;
        }

        private void btnPrev_Click(object sender, RoutedEventArgs e)
        {
            int currentApp = comboBoxApplicationID.SelectedIndex - 1, counter = 1;
            while (comboBoxApplicationID.SelectedIndex - counter == -1)
            {
                counter++;
            }
            comboBoxApplicationID.SelectedIndex = comboBoxApplicationID.SelectedIndex - counter;
        }

        private void btnDel_Click(object sender, RoutedEventArgs e)
        {
            if (p.DeleteItem(table, primaryKey, int.Parse(comboBoxApplicationID.Text)))
            {
                reopen = true;
                Close();
                ViewApplications va1 = new ViewApplications(progTitle);
                va1.Show();
            }
            else
                MessageBox.Show("Noe gikk galt uder sletting av søknad: " + p.getError(), progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
        }

        private void btnUpdate_Click(object sender, RoutedEventArgs e)
        {
            if(p.updateApplication(int.Parse(comboBoxApplicationID.Text), getJobTitle(), getCompany(), getTownID(), getStatusID(), getDeadline()))
            {
                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for søknadID " + int.Parse(comboBoxApplicationID.Text) + ":\nTittel: " + getJobTitle() + "\nBedrift: " + getCompany() + "\nStedID: " + getTownID() + "\nStatusID: " + getStatusID() + "\nSøknadsfrist: " + getDeadline(), progTitle, MessageBoxButton.OK, MessageBoxImage.Information);
                setChanged(false);
            }
            else
            {
                MessageBox.Show(p.getError(), progTitle, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private void btnNext_Click(object sender, RoutedEventArgs e)
        {
            int currentApp = comboBoxApplicationID.SelectedIndex+1, counter = 1;
            while(comboBoxApplicationID.SelectedIndex+counter == -1)
            {
                counter++;
            }
            comboBoxApplicationID.SelectedIndex = comboBoxApplicationID.SelectedIndex+counter;
        }

        private void btnLast_Click(object sender, RoutedEventArgs e)
        {
            comboBoxApplicationID.SelectedIndex = comboBoxApplicationID.Items.Count-1;
        }
    }
}
