using System;
using System.Collections.Generic;
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
            string[] strings = Console.ReadLine().Split('-');
            int[] ints = convertToInts(strings);
            if(isConsecutive(ints))
                Console.WriteLine("Consecutive");
            else
                Console.WriteLine("Not consecutive.");
        }

        static bool isConsecutive(int[] intArr)
        {
            bool isConsecutive = false;
            for (int i = 0; i < intArr.Length - 1; i++)
            {
                if (intArr[i + 1] == intArr[i] + 1)
                {
                    isConsecutive = true;
                }
                else if (intArr[i + 1] == intArr[i] - 1)
                {
                    isConsecutive = true;
                }
                else
                {
                    isConsecutive = false;
                    break;
                }
            }
            return isConsecutive;
        }

        static void task2()
        {
            Console.Write("Skriv inn noen heltall. Bruk tegnet '-' til å skille tallene: ");
            string ans = Console.ReadLine();
            if (String.IsNullOrWhiteSpace(ans))
                return;

            string[] strings = ans.Split('-');
            int[] numbers = convertToInts(strings);
            
            List<int> numberList = new List<int>();
            foreach(int number in numbers)
            {
                numberList.Add(number);
            }
            if (checkUnique(numberList))
            {
                Console.WriteLine("Duplicate");
            }
            else
            {
                Console.WriteLine("No duplicates.");
            }
        }

        static int[] convertToInts(string[] arr)
        {
            int[] res = new int[arr.Length];
            for (int i = 0; i < arr.Length; i++)
            {
                res[i] = Convert.ToInt32(arr[i]);
            }
            return res;
        }

        static bool checkUnique(List<int> numbers)
        {
            List<int> unikListe = new List<int>();
            foreach(int i in numbers)
            {
                if (unikListe.Contains(i))
                    return true;
                else
                    unikListe.Add(i);
            }
            return false;
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
            if (timeIsValid(ans))
                Console.WriteLine("OK");
            else
                Console.WriteLine("Invalid time.");
        }

        static bool timeIsValid(string input)
        {
            try
            {
                string[] time = input.Split(':');
                int hrs = Convert.ToInt32(time[0]);
                int mins = Convert.ToInt32(time[1]);
                if (hrs >= 0 && hrs <= 23 && mins >= 0 && mins <= 59)
                    return true;
                else
                    return false;
            }
            catch (Exception)
            {
                return false;
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
            Console.WriteLine(buildPascalString(ans));
        }

        static string buildPascalString(string input)
        {
            string pascSvar = "";
            foreach (string ord in input.Split(' '))
            {
                string pascString = char.ToUpper(ord[0]) + ord.ToLower().Substring(1);
                pascSvar += pascString;
            }
            return pascSvar;
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
            Console.WriteLine("Ordet {0} består av {1} vokaler.", ans, vowelCount(ans));
        }

        static int vowelCount(string word)
        {
            int vowelCounter = 0;
            foreach (char c in word)
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
            return vowelCounter;
        }
    }
}
