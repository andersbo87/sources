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
    /// Interaction logic for ViewTowns.xaml
    /// </summary>
    public partial class ViewTowns : Window
    {
        private string title, townName;
        private const string table = "sted", primaryKey = "stedid";
        private bool opening = false, textChanged = false;
        private int townID, max, c, countryID;
        private MainWindow mw = App.mw;
        private pgsql p;
        public ViewTowns(string newTitle)
        {
            title = newTitle;
            InitializeComponent();
            p = mw.ps;
        }
        private void setTownID(int newTownID)
        {
            if (newTownID == 0)
                throw new ArgumentException("StedID kan ikke være lik 0.", newTownID.ToString());
            if (!p.GetTownIDs().Contains(newTownID))
                throw new NoSuchElementException("StedID med verdi " + newTownID + " finnes ikke i databasen.", newTownID.ToString());
            townID = newTownID;
        }

        private void setCountryID(int newCountryID)
        {
            if (newCountryID <= 0)
                throw new ArgumentException("LandID må være større enn 0.", newCountryID.ToString());
            if (!p.GetCountryIDs().Contains(newCountryID))
                throw new NoSuchElementException("Denne land-id-en finnes ikke i databasen.");
            countryID = newCountryID;
        }

        private int getCountryID()
        {
            return countryID;
        }

        private void setTownName(string newName)
        {
            if (string.IsNullOrWhiteSpace(newName))
                throw new ArgumentException("Det nye bynavnet kan ikke bare bestå av mellomrom eller være tomt.", newName);
            townName = newName;
        }
        private int getTownID()
        {
            return townID;
        }
        private string getTownName()
        {
            return townName;
        }
        private void setChanged(bool changed)
        {
            textChanged = changed;
            btnUpdate.IsEnabled = changed;
        }
        private bool isChanged()
        {
            return textChanged;
        }
        private bool canSave()
        {
            if (String.IsNullOrWhiteSpace(textBoxTownName.Text))
                return false;
            return true;
        }
        private bool getData(int index)
        {
            try
            {
                List<string> townData = p.GetCities(index);
                textBoxTownName.Text = townData.ElementAt(1);
                comboBoxTownID.Text = index.ToString();
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
            catch(Npgsql.NpgsqlException)
            {
                MessageBox.Show("Kan ikke utføre henteoperasjonen. Feilmelding: " + p.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
                return false;
            }
            catch (Exception)
            {
                return false;
            }
        }
        private void changeTownID(int idx)
        {
            if (getData(idx))
            {
                fillCountryList(idx);
                if (idx == Int32.Parse(comboBoxTownID.Items[0].ToString()))
                {
                    btnPrev.IsEnabled = false;
                    btnFirst.IsEnabled = false;
                    btnNext.IsEnabled = true;
                    btnLast.IsEnabled = true;
                }
                else if (idx == Int32.Parse(comboBoxTownID.Items[comboBoxTownID.Items.Count - 1].ToString()))
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
                setTownID(idx);
                setChanged(false);
            }
            else
            {
                MessageBox.Show("Kan ikke utføre henteoperasjonen: " + p.getError(), title, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }



        private void textBoxTownName_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                setTownName(textBoxTownName.Text);
                setChanged(canSave());
            }
            catch (ArgumentException)
            {
                setChanged(false);
            }
            
        }

        private void btnFirst_Click(object sender, RoutedEventArgs e)
        {
            comboBoxTownID.SelectedIndex = 0;
        }

        private void btnPrev_Click(object sender, RoutedEventArgs e)
        {
            int currentApp = comboBoxTownID.SelectedIndex - 1, counter = 1;
            while (comboBoxTownID.SelectedIndex - counter == -1)
            {
                counter++;
            }
            comboBoxTownID.SelectedIndex = comboBoxTownID.SelectedIndex - counter;
        }

        private void fillCountryList(int index)
        {
            if(comboBoxCountry.Items.Count == 0)
            {
                List<string> countryList = p.GetData("SELECT land FROM land ORDER BY land", 0);
                if (countryList == null)
                {
                    MessageBox.Show("Kunne ikke opprette liste over registrerte steder.", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else if (countryList.Count == 0)
                {
                    MessageBox.Show("Tabellen over registrerte steder er tom. Vennligst legg inn en søknad og åpne dette vinduet igjen.", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else
                {
                    int i = 0;
                    while (i < countryList.Count)
                    {
                        comboBoxCountry.Items.Add(countryList.ElementAt(i));
                        i++;
                    }
                }
            }
            comboBoxCountry.Text = p.GetCountryName(p.GetCityCountryID(index));
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                opening = true;
                //reopen = false;
                List<string> l = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
                if (l == null)
                {
                    MessageBox.Show("Kunne ikke opprette liste over registrerte steder.", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else if (l.Count == 0)
                {
                    MessageBox.Show("Tabellen over registrerte steder er tom. Vennligst legg inn en søknad og åpne dette vinduet igjen.", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else
                {
                    int i = 0;
                    while (i < l.Count)
                    {
                        comboBoxTownID.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(comboBoxTownID.Items[comboBoxTownID.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(comboBoxTownID.Items[0].ToString()));
                        c++;
                    }
                    if (Int32.Parse(comboBoxTownID.Text) == Int32.Parse(comboBoxTownID.Items[comboBoxTownID.Items.Count - 1].ToString()))
                    {
                        btnNext.IsEnabled = false;
                        btnLast.IsEnabled = false;
                    }
                    fillCountryList(Int32.Parse(comboBoxTownID.Items[0].ToString()));
                    opening = false;
                    setTownID(1);
                    setChanged(false);
                }
            }
            catch (TimeoutException te)
            {
                MessageBox.Show("En feil oppstod under henting av data. Er serveren fortsatt online? Feilmeldingen lyder slik: " + te.Message, title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch (SocketException se)
            {
                MessageBox.Show("Kan ikke opprette forbindelse med den eksterne serveren. Feilmeldingen lyder: " + se.Message, title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("En feil har oppstått under henting av data. Feilmeldinga lyder: " + ex.ToString(), title, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            int newidx = Int32.Parse(comboBoxTownID.SelectedValue.ToString());
            if (isChanged() && canSave())
            {
                // Spør om endringene skal lagres
                MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for stedID=" + getTownID() + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                if (msr == MessageBoxResult.Yes)
                {
                    // Lagre endringa og gå videre.
                    if (p.updateTown(getTownID(), getTownName(), getCountryID()))
                    {
                        MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for stedID " + getTownID() + "\nStedsnavn: " + getTownName() + "\nLandID: " + getCountryID(), title, MessageBoxButton.OK, MessageBoxImage.Information);
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

        private void comboBoxCountry_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                setCountryID(p.getCountryID(comboBoxCountry.SelectedItem.ToString()));
                setChanged(canSave());
            }
            catch(ArgumentException)
            {
                setChanged(false);
            }
            catch(NoSuchElementException nse)
            {
                MessageBox.Show(nse.Message, title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                setChanged(false);
            }
        }

        private void btnDelete_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult del = MessageBox.Show("Er du sikker på at du vil fjerne stedid " + getTownID() + " og tilhørende data fra databasen? Dette kan ikke angres!", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
            if (del == MessageBoxResult.Yes)
            {
                if (p.DeleteItem(table, primaryKey, int.Parse(comboBoxTownID.Text)))
                {
                    MessageBox.Show("Stedet med ID " + getTownID() + " er nå fjernet fra databasen. Vinduet vil nå lukkes og gjenåpnes.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    Close();
                    ViewTowns vt1 = new ViewTowns(title);
                    vt1.Show();
                }
                else
                    MessageBox.Show("Kunne ikke fjerne stedet fra databasen. Feilmeldinga lyder som følger: " + p.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private void btnUpdate_Click(object sender, RoutedEventArgs e)
        {
            if (p.updateTown(getTownID(), getTownName(), getCountryID()))
            {
                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for stedID " + getTownID() + ":\nStedsnavn: " + getTownName() + "\nLandID: " + getCountryID(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                setChanged(false);
            }
            else
            {
                MessageBox.Show("En feil oppstod under oppdatering av byen: " + p.getError(), title, MessageBoxButton.OK);
            }
        }

        private void btnNext_Click(object sender, RoutedEventArgs e)
        {
            btnFirst.IsEnabled = true;
            btnPrev.IsEnabled = true;
            int currentApp = comboBoxTownID.SelectedIndex + 1, counter = 1;
            while (comboBoxTownID.SelectedIndex + counter == -1)
            {
                counter++;
            }
            comboBoxTownID.SelectedIndex = comboBoxTownID.SelectedIndex + counter;
        }

        private void btnLast_Click(object sender, RoutedEventArgs e)
        {
            comboBoxTownID.SelectedIndex = comboBoxTownID.Items.Count - 1;
        }

        private void comboBoxTownID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (!opening)
                {
                    int newidx = Int32.Parse(comboBoxTownID.SelectedValue.ToString());
                    if (isChanged() && canSave())
                    {
                        // Spør om endringene skal lagres
                        MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for stedID=" + getTownID() + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                        {
                            // Lagre endringa og gå videre.
                            if (p.updateTown(getTownID(), getTownName(), getCountryID()))
                            {
                                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for stedID " + getTownID() + ":\nStedsnavn: " + getTownName() + "\nLandID: " + getCountryID(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                                changeTownID(newidx);
                            }
                            else // Dersom lagringsforsøket gikk galt:
                            {
                                MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Feilmelding: " + p.getError() + " Vil du forkaste endringene og gå videre?", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
                                if (msgUpdateFailed == MessageBoxResult.Yes)
                                {
                                    setChanged(false);
                                    changeTownID(newidx);
                                }
                            }
                        }
                        else if (msr == MessageBoxResult.No)
                        {
                            // Fortsett uten å lagre.
                            setChanged(false);
                            changeTownID(newidx);
                        }
                    }
                    else
                        changeTownID(newidx);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return;
            }
        }
    }
}
