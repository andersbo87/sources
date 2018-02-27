using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Threading;

namespace Beginner4
{
    class Beginner4
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
            Console.Write("Skriv inn noen heltall. Bruk tegnet '-' til å skille tallene: ");
            string ans = Console.ReadLine();
            string[] strings = ans.Split('-');
            int[] ints = new int[strings.Length];
            bool isConsecutive = false;
            for(int i = 0; i < strings.Length; i++)
            {
                ints[i] = Convert.ToInt32(strings[i]);
            }
            for(int i = 0; i < ints.Length-1; i++)
            {
                if (ints[i + 1] == ints[i] + 1)
                {
                    isConsecutive = true;
                }
                else if (ints[i + 1] == ints[i] - 1)
                {
                    isConsecutive = true;
                }
                else
                {
                    isConsecutive = false;
                }
            }
            if(isConsecutive)
                Console.WriteLine("Consecutive");
            else
                Console.WriteLine("Not consecutive.");
        }

        static void task2()
        {
            Console.Write("Skriv inn noen heltall. Bruk tegnet '-' til å skille tallene: ");
            string ans = Console.ReadLine();
            if (String.IsNullOrWhiteSpace(ans))
                return;

            string[] strings = ans.Split('-');
            int[] numbers = new int[strings.Length];
            for(int i = 0; i<strings.Length; i++)
            {
                numbers[i] = Convert.ToInt32(strings[i]);
            }

            List<int> numberList = new List<int>();
            foreach(int number in numbers)
            {
                numberList.Add(number);
            }
            if (numberList.Count != numberList.Distinct().Count())
            {
                Console.WriteLine("Duplicate");
            }
            else
            {
                Console.WriteLine("No duplicates.");
            }
        }

        static void task3()
        {
            Console.Write("Skriv inn en tid i 24-timersformatet, slik hh:mm:ss : ");
            string ans = Console.ReadLine();
            if (String.IsNullOrWhiteSpace(ans))
            {
                Console.WriteLine("Invalid time.");
                return;
            }
            try
            {
                string[] time = ans.Split(':');
                int hrs = Convert.ToInt32(time[0]);
                int mins = Convert.ToInt32(time[1]);
                if (hrs >= 0 && hrs <= 23 && mins >= 0 && mins <= 59)
                    Console.WriteLine("OK");
                else
                    Console.WriteLine("Invalid time.");
            }
            catch(Exception)
            {
                Console.WriteLine("Invalid time.");
            }
        }

        static void task4()
        {
            Console.Write("Skriv inn noen ord som er separert av mellomrom: ");
            string ans = Console.ReadLine();
            if(String.IsNullOrWhiteSpace(ans))
            {
                Console.WriteLine("Ugyldig tekst.");
                return;
            }
            /*
             * TextInfo info = CultureInfo.CurrentCulture.TextInfo;
             * ans = info.ToTitleCase(ans).Replace(" ", string.Empty);
            */
            string pascSvar= "";
            foreach(string ord in ans.Split(' '))
            {
                string pascString = char.ToUpper(ord[0]) + ord.ToLower().Substring(1);
                pascSvar += pascString;
            }
            Console.WriteLine(pascSvar);
        }

        static void task5()
        {
            Console.Write("Skriv inn et engelsk ord: ");
            string ans = Console.ReadLine();
            if(string.IsNullOrWhiteSpace(ans))
            {
                Console.WriteLine("Ugyldig tekst.");
                return;
            }
            int vowelCounter = 0;
            foreach(char c in ans)
            {
                if (c == 'a' || c == 'A')
                    vowelCounter++;
                else if (c == 'e' || c == 'E')
                    vowelCounter++;
                else if (c == 'i' || c == 'I')
                    vowelCounter++;
                else if (c == 'o' || c == 'O')
                    vowelCounter++;
                else if (c == 'u' || c == 'U')
                    vowelCounter++;
            }
            /*
             * Alternativ måte:
             * string ans = Console.ReadLine().ToLower();
             * var vowels = new List<char>(new char[] {'a', 'e', 'o', 'u', 'i'});
             * var vowelCounter = 0;
             * foreach (var character in input)
             * {
             *     if (vowels.Contains(character))
             *         vowelCounter++;
             * }
             */
            Console.WriteLine("Ordet {0} består av {1} vokaler.", ans, vowelCounter);
        }
    }
}
