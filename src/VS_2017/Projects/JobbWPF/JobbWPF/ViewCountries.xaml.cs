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

        // Offentlige metoder
        public void setCountryID(int newID)
        {
            countryID = newID;
        }

        public void setCountryName(string newName)
        {
            countryName = newName;
        }

        public int getCountryID()
        {
            return countryID;
        }

        public string getCountryName()
        {
            return countryName;
        }

        // Private metoder
        void setChanged(bool changed)
        {
            textChanged = changed;
        }
        bool isChanged()
        {
            return textChanged;
        }
        bool getData(int index)
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

        bool getNext(int index)
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

        void changeCountryID(int idx)
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

        // Automatisk genererte private metoder
        private void textBoxCountryName_TextChanged(object sender, TextChangedEventArgs e)
        {
            setChanged(true);
            setCountryName(textBoxCountryName.Text);
        }

        private void comboBoxCountryID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (!opening)
                {
                    int idx = Int32.Parse(comboBoxCountryID.Text);
                    int nyidx = Int32.Parse(comboBoxCountryID.SelectedValue.ToString());
                    if (isChanged())
                    {
                        // Spør om endringene skal lagres
                        MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for landID=" + idx + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                        {
                            // Lagre endringa og gå videre.
                            if (p.updateCountry(getCountryID(), getCountryName()))
                            {
                                changeCountryID(nyidx);
                            }
                            else // Dersom lagringsforsøket gikk galt:
                            {
                                MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Vil du forkaste endringene og gå videre?", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
                                if (msgUpdateFailed == MessageBoxResult.Yes)
                                    changeCountryID(nyidx);
                            }
                        }
                        else if (msr == MessageBoxResult.No)
                        {
                            // Fortsett uten å lagre.
                            changeCountryID(idx);
                        }
                    }
                    else
                        changeCountryID(nyidx);
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
            opening = true;
            //reopen = false;
            List<string> l = p.GetData("SELECT landid FROM land ORDER BY landid asc", 0);
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
            setChanged(false);
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
                    MessageBox.Show("Kunne ikke fjerne landet fra databasen.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private void btnUpdate_Click(object sender, RoutedEventArgs e)
        {
            if(p.updateCountry(getCountryID(), getCountryName()))
            {
                setChanged(false);
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
