using System;

namespace DateAndTime
{
    class DateAndTime
    {
        static void Main(string[] args)
        {
            DateTime dateTime = new DateTime(2018, 02, 26);
            DateTime now = DateTime.Now;
            DateTime today = DateTime.Today;

            Console.WriteLine("Time  : " + now.Hour);
            Console.WriteLine("Minutt: " + now.Minute);
            Console.WriteLine("Sekund: " + now.Second);

            Console.WriteLine("Ukedag: " + now.DayOfWeek);
            Console.WriteLine("Dag   : " + now.Day);
            Console.WriteLine("Måned : " + now.Month);
            Console.WriteLine("År    : " + now.Year);

            // Så fort et DateTime-objekt er opprettet, kan det ikke endres.
            // Skal man gjøre endringer, må man bruke metoden add$hvasomskalleggestil,
            // for eksempel addDays(n), n = antall dager.
            DateTime iMorgen = now.AddDays(1);
            // For å trekke fra en dag, skriver man -n isteden:
            DateTime iGaar = now.AddDays(-1);

            Console.WriteLine(now.ToLongDateString());
            Console.WriteLine(now.ToShortDateString());
            Console.WriteLine(now.ToLongTimeString());
            Console.WriteLine(now.ToShortTimeString());
            Console.WriteLine(now.ToString());

            TimeSpan ts1 = new TimeSpan(1, 2, 3);
            TimeSpan ts2 = TimeSpan.FromHours(1);
            DateTime start = DateTime.Now;
            DateTime end = DateTime.Now.AddMinutes(2);
            TimeSpan duration = end - start;
            Console.WriteLine("Varighet: " + duration);

            // TimeSpan har ulike "egenskaper"
            Console.WriteLine("Minutter              : " + ts1.Minutes);
            Console.WriteLine("Totalt antall minutter: " + ts1.TotalMinutes);

            // Man kan manipulere TimeSpan med metoden Add(), slik som med DateTime over.
            Console.WriteLine("Eksempel med tillegg    : " + ts1.Add(TimeSpan.FromMinutes(10)));
            Console.WriteLine("Eksempel med subtraksjon: " + ts1.Subtract(TimeSpan.FromMinutes(2)));

            // Kovertere TimeSpan til en tekststreng:
            string res = ts1.ToString();
            Console.WriteLine(res);

            // Konvertere til TimeSpan hva Parse
            TimeSpan ts3 = TimeSpan.Parse("11:02:03");
            Console.WriteLine("Resultat etter konvertering (bruker 11 timer istedenfor 1): " + ts3);
        }
    }
}
