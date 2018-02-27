using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace KursOppgaver
{
    class Beginner1
    {
        static void Main(string[] args)
        {
            task1();
            task2();
            task3();
            task4();
            Thread.Sleep(5000);
        }
        static void task1()
        {
            Console.WriteLine("Type a number between 1 and 10.");
            int number = int.Parse(Console.ReadLine());
            bool valid = number >= 1 && number <= 10;
            if (valid)
                Console.WriteLine("Valid");
            else
                Console.WriteLine("Invalid");
        }

        static void task2()
        {
            Console.WriteLine("Type a number.");
            int number1 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Type another number.");
            int number2 = Convert.ToInt32(Console.ReadLine());
            if(number2 > number1)
            {
                Console.WriteLine(number2);
            }
            else
            {
                Console.WriteLine(number1);
            }
        }
        static void task3()
        {
            Console.WriteLine("Type the width of an image.");
            int width = int.Parse(Console.ReadLine());
            Console.WriteLine("Type the height of the same image.");
            int height = int.Parse(Console.ReadLine());
            if(width > height)
            {
                Console.WriteLine("This is a landscape photo.");
            }
            else
                Console.WriteLine("This is a horizontal image");
        }

        static void task4()
        {
            int penaltyPoints = 0;
            Console.WriteLine("Enter a speed limit");
            int limit = int.Parse(Console.ReadLine());
            Console.WriteLine("Enter the actual speed of the car.");
            int speed = int.Parse(Console.ReadLine());
            if (speed <= limit)
            {
                Console.WriteLine("OK");
            }
            else
            {
                const int pointsPerKm = 5;
                penaltyPoints = (speed - limit) / pointsPerKm;
                if(penaltyPoints > 12)
                {
                    Console.WriteLine("Licence suspended.");
                }
                else
                {
                    Console.WriteLine("Penalty points: " + penaltyPoints);
                }
            }

            /*else if (speed <= limit + 10 && speed >= limit + 5)
            {
                penaltyPoints++;
            }
            else if (speed <= limit + 15 && speed >= limit + 10)
            {
                penaltyPoints += 2;
            }
            else if (speed <= limit + 20 && speed >= limit + 15)
            {
                penaltyPoints += 3;
            }
            else if (speed <= limit + 25 && speed >= limit + 20)
            {
                penaltyPoints += 4;
            }
            else if (speed <= limit + 30 && speed >= limit + 25)
            {
                penaltyPoints += 5;
            }
            else if (speed <= limit + 35 && speed >= limit + 30)
            {
                penaltyPoints += 6;
            }
            else if (speed <= limit + 40 && speed >= limit + 35)
            {
                penaltyPoints += 7;
            }
            else if (speed <= limit + 45 && speed >= limit + 40)
            {
                penaltyPoints += 8;
            }
            else if (speed <= limit + 50 && speed >= limit + 45)
            {
                penaltyPoints += 9;
            }
            else if (speed <= limit + 55 && speed >= limit + 50)
            {
                penaltyPoints += 10;
            }
            else if (speed <= limit + 60 && speed >= limit + 55)
            {
                penaltyPoints += 11;
            }
            else if (speed <= limit + 65 && speed >= limit + 60)
            {
                penaltyPoints += 12;
            }
            else
                penaltyPoints += 13;
            if (penaltyPoints > 12)
            {
                Console.WriteLine("Licence suspended.");
            }*/
        }
    }
}
