using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileInputOutput
{
    class Program
    {
        static void Main(string[] args)
        {
            //directoryAndDirectoryInfo();
            sti();
        }

        static void fileAndFileInfo()
        {
            string path = @"C:\Fil.txt";
            File.Copy(@"C:\Fil.txt", @"C:\NyFil.txt", true);
            File.Delete(path);
            if (File.Exists(path))
            {
                // Gjør noe
            }
            string content = File.ReadAllText(path);

            FileInfo fi = new FileInfo(path);
            fi.CopyTo("Nokenfil.txt", true);
            fi.Delete();
            if (fi.Exists)
            {    
                //
            }
        }

        static void directoryAndDirectoryInfo()
        {
            string path = @"D:\Users\andersbo\Pictures";
            string fileType = "*.jpg";
            Directory.CreateDirectory(path);
            string[] files = Directory.GetFiles(path, fileType, SearchOption.AllDirectories);
            foreach(string file in files)
            {
                Console.WriteLine(file);
            }

            string[] mapper = Directory.GetDirectories(path,"*",SearchOption.AllDirectories);
            foreach (string file in mapper)
            {
                Console.WriteLine(file);
            }

            // Det samme kan også oppnås vha DirectoryInfo, slik:
            DirectoryInfo di = new DirectoryInfo(path);
            DirectoryInfo[] nyemapper = di.GetDirectories();
            FileInfo[] nyeFile = di.GetFiles(fileType, SearchOption.AllDirectories);
        }

        // Sti = path
        static void sti()
        {
            string path = @"C:\Users\andersbo\Documents\fil.txt";
            Console.WriteLine("Filtype (forkortelse)" + Path.GetExtension(path));
            Console.WriteLine("Filnavn: " + Path.GetFileName(path));
            Console.WriteLine("Filnavn uten type: " + Path.GetFileNameWithoutExtension(path));
            Console.WriteLine("Mappenavn: " + Path.GetDirectoryName(path));
            Console.WriteLine("Fullt navn: " + Path.GetFullPath(path));

        }
    }
}
