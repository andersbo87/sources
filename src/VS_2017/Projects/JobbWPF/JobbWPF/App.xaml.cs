using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace JobbWPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static MainWindow mw;
        [STAThread]
        public static void Main()
        {
            try
            {
                var application = new App();
                mw = new JobbWPF.MainWindow("Jobber");
                application.InitializeComponent();
                application.Run(mw);
            }
            catch(Exception)
            {
                return;
            }
        }
    }
}
