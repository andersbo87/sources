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
    /// Interaction logic for ViewCountries.xaml
    /// </summary>
    public partial class ViewCountries : Window
    {
        pgsql p;
        MainWindow mw = App.mw;
        private string title, countryName, table="land", primaryKey="landid";
        private int max, c = 0, countryID;
        private bool opening = false, textChanged = false;

        // Konstruktør
        public ViewCountries(string newTitle)
        {
            InitializeComponent();
            p = mw.ps;
            title = newTitle;
        }
        
        private void setCountryID(int newCountryID)
        {
            if (newCountryID <= 0)
                throw new ArgumentException("LandID må være større enn 0", newCountryID.ToString());
            if (!p.GetCountryIDs().Contains(newCountryID))
                throw new NoSuchElementException("Landet med ID " + newCountryID + " finnes ikke i databasen.", newCountryID.ToString());
            countryID = newCountryID;
        }

        private void setCountryName(string newName)
        {
            if (String.IsNullOrWhiteSpace(newName))
                throw new ArgumentException("Det nye navnet kan ikke være tomt eller bare bestå av mellomrom.", newName);
            countryName = newName;
        }

        private int getCountryID()
        {
            return countryID;
        }

        private string getCountryName()
        {
            return countryName;
        }

        // Private metoder
        private void setChanged(bool changed)
        {
            textChanged = changed;
            btnUpdate.IsEnabled = changed;
        }
        bool isChanged()
        {
            return textChanged;
        }
        private bool getData(int index)
        {
            try
            {
                List<string> countryData = p.GetCountries(index);
                textBoxCountryName.Text = countryData.ElementAt(1);
                comboBoxCountryID.Text = index.ToString();
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
            catch (NullReferenceException)
            {
                return false;
            }
            catch (Exception)
            {
                return false;
            }
        }
        private bool getPrev(int index)
        {
            try
            {
                int idx = index;
                btnNext.IsEnabled = true;
                btnLast.IsEnabled = true;
                if (idx >= 1)
                {
                    getData(idx);
                    comboBoxCountryID.Text = idx.ToString();
                    if (idx == 1 || idx == Int32.Parse(comboBoxCountryID.Items[0].ToString()))
                    {
                        btnPrev.IsEnabled = false;
                        btnFirst.IsEnabled = false;
                    }
                    else if (idx == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
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

        private bool getNext(int index)
        {
            int idx = index + 1;
            try
            {
                if (Int32.Parse(comboBoxCountryID.Text) != Int32.Parse(comboBoxCountryID.Items[0].ToString()))
                {
                    btnPrev.IsEnabled = true;
                    btnFirst.IsEnabled = true;
                }
                if (idx <= max)
                {
                    int currentApp = getCountryID(), counter = 1;
                    while (string.Compare(p.getCompany(currentApp + counter), "") == 0)
                    {
                        counter++;
                    }
                    getData(currentApp + counter);
                    if (idx == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
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
                MessageBox.Show("En PostgreSQL-feil har oppstått: " + ne.Message, title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return false;
            }
        }

        private void changeCountryID(int idx)
        {
            try
            {
                getData(idx);
                if (idx == Int32.Parse(comboBoxCountryID.Items[0].ToString()))
                {
                    btnPrev.IsEnabled = false;
                    btnFirst.IsEnabled = false;
                    btnNext.IsEnabled = true;
                    btnLast.IsEnabled = true;
                }
                else if (idx == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
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
                setCountryID(idx);
                setChanged(false);
            }
            catch(NoSuchElementException nse)
            {
                MessageBox.Show(nse.Message, title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private bool canSave()
        {
            bool res = true;
            if (String.IsNullOrWhiteSpace(textBoxCountryName.Text))
                res = false;
            return res;
        }

        // Automatisk genererte private metoder
        private void textBoxCountryName_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                setCountryName(textBoxCountryName.Text);
                setChanged(canSave());
            }
            catch (ArgumentException)
            {
                setChanged(false);
            }
        }

        private void comboBoxCountryID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (!opening)
                {
                    int idx = Int32.Parse(comboBoxCountryID.Text);
                    int newidx = Int32.Parse(comboBoxCountryID.SelectedValue.ToString());
                    if (isChanged() && canSave())
                    {
                        // Spør om endringene skal lagres
                        MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for landID=" + idx + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                        {
                            // Lagre endringa og gå videre.
                            if (p.updateCountry(getCountryID(), getCountryName()))
                            {
                                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for landID " + getCountryID() + ":\nLandnavn: " + getCountryName(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                                changeCountryID(newidx);
                            }
                            else // Dersom lagringsforsøket gikk galt:
                            {
                                MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Feilmelding: " + p.getError() + " Vil du forkaste endringene og gå videre?", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
                                if (msgUpdateFailed == MessageBoxResult.Yes)
                                {
                                    setChanged(false);
                                    changeCountryID(newidx);
                                }
                            }
                        }
                        else if (msr == MessageBoxResult.No)
                        {
                            // Fortsett uten å lagre.
                            setChanged(false);
                            changeCountryID(newidx);
                        }
                    }
                    else
                        changeCountryID(newidx);
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        private void btnFirst_Click(object sender, RoutedEventArgs e)
        {
            comboBoxCountryID.SelectedIndex = 0;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            if (isChanged() && canSave())
            {
                // Spør om endringene skal lagres
                MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for landID=" + getCountryID() + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                if (msr == MessageBoxResult.Yes)
                {
                    // Lagre endringa og gå videre.
                    if (p.updateCountry(getCountryID(), getCountryName()))
                    {
                        MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for landID " + getCountryID() + ":\nLandnavn: " + getCountryName(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                        e.Cancel = false;
                    }
                    else // Dersom lagringsforsøket gikk galt:
                    {
                        MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Feilmelding: " + p.getError() + " Vil du forkaste endringene og gå videre?", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
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

        private void btnPrev_Click(object sender, RoutedEventArgs e)
        {
            int currentApp = comboBoxCountryID.SelectedIndex - 1, counter = 1;
            while (comboBoxCountryID.SelectedIndex - counter == -1)
            {
                counter++;
            }
            comboBoxCountryID.SelectedIndex = comboBoxCountryID.SelectedIndex - counter;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                opening = true;
                //reopen = false;
                List<string> l = p.GetData("SELECT landid FROM land ORDER BY landid asc", 0);
                if (l == null)
                {
                    MessageBox.Show("Kunne ikke opprette liste over registerte land..", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else if (l.Count == 0)
                {
                    MessageBox.Show("Tabellen over land er tom. Vennligst legg inn en søknad og åpne dette vinduet igjen.", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else
                {
                    int i = 0;
                    while (i < l.Count)
                    {
                        comboBoxCountryID.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(comboBoxCountryID.Items[0].ToString()));
                        c++;
                    }
                    if (Int32.Parse(comboBoxCountryID.Text) == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
                    {
                        btnNext.IsEnabled = false;
                        btnLast.IsEnabled = false;
                    }
                    opening = false;
                    setCountryID(1);
                    setChanged(false);
                }
            }
            catch (TimeoutException te)
            {
                MessageBox.Show("En feil oppstod under henting av data. Er serveren fortsatt online? Feilmeldingen lyder slik: " + te.ToString(), title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("En feil har oppstått under henting av data. Er serveren fortsatt online? Feilmeldinga lyder: " + ex.Message, title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
        }

        private void btnDelete_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult del = MessageBox.Show("Er du sikker på at du vil fjerne landid " + getCountryID() + " og tilhørende data fra databasen? Dette kan ikke angres!", title, MessageBoxButton.YesNo,MessageBoxImage.Question);
            if (del == MessageBoxResult.Yes)
            {
                if (p.DeleteItem(table, primaryKey, int.Parse(comboBoxCountryID.Text)))
                {
                    MessageBox.Show("Landet med ID " + getCountryID() + " er nå fjernet fra databasen. Vinduet vil nå lukkes og gjenåpnes.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    Close();
                    ViewCountries vc1 = new ViewCountries(title);
                    vc1.Show();
                }
                else
                    MessageBox.Show("Kunne ikke fjerne landet fra databasen: " + p.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void btnUpdate_Click(object sender, RoutedEventArgs e)
        {
            if(p.updateCountry(getCountryID(), getCountryName()))
            {
                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for landID " + getCountryID() + ":\nLandnavn: " + getCountryName(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                setChanged(false);
            }
            else
            {
                MessageBox.Show(p.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void btnNext_Click(object sender, RoutedEventArgs e)
        {
            btnFirst.IsEnabled = true;
            btnPrev.IsEnabled = true;
            int currentApp = comboBoxCountryID.SelectedIndex + 1, counter = 1;
            while (comboBoxCountryID.SelectedIndex + counter == -1)
            {
                counter++;
            }
            comboBoxCountryID.SelectedIndex = comboBoxCountryID.SelectedIndex + counter;
        }

        private void btnLast_Click(object sender, RoutedEventArgs e)
        {
            comboBoxCountryID.SelectedIndex = comboBoxCountryID.Items.Count - 1;
        }
    }
}
