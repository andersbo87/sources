using System;
using System.Collections.Generic;
using System.IO;
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
    /// Interaction logic for Settings.xaml
    /// </summary>
    public partial class Settings : Window
    {
        const string settingsFile = @"settings.conf";
        public Settings()
        {
            InitializeComponent();
            if (File.Exists(settingsFile))
            {
                string content = File.ReadAllText(settingsFile);
                if (string.Compare(content, "softwareAcceleration: true") == 0)
                {
                    checkBoxSoftwareAcceleration.IsChecked = true;
                }
                else
                {
                    checkBoxSoftwareAcceleration.IsChecked = false;
                }
            }
        }

        private void writeSettings() { }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!File.Exists(settingsFile))
                {
                    File.Create(settingsFile);
                }
                if (checkBoxSoftwareAcceleration.IsChecked == true)
                {
                    File.WriteAllText(settingsFile, "softwareAcceleration: true");
                }
                else
                {
                    File.WriteAllText(settingsFile, "softwareAcceleration: false");
                }
                Close();
            }
            catch(IOException ioe)
            {
                MessageBox.Show(ioe.ToString());
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
