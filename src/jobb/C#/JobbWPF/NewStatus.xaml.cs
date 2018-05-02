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
    /// Interaction logic for NewStatus.xaml
    /// </summary>
    public partial class NewStatus : Window
    {
        MainWindow mw = App.mw;
        pgsql p;
        private string title, status;
        bool textChanged = false, saveBtnClicked =false;
        public NewStatus(string newTitle)
        {
            InitializeComponent();
            p = mw.ps;
            title = newTitle;
        }

        public void setStatus(string newStatus)
        {
            status = newStatus;
        }

        public void setChanged(bool changed)
        {
            textChanged = changed;
        }

        public string getStatus()
        {
            return status;
        }

        private void prepareToSave()
        {
            saveBtnClicked = true;
            setChanged(false);
            setStatus(statusName.Text);
            DialogResult = true;
            Close();
        }

        private void statusName_TextChanged(object sender, TextChangedEventArgs e)
        {
            setChanged(true);
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(saveBtnClicked == true)
            {
                if(getStatus().Length == 0)
                {
                    MessageBox.Show("Du må oppgi en unik status på ett eller flere tegn.", title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    saveBtnClicked = false;
                    e.Cancel = true;
                }
            }
            else
            {
                if(textChanged)
                {
                    MessageBoxResult mbr = MessageBox.Show("Du har en ulagret endring. Vil du lagre denne nå?", title, MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                    if (mbr == MessageBoxResult.Yes)
                    {
                        prepareToSave();
                    }
                    else if (mbr == MessageBoxResult.Cancel)
                        e.Cancel = true;
                }
            }
        }

        private void btnSave_Click(object sender, RoutedEventArgs e)
        {
            prepareToSave();
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            saveBtnClicked = false;
            DialogResult = false;
            Close();
        }
    }
}
