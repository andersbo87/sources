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
    /// Interaction logic for NewTown.xaml
    /// </summary>
    public partial class NewTown : Window
    {
        MainWindow mw = App.mw;
        pgsql p;
        private string title, townName;
        private int countryID;
        private bool textChanged = false, btnSaveClicked = false, btnCloseClicked = false;

        void setChanged(bool changed)
        {
            textChanged = changed;
        }
        void fillCountryIDList()
        {
            List<string> countryList = p.GetData("SELECT landid FROM land ORDER BY landid ASC", 0);
            int i = 0;
            while (i < countryList.Count)
            {
                landID.Items.Add(countryList.ElementAt(i));
                ++i;
            }
            //landID.Text = "1";
            //landID.SelectedIndex = 0;
        }

        void setCountryName(int index)
        {
            lblTownName.Content = p.GetCountryName(index);
        }

        public void setCountryID(int newID)
        {
            countryID = newID;
        }

        public void setTownName(string newName)
        {
            townName = newName;
        }

        public int getCountryID()
        {
            return countryID;
        }

        public string getTownName()
        {
            return townName;
        }

        public NewTown(string newTitle)
        {
            InitializeComponent();
            p = mw.ps;
            btnSaveClicked = false;
            title = newTitle;
            fillCountryIDList();
        }

        void prepareToSave()
        {
            btnSaveClicked = true;
            setChanged(false);
            setTownName(townNameText.Text);
            setCountryID((int.Parse(landID.Text)));
            DialogResult = true;
            Close();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(btnSaveClicked == true)
            {
                if (getTownName().Length == 0)
                {
                    MessageBox.Show("Vennligst angi et unikt stedsnavn på ett eller flere tegn.", title, MessageBoxButton.OK,MessageBoxImage.Exclamation);
                    btnSaveClicked = false;
                    e.Cancel = true;
                }
            }
            else
            {
                if(!btnCloseClicked)
                {
                    if (textChanged)
                    {
                        MessageBoxResult msr = MessageBox.Show("Du har en ulagret endring. Vil du lagre denne endringa?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                        if (msr == MessageBoxResult.Yes)
                            prepareToSave();
                        else if (msr == MessageBoxResult.Cancel)
                            e.Cancel = true;
                    }
                }
            }
        }

        private void townNameText_TextChanged(object sender, TextChangedEventArgs e)
        {
            setChanged(true);
        }

        private void landID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            setCountryID(Int32.Parse(landID.SelectedItem.ToString()));
            setChanged(true);
            setCountryName(Int32.Parse(landID.SelectedItem.ToString()));
        }

        private void btnSave_Click(object sender, RoutedEventArgs e)
        {
            prepareToSave();
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            btnSaveClicked = false;
            btnCloseClicked = true;
            DialogResult = false;
            Close();
        }
    }
}
