using System;
using System.Collections.Generic;
using System.Data;
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
    class Test
    {
        public string Test1 { get; set; }
        public string Test2 { get; set; }
        public string Test3 { get; set; }
        public string Test4 { get; set; }
        public string Test5 { get; set; }
        public string Test6 { get; set; }
    }
    /// <summary>
    /// Interaction logic for ViewSpecificApplications.xaml
    /// </summary>
    public partial class ViewSpecificApplications : Window
    {
        private string progTitle, companyName, jobTitle, deadline, cityName, statusName;
        private MainWindow mw = App.mw;
        private pgsql p;
        public ViewSpecificApplications(string newTitle)
        {
            InitializeComponent();
            p = mw.ps;
            progTitle = newTitle;
        }

        void setCompanyName(string newName)
        {
            companyName = newName;
        }

        void setJobTitle(string newTitle)
        {
            jobTitle = newTitle;
        }

        void setDeadline(string newDeadline)
        {
            deadline = newDeadline;
        }

        void setCityName(string newName)
        {
            cityName = newName;
        }

        void setStatusName(string newName)
        {
            statusName = newName;
        }
        
        string getJobTitle()
        {
            return jobTitle;
        }

        string getCompanyName()
        {
            return companyName;
        }

        string getCityName()
        {
            return cityName;
        }

        string getStatusName()
        {
            return statusName;
        }

        string getDeadline()
        {
            return deadline;
        }

        private void textBoxJobTitle_TextChanged(object sender, TextChangedEventArgs e)
        {
            setJobTitle(textBoxJobTitle.Text);
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            dataGrid.Width = this.Width-10;
        }

        private void btnSearch_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                List<jobb> titles = p.getSpecificJobs(getJobTitle(), getCompanyName(), getCityName(), getStatusName(), getDeadline());
                if (p.getRecord() == 0)
                    MessageBox.Show("Søket returnerte ingen treff.", progTitle, MessageBoxButton.OK, MessageBoxImage.Information);
                dataGrid.ItemsSource = titles;
                p.setRecord(0);
            }
            catch(System.Net.Sockets.SocketException se)
            {
                MessageBox.Show("Kan ikke koble til serveren. Feilmelding: " + se.Message, progTitle, MessageBoxButton.OK,MessageBoxImage.Error);
                Close();
            }
            catch(TimeoutException te)
            {
                MessageBox.Show("Kan ikke gjennomføre søket fordi det tok for lang tid å kommunisere med serveren. Den er muligens frakoblet? Feilmelding: " + te.Message, progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            catch(Npgsql.NpgsqlException ne)
            {
                MessageBox.Show("Noe gikk galt under søking i databasen: " + ne.Message, progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
            }
            catch(Exception ex)
            {
                MessageBox.Show("Noe gikk galt under søking i databasen: " + ex.Message, progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void textBoxCompanyName_TextChanged(object sender, TextChangedEventArgs e)
        {
            setCompanyName(textBoxCompanyName.Text);
        }

        private void textBoxCityName_TextChanged(object sender, TextChangedEventArgs e)
        {
            setCityName(textBoxCityName.Text);
        }

        private void textBoxStatusName_TextChanged(object sender, TextChangedEventArgs e)
        {
            setStatusName(textBoxStatusName.Text);
        }

        private void textBoxDeadline_TextChanged(object sender, TextChangedEventArgs e)
        {
            setDeadline(textBoxDeadline.Text);
        }
    }
}
