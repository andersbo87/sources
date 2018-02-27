using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Beginner2_Loops
{
    class Beginner2_Loops
    {
        static void Main(string[] args)
        {
            task1();
            task2();
            task3();
            task4();
            task5();
            Thread.Sleep(5000);
        }
        static void task1()
        {
            int counter = 0;
            for (int i = 0; i < 100; i++)
            {
                if (i % 3 == 0)
                    counter++;
            }
            Console.WriteLine(counter);
        }
        static void task2()
        {
            int sum = 0;
            while(true)
            {
                Console.Write("Skriv et tall eller skriv OK for å avslutte: ");
                string res = Console.ReadLine();
                if(res.Equals("OK"))
                {
                    break;
                }
                sum += int.Parse(res);
            }
            Console.WriteLine("Totalt blir summen {0}.", sum);
        }

        static void task3()
        {
            // Poenget med denne metoden er å regne fakultet (X!)
            // F. eks skrives "5 fakultet" 5! og regnes slik: 5*4*3*2*1
            Console.Write("Skriv inn et tall: ");
            int factorial = int.Parse(Console.ReadLine());
            int res = 1;
            for(int i = 1; i <= factorial; i++)
            {
                res = res * i;
            }
            Console.WriteLine("{0}! = {1}", factorial, res);
        }
        static void task4()
        {
            Random r = new Random();
            int corrAnswer = r.Next(1, 10);
            for(int i = 1; i <= 4; i++)
            {
                Console.Write("Skriv inn et nummer mellom 1 og 10. Klarer du å gjette rett, tilfeldig tall? ");
                int userAns = int.Parse(Console.ReadLine());
                if(userAns == corrAnswer)
                {
                    Console.WriteLine("Du vant.");
                    break;
                }
                else
                {
                    Console.WriteLine("Du tapte.");
                }
            }
        }
        static void task5()
        {
            Console.Write("Skriv inn en streng med heltall som skilles med et komma: ");
            string userAns = Console.ReadLine();
            int highest = 0;
            string[] list;
            list = userAns.Split(',');
            foreach(string item in list)
            {
                int number = int.Parse(item);
                if (number > highest)
                    highest = number;
            }
            Console.WriteLine("Highest number: {0}", highest);
        }
    }
}
