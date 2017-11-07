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
    /// Interaction logic for NewCountry.xaml
    /// </summary>
    public partial class NewCountry : Window
    {
        private string countryName, title;
        pgsql p;
        MainWindow mw = App.mw;
        bool textChanged = false, insertButtonClicked = false;
        public NewCountry(string newTitle)
        {
            InitializeComponent();
            title = newTitle;
            p = mw.ps;
        }

        public void setCountryName(string newName)
        {
            countryName = newName;
        }

        public void save()
        {
            textChanged = false;
            insertButtonClicked = true;
            setCountryName(landNavn.Text);
            if (!p.InsertCountry(getCountryName()))
            {
                MessageBox.Show("Kan ikke sette inn det nye landet.", title, MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                MessageBox.Show("Det nye landet \"" + getCountryName() + "\" ble lagret i databasen.", title, MessageBoxButton.OK, MessageBoxImage.Information);
                DialogResult = true;
                Close();
            }
        }

        public string getCountryName()
        {
            return countryName;
        }

        private void btnSave_Click(object sender, RoutedEventArgs e)
        {
            save();
        }

        private void landNavn_TextChanged(object sender, TextChangedEventArgs e)
        {
            textChanged = true;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(insertButtonClicked == true)
            {
                if(getCountryName().Length == 0)
                {
                    MessageBox.Show("Du må angi et unikt landnavn på ett eller flere tegn.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    insertButtonClicked = false;
                    e.Cancel = true;
                }
            }
            else
            {
                if(textChanged)
                {
                    MessageBoxResult msg;
                    msg = MessageBox.Show("Du har endret på teksten i tekstboksen for land. Vil du lagre disse endringene i databasen?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                    if (msg == MessageBoxResult.Yes)
                    {
                        save();
                    }
                    else if (msg == MessageBoxResult.Cancel)
                        e.Cancel = true;
                }
            }
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            insertButtonClicked = false;
            DialogResult = false;
            Close();
        }
    }
}
