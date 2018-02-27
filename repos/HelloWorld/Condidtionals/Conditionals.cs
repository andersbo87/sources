using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Condidtionals
{
    public enum Årstid
    {
        vår = 0,
        sommer = 1,
        høst = 2,
        vinter = 3
    }
    class Conditionals
    {
        static void Main(string[] args)
        {
            int hour = 10;
            if(hour > 0 && hour < 12)
            {
                Console.WriteLine("Det er morgen.");
            }
            else if(hour >= 12 && hour < 18)
            {
                Console.WriteLine("Det er ettermiddag.");
            }
            else
            {
                Console.WriteLine("Det er kveld.");
            }

            bool erGodKunde = true;
            double pris;
            if (erGodKunde)
                pris = 19.95;
            else
                pris = 29.95;
            Console.WriteLine(pris);
            // Koden over kan også skrives slik (personen som fant på dette skulle vært skutt!!!)
            // erklære var. sjekke sannhet sann    usann
            double nypris = (erGodKunde) ? 19.95 : 29.95;
            Console.WriteLine(nypris);

            /*
             * Bruker så en switch - case:
             */
            var årstid = Årstid.høst;
            switch (årstid) {
                case Årstid.høst:
                    Console.WriteLine("Det er høst.");
                    break;
                case Årstid.sommer:
                    Console.WriteLine("Det er sommer.");
                    break;
                case Årstid.vinter:
                    Console.WriteLine("Det er vår.");
                    break;
                case Årstid.vår:
                    Console.WriteLine("Det er vår.");
                    break;
                default:
                    break;
            }

            switch (årstid)
            {
                case Årstid.høst:
                case Årstid.sommer:
                    Console.WriteLine("Det er en flott årstid.");
                    break;
                default:
                    break;
            }
        }
    }
}
