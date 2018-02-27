using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FundamentalsInCSharp
{

    public enum Levering
    {
        RegularAirMail = 1,
        RegisteredAirMail = 2,
        Express = 3
    }

    class FundamentalsInCSharp
    {
        static void Main(string[] args)
        {
            var firstName = "Anders"; // Samme som å skrive "string (eller String) firstName
            var lastName = "Bolt-Evensen"; // Samme som å skrive string (eller String) lastName

            var fullName = firstName + " " + lastName;
            var anotherFullName = string.Format("{0} {1}", firstName, lastName);

            var names = new string[3] { "Anne", "Johanne", "Maria" };
            var namesList = string.Join(", ", names);
            Console.WriteLine(namesList);
            Console.WriteLine(names.First());
            // Jeg bruker @ foran tekststrengen for å forenkle koden (fjerne unødige //, slik at C:\\Users blir til C:\Users isteden)
            var info = @"Hei, Johanne.
Kan du ta en kikk på følgende fil: C:\Users\andersbo\info.txt";
            Console.WriteLine(info);



            Console.WriteLine("\n");
            var metode = Levering.Express;
            Console.WriteLine(metode + " " + (int)metode);
            Console.WriteLine("\n");
            var metodeID = 1;
            Console.WriteLine((Levering)metodeID);

            string name = metode.ToString();
            Console.WriteLine(name);

            var enumName = "RegisteredAirMail";
            var leveringsMetode = (Levering)Enum.Parse(typeof(Levering), enumName);
            Console.WriteLine(leveringsMetode);

            // Heltall og andre primitive datatyper kalles "value types" fordi det er VERDIEN som lagres i
            // minnet. Lager man en kopi, opprettes det en ny plass i minnet.
            // Dette ser vi nedenfor. Her kopierer vi a til b, for så å øke b. Vi ser at a forblir uforandret.
            var a = 10;
            var b = a;
            b++;
            Console.WriteLine(a);

            // Objekter av klasser (inkl. tabeller) er "reference types" fordi disse kopierer adressen til objektet i minnet.
            // Siden det er adressen som kopieres, peker begge "pekerne" på samme objekt i minnet
            // Derfor vil endringer i kopien også endre originalen, som vi ser under:
            var tabell1 = new int[4] { 1, 2, 3, 4 };
            var tabell2 = tabell1;
            tabell2[0] = 5;
            Console.WriteLine(string.Format("tabell1[0]: {0} tabell1[1]: {1} tabell1[2]: {2}tabell1[3]: {3}", tabell1[0], tabell1[1], tabell1[2], tabell1[3]));
            Console.WriteLine(string.Format("tabell2[0]: {0} tabell2[1]: {1} tabell2[2]: {2}tabell2[3]: {3}", tabell2[0], tabell2[1], tabell2[2], tabell2[3]));





            Random r = new Random();
            Console.WriteLine("Noen tilfeldige tall:");
            for(int i = 1; i < 20; i++)
            {
                Console.WriteLine(r.Next());
            }
            Console.WriteLine("Noen tilfeldige små bokstaver:");
            for(int i = 0; i < 10; i++)
            {
                Console.Write((char)('a' + r.Next(0, 26)));
            }
            Console.Write('\n');



            //r = new Random();
            const int passwdLength = 10;
            char[] buffer = new char[passwdLength];
            for(int i = 0; i < passwdLength; i++)
            {
                buffer[i] = (char)('a' + r.Next(0,26));
            }

            string passwd = new string(buffer);
            Console.WriteLine(passwd);
        }
    }
}
