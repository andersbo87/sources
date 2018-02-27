using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lister
{
    class Lister
    {
        static void Main(string[] args)
        {
            List<int> numbers = new List<int>() { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            numbers.Add(10);
            numbers.AddRange(new int[3] { 11, 12, 13 });
            foreach (int number in numbers)
                Console.Write(number + " ");

            Console.WriteLine();

            int res = numbers.IndexOf(3);
            Console.WriteLine(res);

            int lastRes = numbers.LastIndexOf(3);
            Console.WriteLine("siste indeks av 3: " + lastRes);

            Console.WriteLine("Antall elementer i lista: " + numbers.Count);
            
            for(int i = 0; i < numbers.Count; i++) {
                if(numbers[i] == 2)
                {
                    numbers.Remove(numbers[i]);
                }
            }
            Console.WriteLine("Lista etter fjerning av element 2:");
            foreach (int i in numbers)
                Console.Write(i + " ");
            Console.WriteLine();

            numbers.Clear();
            Console.WriteLine(numbers.Count);
        }
    }
}
