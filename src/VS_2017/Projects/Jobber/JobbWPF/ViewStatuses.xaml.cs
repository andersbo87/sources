using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace JobbWPF
{
    /// <summary>
    /// Interaction logic for ViewStatuses.xaml
    /// </summary>
    public partial class ViewStatuses : Window
    {
        private string title, statusName;
        private const string primaryKey = "statusID", table="status";
        private int statusID, max, c;
        pgsql p;
        private MainWindow mw = App.mw;
        private bool textChanged = false, opening=false;
        
        private void setStatusID(int newStatusID)
        {
            if (newStatusID <= 0)
                throw new ArgumentException("StatusID må være større enn 0.", newStatusID.ToString());
            if (!p.GetStatusIDs().Contains(newStatusID))
                throw new NoSuchElementException("StatusID nummer " + newStatusID + " finnes ikke i databasen.", newStatusID.ToString());
            statusID = newStatusID;
        }
        private void setStatusName(string newName)
        {
            if (String.IsNullOrWhiteSpace(newName))
                throw new ArgumentException("Den nye statusens navn kan ikke være tomt. Det kan heller ikke bare bestå av mellomrom.", newName);
            statusName = newName;
        }
        private int getStatusID()
        {
            return statusID;
        }
        private string getStatusName()
        {
            return statusName;
        }

        public ViewStatuses(string newTitle)
        {
            InitializeComponent();
            title = newTitle;
            p = mw.ps;
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
            // Denne metoden er kanskje unødvendig, i og med at samme sjekk gjøres i setStatusName over (hvor det kastes et unntak), men man vet jo aldri...
            bool res = true;
            if (String.IsNullOrWhiteSpace(textBoxStatusName.Text))
                res = false;
            return res;
        }

        private void changeStatusID(int idx)
        {
            try
            {
                getData(idx);
                if (idx == Int32.Parse(comboBoxStatusID.Items[0].ToString()))
                {
                    btnPrev.IsEnabled = false;
                    btnFirst.IsEnabled = false;
                    btnNext.IsEnabled = true;
                    btnLast.IsEnabled = true;
                }
                else if (idx == Int32.Parse(comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString()))
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
                setStatusID(idx);
                setChanged(false);
            }
            catch(NoSuchElementException nse)
            {
                MessageBox.Show(nse.Message, title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private bool getData(int index)
        {
            try
            {
                List<string> statusData = p.GetStatuses(index);
                textBoxStatusName.Text = statusData.ElementAt(1);
                comboBoxStatusID.Text = index.ToString();
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

        private void comboBoxStatusID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (!opening)
                {
                    int idx = Int32.Parse(comboBoxStatusID.Text);
                    int newidx = Int32.Parse(comboBoxStatusID.SelectedValue.ToString());
                    if (isChanged() && canSave())
                    {
                        // Spør om endringene skal lagres
                        MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for statusID=" + getStatusID() + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                        {
                            // Lagre endringa og gå videre.
                            if (p.updateStatus(getStatusID(), getStatusName()))
                            {
                                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for statusID " + getStatusID() + ":\nStatus: " + getStatusName(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                                changeStatusID(newidx);
                            }
                            else // Dersom lagringsforsøket gikk galt:
                            {
                                MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Feilmelding: " + p.getError() + " Vil du forkaste endringene og gå videre?", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
                                if (msgUpdateFailed == MessageBoxResult.Yes)
                                {
                                    setChanged(false);
                                    changeStatusID(newidx);
                                }
                            }
                        }
                        else if (msr == MessageBoxResult.No)
                        {
                            // Fortsett uten å lagre.
                            setChanged(false);
                            changeStatusID(newidx);
                        }
                    }
                    else
                        changeStatusID(newidx);
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        private void textBoxStatusName_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                setStatusName(textBoxStatusName.Text);
                setChanged(canSave());
            }
            catch(ArgumentException)
            {
                setChanged(false);
            }
        }

        private void btnFirst_Click(object sender, RoutedEventArgs e)
        {
            comboBoxStatusID.SelectedIndex = 0;
        }

        private void btnPrev_Click(object sender, RoutedEventArgs e)
        {
            int currentApp = comboBoxStatusID.SelectedIndex - 1, counter = 1;
            while (comboBoxStatusID.SelectedIndex - counter == -1)
            {
                counter++;
            }
            comboBoxStatusID.SelectedIndex = comboBoxStatusID.SelectedIndex - counter;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            if (isChanged() && canSave())
            {
                // Spør om endringene skal lagres
                MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for statusID=" + getStatusID() + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                if (msr == MessageBoxResult.Yes)
                {
                    // Lagre endringa og gå videre.
                    if (p.updateStatus(getStatusID(), getStatusName()))
                    {
                        MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for statusID " + getStatusID() + ":\nStatus: " + getStatusName(), title, MessageBoxButton.OK, MessageBoxImage.Information);
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

        private void btnDelete_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult del = MessageBox.Show("Er du sikker på at du vil fjerne statusid " + getStatusID() + " og tilhørende data fra databasen? Dette kan ikke angres!", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
            if (del == MessageBoxResult.Yes)
            {
                if (p.DeleteItem(table, primaryKey, int.Parse(comboBoxStatusID.Text)))
                {
                    MessageBox.Show("Statusen med ID " + getStatusID() + " er nå fjernet fra databasen. Vinduet vil nå lukkes og gjenåpnes.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                    Close();
                    ViewStatuses vs1 = new ViewStatuses(title);
                    vs1.Show();
                }
                else
                    MessageBox.Show("Kunne ikke fjerne statusen fra databasen: " + p.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                opening = true;
                //reopen = false;
                List<string> l = p.GetData("SELECT statusid FROM status ORDER BY statusid asc", 0);
                if (l == null)
                {
                    MessageBox.Show("Kunne ikke opprette liste over registrerte statuser..", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else if (l.Count == 0)
                {
                    MessageBox.Show("Tabellen over registrerte statuser er tom. Vennligst legg inn en søknad og åpne dette vinduet igjen.", Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Close();
                }
                else
                {
                    int i = 0;
                    while (i < l.Count)
                    {
                        comboBoxStatusID.Items.Add(l.ElementAt(i));
                        i++;
                    }
                    max = Int32.Parse(comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString());
                    if (c == 0)
                    {
                        getData(Int32.Parse(comboBoxStatusID.Items[0].ToString()));
                        c++;
                    }
                    if (Int32.Parse(comboBoxStatusID.Text) == Int32.Parse(comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString()))
                    {
                        btnNext.IsEnabled = false;
                        btnLast.IsEnabled = false;
                    }
                    opening = false;
                    setStatusID(1);
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

        private void btnUpdate_Click(object sender, RoutedEventArgs e)
        {
            if (p.updateStatus(getStatusID(), getStatusName()))
            {
                MessageBox.Show("Endringen ble lagret i databasen. Nye verdier for statusID " + getStatusID() + ":\nStatus: " + getStatusName(), title, MessageBoxButton.OK, MessageBoxImage.Information);
                setChanged(false);
            }
            else
            {
                MessageBox.Show(p.getError(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private void btnNext_Click(object sender, RoutedEventArgs e)
        {
            btnFirst.IsEnabled = true;
            btnPrev.IsEnabled = true;
            int currentApp = comboBoxStatusID.SelectedIndex + 1, counter = 1;
            while (comboBoxStatusID.SelectedIndex + counter == -1)
            {
                counter++;
            }
            comboBoxStatusID.SelectedIndex = comboBoxStatusID.SelectedIndex + counter;
        }

        private void btnLast_Click(object sender, RoutedEventArgs e)
        {
            comboBoxStatusID.SelectedIndex = comboBoxStatusID.Items.Count - 1;
        }
    }
}
