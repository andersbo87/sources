using System;

namespace Operations
{
    class Lister
    {
        static void Main(string[] args)
        {
            double a = 10.3;
            int b = 3;
            Console.WriteLine("a = 10,3 b = 3");
            Console.WriteLine("a + b: {0}", a + b);
            Console.WriteLine("a - b: {0}", a - b);
            Console.WriteLine("Vanlig divisjon: a / b: {0}", a / b);
            int i = 10;
            b = 3;
            Console.WriteLine("i = 10 b = 3");
            Console.WriteLine("i * b: {0}", i * b);
            Console.WriteLine("Heltallsdivisjon: i / b: {0}", i / b);
            Console.WriteLine("i mod b: {0}", i % b);


            Console.WriteLine("Presedens: a = 1, b = 2, c = 3. Utfører: a + b * c");
            a = 1;
            b = 2;
            int c = 3;
            Console.WriteLine("a + b * c = {0}",a + b * c);
            Console.WriteLine("For at addisjonen skal gå foran multiplikasjon, må man bruke parentes: (a + b) * c");
            Console.WriteLine("(a + b) * c: {0}", (a +b ) * c);

            Console.WriteLine("Påstand: a er større enn b: {0}", a > b);
            Console.WriteLine("Påstand: a er lik b: {0}", a == b);
            Console.WriteLine("Påstand: c er større enn b og c er større enn a: {0}", c > b && c > a);
            Console.WriteLine("Påstand: c er større enn b og c er lik a: {0}", c > b && c == a);
            Console.WriteLine("Påstand: c er større enn b eller c er lik a: {0}", c > b || c == a);
            Console.WriteLine("Påstand: c er større enn b eller c er større enn a: {0}", c > b || c > a);
        }
    }
}
