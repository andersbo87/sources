using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Iterations
{
    class Iterations
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Skriver ut nummer som er delbare med 2...");
            int i = 0;
            while(i <= 10)
            {
                if(i%2 == 0)
                {
                    Console.WriteLine(i);
                }
                ++i;
            }
            Console.WriteLine("Skriver ut nummer som er delbare med 2 i omvendt rekkefølge...");
            while (i >= 0)
            {
                if(i % 2 == 0)
                {
                    Console.WriteLine(i);
                }
                --i;
            }

            string name = "Heisann";
            for(int j = 0; j < name.Length; j++)
            {
                Console.WriteLine(name[j]);
            }
            foreach(char c in name)
            {
                Console.WriteLine(c);
            }
            int[] integers = new int[6] { 10, 20, 55, 78, 0, 100 };
            foreach(int k in integers)
            {
                Console.Write(k + " ");
            }
            Console.Write("\n");



            while(true)
            {
                Console.Write("Skriv inn navnet ditt: ");
                string res = Console.ReadLine();
                if(string.IsNullOrWhiteSpace(res))
                {
                    break;
                }
                Console.WriteLine("@Echo: " + res);
            }

            while (true)
            {
                Console.Write("Skriv inn navnet ditt: ");
                string res = Console.ReadLine();
                if (!string.IsNullOrWhiteSpace(res))
                {
                    Console.WriteLine("@Echo: " + res);
                    continue;
                }
                break;
            }
        }
    }
}
