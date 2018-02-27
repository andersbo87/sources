using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextString
{
    class TextString
    {
        static void Main(string[] args)
        {
            string fullName = "Anders Bolt-Evensen ";
            Console.WriteLine("Trim: '{0}'", fullName.Trim());
            Console.WriteLine("ToUpper: '{0}'", fullName.Trim().ToUpper());

            // Bruk av metoden IndexOf():
            int idx = fullName.IndexOf(' ');
            string firstName = fullName.Substring(0, idx);
            string lastName = fullName.Substring(idx + 1);
            Console.WriteLine("Fornavn  : {0}\nEtternavn: {1}", firstName, lastName);

            // Bruk av metoden Split():
            string[] names = fullName.Split(' ');
            Console.WriteLine("Fornavn  : {0}\nEtternavn: {1}", names[0], names[1]);

            // Bruk av metoden Replace():
            Console.WriteLine(fullName.Replace("Bolt", "Skrue"));

            // Sjekke om en tekstreng finnes, er tom eller bare har mellomrom:
            if(String.IsNullOrWhiteSpace(" "))
                Console.WriteLine("Ugyldig tekststreng.");

            // Kovertering
            // Fra streng til byte:
            string str = "30";
            byte age1 = 0;
            byte age2 = 0;
            age1 = Convert.ToByte(str);
            age2 = Byte.Parse(str);

            // Fra tall til streng:
            float pris = 29.70f;
            string str2 = pris.ToString("C");
            string str3 = pris.ToString("C0");
            Console.WriteLine(str2);
            Console.WriteLine(str3);



            string setning = "Dette er en veldig, fryktelig, forferdelig kjeeeeeeeeempelang tekst.";
            Console.WriteLine(StringUtility.summarize(setning, 45));

            StringBuilder sb = new StringBuilder("Hello, world");

            sb
                .Append('-', 10)
                .AppendLine()
                .Append("Header")
                .AppendLine()
                .Append('-', 10)
                .Replace('-', '+')
                .Remove(0, 10)
                .Insert(0, new string('-', 10));
            Console.WriteLine(sb);
        }
    }
}
