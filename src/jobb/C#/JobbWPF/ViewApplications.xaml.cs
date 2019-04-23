using Npgsql;
using System;
using System.Collections;
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
        private string progTitle, jobTitle, company, deadline, motivation;
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
         * La oss begynne med metoder som setter verdier:
         */
        private void setApplicationID(int newAppliationID)
        {
            if (newAppliationID == 0)
                throw new ArgumentException("SøknadID må være større enn 0.", newAppliationID.ToString());
            ArrayList applicationIDs = p.GetApplicationIDs();
            if (!applicationIDs.Contains(newAppliationID))
                throw new NoSuchElementException("Søknad med ID " + newAppliationID + " finnes ikke i databasen.", newAppliationID.ToString());
            applicationID = newAppliationID;
        }
        
        private void setJobTitle(string newTitle)
        {
            if (String.IsNullOrWhiteSpace(newTitle))
                throw new ArgumentException("Tittelen kan ikke være tom eller bare bestå av mellomrom.", newTitle);
            jobTitle = newTitle;
        }

        private void setCompany(string newCompany)
        {
            if(String.IsNullOrWhiteSpace(newCompany))
                throw new ArgumentException("Bedriftens navn kan ikke være tom eller bare bestå av mellomrom.", newCompany);
            company = newCompany;
        }

        private void setTownID(int newTownID)
        {
            if (newTownID == 0)
                throw new ArgumentException("StedID må være større enn 0.", newTownID.ToString());
            if (!p.GetTownIDs().Contains(newTownID))
                throw new NoSuchElementException("Sted med ID " + newTownID + " finnes ikke i databasen.", newTownID.ToString());
            townID = newTownID;
        }

        private void setStatusID(int newStatusID)
        {
            if (newStatusID == 0)
                throw new ArgumentException("StatusID må være større enn 0.", newStatusID.ToString());
            if (!p.GetStatusIDs().Contains(newStatusID))
                throw new NoSuchElementException("Status med ID " + newStatusID + " finnes ikke i databasen.", newStatusID.ToString());
            statusID = newStatusID;
        }

        private void setCountryID(int townID)
        {
            lblCountryID.Content = p.GetCityCountryID(townID);
        }

        private void setCountryName(int townID)
        {
            lblCountryName.Content = p.GetCountryName(townID);
        }

        private void setDeadline(string newDeadline)
        {
            if(String.IsNullOrWhiteSpace(newDeadline))
                throw new ArgumentException("Søknadsfristen kan ikke være tom eller bare bestå av mellomrom. Er det ikke angitt en søknadsfrist, kan du bruke 'Snarest' eller noe tilsvarende.", newDeadline);
            deadline = newDeadline;
        }

        private void setMotivation(string newMotivation)
        {
            // According to the database definition, motivasjon (motivation) may be null or empty.
            motivation = newMotivation;
        }
        
        private int getApplicationID()
        {
            return applicationID;
        }
        
        private string getJobTitle()
        {
            return jobTitle;
        }

        private string getCompany()
        {
            return company;
        }

        private int getTownID()
        {
            return townID;
        }

        private int getStatusID()
        {
            return statusID;
        }

        private string getDeadline()
        {
            return deadline;
        }

        private string getMotivation()
        {
            return motivation;
        }

        private void setChanged(bool changed)
        {
            contentChanged = changed;
            btnUpdate.IsEnabled = changed;
        }

        private bool isChanged()
        {
            return contentChanged;
        }

        public bool shouldReopen()
        {
            return reopen;
        }

        bool canSave()
        {
            bool res = true;
            if (String.IsNullOrWhiteSpace(textBoxCompany.Text))
                res = false;
            if (String.IsNullOrWhiteSpace(textBoxDeadline.Text))
                res = false;
            if (String.IsNullOrWhiteSpace(textBoxJobTitle.Text))
                res = false;
            return res;
        }

        private void getCities(int index)
        {
            //List<string> cityList = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
            List<string> cityList = p.GetData("SELECT stedsnavn FROM sted ORDER BY stedsnavn asc", 0);
            int i = 0;
            if (comboBoxTownName.Items.Count == 0)
            {
                while (i < cityList.Count)
                {
                    comboBoxTownName.Items.Add(cityList.ElementAt(i));
                    i++;
                }
            }
            //comboBoxTownName.Text = p.GetCityID(index).ToString();
            comboBoxTownName.Text = p.getCityName(p.GetCityID(index));
        }

        private void getStatuses(int index)
        {
            //List<string> statusList = p.GetData("SELECT statusid FROM status order by statusid asc", 0);
            List<string> statusList = p.GetData("SELECT status FROM status ORDER BY status asc", 0);
            int i = 0;
            if (comboBoxStatusName.Items.Count == 0)
            {
                while (i < statusList.Count)
                {
                    comboBoxStatusName.Items.Add(statusList.ElementAt(i));
                    i++;
                }
            }
            //comboBoxStatusName.Text = p.GetStatusID(index).ToString();
            comboBoxStatusName.Text = p.getStatusName(p.GetStatusID(index));
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
                lblCountryID.Content = applicationData.ElementAt(4);
                lblCountryName.Content = applicationData.ElementAt(5);
                textBoxDeadline.Text = applicationData.ElementAt(8);
                textBoxMotivation.Text = applicationData.ElementAt(9);
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
            setApplicationID(idx);
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

        // Automatisk genererte private metoder:
        private void viewApplications_Loaded(object sender, RoutedEventArgs e)
        {
            //try
            //{
                opening = true;
                reopen = false;
                List<string> l = p.GetData("SELECT soknadid FROM view_soknad ORDER BY soknadid asc", 0);
                if(l == null)
                {
                    MessageBox.Show("Kunne ikke opprette liste over sendte/registrerte søknader..", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else if(l.Count == 0)
                {
                    MessageBox.Show("Tabellen over sendte søknader er tom. Vennligst legg inn en søknad og åpne dette vinduet igjen.", Title,MessageBoxButton.OK,MessageBoxImage.Exclamation);
                    Close();
                }
                else
                {
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
                    setApplicationID(1);
                    comboBoxApplicationID.Focus();
                }
            /*}
            catch (TimeoutException te)
            {
                MessageBox.Show("En feil oppstod under henting av data. Er serveren fortsatt online? Feilmeldingen lyder slik: " + te.ToString(), progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("En feil har oppstått under henting av data. Er serveren fortsatt online? Feilmeldinga lyder: " + ex.ToString(), progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }*/
        }

        private void comboBoxApplicationID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (!opening)
                {
                    int newidx = Int32.Parse(comboBoxApplicationID.SelectedValue.ToString());
                    if (isChanged() && canSave())
                    {
                        // Spør om endringene skal lagres
                        MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for sønkadID=" + getApplicationID() + ". Vil du lagre endringa?", progTitle, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                        {
                            // Lagre endringa og gå videre.
                            if (p.updateApplication(getApplicationID(), getJobTitle(), getCompany(), getTownID(), getStatusID(), getDeadline(), getMotivation()))
                            {
                                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for søknadID " + int.Parse(comboBoxApplicationID.Text) + ":\nTittel: " + getJobTitle() + "\nBedrift: " + getCompany() + "\nStedID: " + getTownID() + "\nStatusID: " + getStatusID() + "\nSøknadsfrist: " + getDeadline() + "\nMotivasjon: " + getMotivation(), progTitle, MessageBoxButton.OK, MessageBoxImage.Information);
                                changeApplicationID(newidx);
                            }
                            else
                            {
                                MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Feilmelding: " + p.getError() + " Vil du forkaste endringene og gå videre?", progTitle, MessageBoxButton.YesNo, MessageBoxImage.Question);
                                if (msgUpdateFailed == MessageBoxResult.Yes)
                                {
                                    setChanged(false);
                                    changeApplicationID(newidx);
                                }
                            }
                        }
                        else if (msr == MessageBoxResult.No)
                        {
                            // Fortsett uten å lagre.
                            setChanged(false);
                            changeApplicationID(newidx);
                        }
                    }
                    else
                        changeApplicationID(newidx);
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        private void textBoxJobTitle_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                setJobTitle(textBoxJobTitle.Text);
                setChanged(canSave());
            }
            catch(ArgumentException)
            {
                setChanged(false);
            }
        }

        private void viewApplications_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            if (isChanged() && canSave())
            {
                // Spør om endringene skal lagres
                MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for sønkadID=" + getApplicationID() + ". Vil du lagre endringa?", progTitle, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                if (msr == MessageBoxResult.Yes)
                {
                    // Lagre endringa og gå videre.
                    if (p.updateApplication(getApplicationID(), getJobTitle(), getCompany(), getTownID(), getStatusID(), getDeadline(), getMotivation()))
                    {
                        MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for søknadID " + int.Parse(comboBoxApplicationID.Text) + ":\nTittel: " + getJobTitle() + "\nBedrift: " + getCompany() + "\nStedID: " + getTownID() + "\nStatusID: " + getStatusID() + "\nSøknadsfrist: " + getDeadline() + "\nMotivasjon: " + getMotivation(), progTitle, MessageBoxButton.OK, MessageBoxImage.Information);
                        e.Cancel = false; ;
                    }
                    else
                    {
                        MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Feilmelding: " + p.getError() + " Vil du forkaste endringene og gå videre?", progTitle, MessageBoxButton.YesNo, MessageBoxImage.Question);
                        if (msgUpdateFailed == MessageBoxResult.Yes)
                        {
                            setChanged(false);
                            e.Cancel = false;
                        }
                    }
                }
                else if (msr == MessageBoxResult.No)
                {
                    // Fortsett uten å lagre.
                    setChanged(false);
                    e.Cancel = false;
                }
            }
            else
                e.Cancel = false;
        }

        private void textBoxMotivation_TextChanged(object sender, TextChangedEventArgs e)
        {
            // According to the database definitions, this field may be empty. Therefore, there won't be any validation checks.
            setMotivation(textBoxMotivation.Text);
            setChanged(canSave());
        }

        private void textBoxCompany_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                setCompany(textBoxCompany.Text);
                setChanged(canSave());
            }
            catch(ArgumentException)
            {
                setChanged(false);
            }
        }

        private void comboBoxTownName_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                setTownID(p.GetCityID(comboBoxTownName.SelectedItem.ToString()));
                setChanged(canSave());
                lblCountryID.Content = p.GetCityCountryID(getTownID());
                setCountryName(p.GetCityCountryID(getTownID()));
            }
            catch(NoSuchElementException)
            {
                setChanged(false);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void comboBoxStatusName_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                setStatusID(p.GetStatusID(comboBoxStatusName.SelectedItem.ToString()));
                setChanged(canSave());
            }
            catch(NoSuchElementException)
            {
                setChanged(false);
            }
        }

        private void textBoxDeadline_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                setDeadline(textBoxDeadline.Text);
                setChanged(canSave());
            }
            catch(ArgumentException)
            {
                setChanged(false);
            }
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
            if(p.updateApplication(int.Parse(comboBoxApplicationID.Text), getJobTitle(), getCompany(), getTownID(), getStatusID(), getDeadline(), getMotivation()))
            {
                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for søknadID " + int.Parse(comboBoxApplicationID.Text) + ":\nTittel: " + getJobTitle() + "\nBedrift: " + getCompany() + "\nStedID: " + getTownID() + "\nStatusID: " + getStatusID() + "\nSøknadsfrist: " + getDeadline() + "\nMotivasjon: " + getMotivation(), progTitle, MessageBoxButton.OK, MessageBoxImage.Information);
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
