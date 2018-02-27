using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arrays
{
    class Arrays
    {
        static void Main(string[] args)
        {
            int[] numbers = new int[] { 2, 50, 67, 2, 100, 5 };

            // Skrive ut lengden.
            Console.WriteLine("Tabellens lengde: " + numbers.Length);

            // IndexOf()
            int index = Array.IndexOf(numbers, 50);
            Console.WriteLine("Indeksen til 50: " + index);

            // Fjerne elementer hva. metoden Clear():
            Array.Clear(numbers, 0, 3);

            foreach(int val in numbers)
            {
                Console.Write(val + " ");
            }
            Console.WriteLine();

            // Kopiere hele eller deler av en tabell til en ny tabell:
            // Kilde, destinasjon, lendge
            int[] ints = new int[3];
            Array.Copy(numbers, ints, 3);

            Console.WriteLine("Resultat av kopiering:");
            foreach(int i in ints)
            {
                Console.Write(i + " ");
            }
            Console.WriteLine();

            // Sortering
            Array.Sort(numbers);

            Console.WriteLine("Resultater av sortering av den opprinnelige tabellen:");
            foreach (int i in numbers)
                Console.Write(i + " ");

            Console.WriteLine();

            // Reversering. Sorterer tabellen i motsatt rekkefølge slik at det største tallet kommer først.
            Array.Reverse(numbers);
            Console.WriteLine("Resultater av reversering av den opprinnelige tabellen:");
            foreach (int i in numbers)
                Console.Write(i + " ");

            Console.WriteLine();

        }
    }
}
