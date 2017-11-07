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
    /// Interaction logic for ViewTowns.xaml
    /// </summary>
    public partial class ViewTowns : Window
    {
        private string title, townName;
        private const string table = "sted", primaryKey = "stedid";
        private bool opening = false, textChanged = false;
        private int townID, max, c;
        private MainWindow mw = App.mw;
        private pgsql p;
        public ViewTowns(string newTitle)
        {
            title = newTitle;
            InitializeComponent();
            p = mw.ps;
        }
        void setTownID(int newID)
        {
            townID = newID;
        }
        void setTownName(string newName)
        {
            townName = newName;
        }
        int getTownID()
        {
            return townID;
        }
        string getTownName()
        {
            return townName;
        }
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
            catch (Exception)
            {
                return false;
            }
        }
        void changeTownID(int idx)
        {
            getData(idx);
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



        private void textBoxTownName_TextChanged(object sender, TextChangedEventArgs e)
        {
            setTownName(textBoxTownName.Text);
            setChanged(true);
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

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            opening = true;
            //reopen = false;
            List<string> l = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
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
            opening = false;
            setChanged(false);
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
                    MessageBox.Show("Kunne ikke fjerne stedet fra databasen.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }

        private void btnUpdate_Click(object sender, RoutedEventArgs e)
        {
            if (p.updateTown(getTownID(), getTownName()))
            {
                setChanged(false);
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
                    int idx = Int32.Parse(comboBoxTownID.Text);
                    int nyidx = Int32.Parse(comboBoxTownID.SelectedValue.ToString());
                    if (isChanged())
                    {
                        // Spør om endringene skal lagres
                        MessageBoxResult msr = MessageBox.Show("Du har gjort en endring for stedID=" + idx + ". Vil du lagre endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                        {
                            // Lagre endringa og gå videre.
                            if (p.updateTown(getTownID(), getTownName()))
                            {
                                changeTownID(nyidx);
                            }
                            else // Dersom lagringsforsøket gikk galt:
                            {
                                MessageBoxResult msgUpdateFailed = MessageBox.Show("Endringene kunne ikke lagres. Vil du forkaste endringene og gå videre?", title, MessageBoxButton.YesNo, MessageBoxImage.Question);
                                if (msgUpdateFailed == MessageBoxResult.Yes)
                                    changeTownID(nyidx);
                            }
                        }
                        else if (msr == MessageBoxResult.No)
                        {
                            // Fortsett uten å lagre.
                            changeTownID(idx);
                        }
                    }
                    else
                        changeTownID(nyidx);
                }
            }
            catch (Exception)
            {
                return;
            }
        }
    }
}
