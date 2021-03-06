﻿using System;
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
        private string progTitle, companyName, jobTitle, deadline, cityName, statusName, motivation;
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
        
        void setMotivation(string newMotivation)
        {
            motivation = newMotivation;
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

        string getMotivation()
        {
            return motivation;
        }

        private void textBoxJobTitle_TextChanged(object sender, TextChangedEventArgs e)
        {
            setJobTitle(textBoxJobTitle.Text);
        }

        private void textBoxMotivation_TextChanged(object sender, TextChangedEventArgs e)
        {
            setMotivation(textBoxMotivation.Text);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            fillComboBoxCityName();
            fillComboBoxStatusName();
        }

        private void comboBoxCityName_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            setCityName(comboBoxCityName.SelectedItem.ToString());
        }

        private void comboBoxStatusName_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            setStatusName(comboBoxStatusName.SelectedItem.ToString());
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            //dataGrid.Width = this.Width-10;
        }

        private void btnSearch_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                List<jobb> titles = p.getSpecificJobs(getJobTitle(), getCompanyName(), getCityName(), getStatusName(), getDeadline(), getMotivation());
                dataGrid.ItemsSource = titles;
                if (p.getRecord() == 0)
                {
                    titles.Clear();
                    MessageBox.Show("Søket returnerte ingen treff.", progTitle, MessageBoxButton.OK, MessageBoxImage.Information);
                }
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

        private void fillComboBoxCityName()
        {
            try
            {
                List<string> list = p.getCityNames();
                int i = 0;
                while (i < list.Count)
                {
                    comboBoxCityName.Items.Add(list.ElementAt(i));
                    i++;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Noe gikk galt under lasting av eksisterende steder: " + ex.Message, progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void fillComboBoxStatusName()
        {
            try
            {
                List<string> list = p.getStatusNames();
                int i = 0;
                while (i < list.Count)
                {
                    comboBoxStatusName.Items.Add(list.ElementAt(i));
                    i++;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Noe gikk galt under lasting av eksisterende steder: " + ex.Message, progTitle, MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void textBoxDeadline_TextChanged(object sender, TextChangedEventArgs e)
        {
            setDeadline(textBoxDeadline.Text);
        }
    }
}
