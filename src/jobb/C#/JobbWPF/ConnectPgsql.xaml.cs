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
    /// Interaction logic for ConnectPgsql.xaml
    /// </summary>
    public partial class ConnectPgsql : Window
    {
        pgsql pg;
        MainWindow mw;
        public ConnectPgsql()
        {
            InitializeComponent();
        }

        void login()
        {
            if(server.Text.Length > 0 && username.Text.Length > 0 && pwbox.Password.Length > 0)
            {
                try
                {
                    mw = App.mw;
                    pg = mw.ps;
                    pg.SetPassword(pwbox.Password);
                    pg.SetServer(server.Text);
                    pg.SetUsername(username.Text);
                    pg.login();
                    DialogResult = true;
                }
                catch(Exception e)
                {
                    MessageBox.Show("Kan ikke koble til databasen. Feilmelding: " + e.Message, "Jobber", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void connectPgSql_Load(object sender, RoutedEventArgs e)
        {
            server.Focusable = true;
            Keyboard.Focus(server);
        }

        private void cancelButtonClicked(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void loginButtonClicked(object sender, RoutedEventArgs e)
        {
            login();
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                login();
        }
    }
}
