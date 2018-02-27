using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Beginner3
{
    class Beginner3
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
            string str;
            List<string> list = new List<string>();
            int i = 0;
            while(true)
            {
                Console.Write("Skriv inn et navn: ");
                str = Console.ReadLine();
                if (str.Length == 0)
                    break;
                else
                {
                    list.Add(str);
                    i++;
                }
            }
            if(i == 1)
            {
                Console.WriteLine("{0} liker denne posten.", list.ElementAt(0));
            }
            else if(i==2)
            {
                Console.WriteLine("{0} og {1} liker denne posten.", list.ElementAt(0), list.ElementAt(1));
            }
            else if(i > 2)
            {
                Console.WriteLine("{0}, {1} og {2} andre liker denne posten.", list.ElementAt(0), list.ElementAt(1), i-2);
            }
        }

        static void task2()
        {
            Console.Write("Skriv inn navnet ditt: ");
            string name = Console.ReadLine();
            int length = name.Length;
            char[] nameArr = name.ToCharArray();
            Array.Reverse(nameArr);
            string res = new string(nameArr);
            Console.WriteLine(res);
        }

        static void task3()
        {
            const int max = 5;
            int counter = 0;
            List<int> intList = new List<int>();
            while(counter < max)
            {
                Console.Write("Skriv inn et unikt tall: ");
                int ans = int.Parse(Console.ReadLine());
                if(intList.Contains(ans))
                {
                    Console.Write("Tallet dus skrev inn, finnes fra før. Vennligst skriv inn et unikt tall: ");
                    continue;
                }
                else
                {
                    intList.Add(ans);
                    counter++;
                }
            }
            intList.Sort();
            foreach(int i in intList)
            {
                Console.Write(i + " ");
            }
            Console.WriteLine();
        }

        static void task4()
        {
            List<int> liste = new List<int>();
            while(true)
            {
                Console.Write("Vennligst skriv inn et tall: ");
                string ans = Console.ReadLine().ToLower();
                if(string.Compare(ans, "quit") == 0)
                {
                    break;
                }
                int val = int.Parse(ans);
                liste.Add(val);
            }
            foreach(int i in liste.Distinct())
            {
                Console.Write(i + " ");
            }
            Console.WriteLine();
        }

        static void task5()
        {
            Console.Write("Vennligst skriv inn ei liste med kommaseparerte tall: ");
            string ans = Console.ReadLine();
            string[] arr = null;
            if (!String.IsNullOrWhiteSpace(ans))
            {
                arr = ans.Split(',');
                if (arr.Length < 5)
                {
                    Console.WriteLine("Lista er for kort. Vennligst prøv igjen.");
                    task5();
                    return;
                }
                else
                {
                    foreach(string tmp in arr)
                    {
                        if(String.IsNullOrWhiteSpace(tmp))
                        {
                            Console.WriteLine("Ugyldig liste. Vennligst prøv igjen.");
                            task5();
                            return;
                        }
                    }
                }
            }
            else
            {
                Console.WriteLine("Ugyldig liste. Vennligst prøv igjen.");
                task5();
                return;
            }
            List<int> liste = new List<int>();
            for(int i = 0; i < arr.Length; i++)
            {
                liste.Add(int.Parse(arr[i]));
            }
            liste.Sort();
            int smallest = liste.Distinct().ElementAt(0);
            int secSmallest = liste.Distinct().ElementAt(1);
            int thirdSmallest = liste.Distinct().ElementAt(2);
            Console.WriteLine("Listas tre minste tall er {0}, {1} og {2}", smallest, secSmallest, thirdSmallest);
        }
    }
}
