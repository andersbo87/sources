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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        MainWindow mw = App.mw;
        pgsql p;
        private string title;
        public Statistics(string newTitle)
        {
            InitializeComponent();
            p = mw.ps;
            title = newTitle;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                totalApplications.Content = p.countTotalApplications();
                totalUnansweredApplications.Content = p.countUnansweredApplications();
                registeredButNotSent.Content = p.countRegisteredNotSentApplications() + p.countWrittenButNotSent();
                totalDeclinedAfterInterviewApplications.Content = p.countDeclinedAfterInterview();
                totalDeclinedApplications.Content = p.countDeclinedApplications() + p.countDeclinedAfterInterview();
                totalSentApplications.Content = p.countUnansweredApplications() + p.countDeclinedApplications() + p.countDeclinedAfterInterview() + p.countAcceptedForInterview() + p.countAcceptedForWork();
                acceptedForInterview.Content = p.countAcceptedForInterview();
                acceptedForWork.Content = p.countAcceptedForWork();
                double percent = (p.countAcceptedForWork() + p.countAcceptedForInterview() + p.countDeclinedAfterInterview() + p.countDeclinedApplications()) / p.countTotalApplications() * 100;
                totalAnsweredApplications.Content = 
                    p.countAcceptedForWork() + 
                    p.countAcceptedForInterview() + 
                    p.countDeclinedAfterInterview() + 
                    p.countDeclinedApplications() +
                    " (" + percent.ToString("N1") + " %)";
            }
            catch(Exception ex)
            {
                MessageBox.Show("Noe er galt: " + ex.Message, title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }
    }
}
