using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Interop;
using System.Windows.Media.Animation;
using System.Diagnostics;

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
                const string settingsFile = @"settings.conf";
                if(File.Exists(settingsFile))
                {
                    // Read the file
                    string content = File.ReadAllText(settingsFile);
                    if (string.Compare(content, "softwareAcceleration: true") == 0)
                    {
                        RenderOptions.ProcessRenderMode = RenderMode.SoftwareOnly;
                    }
                }
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
