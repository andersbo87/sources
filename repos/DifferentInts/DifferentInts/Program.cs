using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DifferentInts
{
    class Program
    {
        static void Main(string[] args)
        {
            string line;
            while((line=Console.ReadLine()) != null)
            {
                string[] split = line.Split(new char[] { ' ' }, StringSplitOptions.None);
                long a = long.Parse(split[0]), b = long.Parse(split[1]);
                if(a-b < 0)
                {
                    Console.WriteLine(Math.Abs(b - a));
                }
                else
                {
                    Console.WriteLine(Math.Abs(a - b));
                }
            }
        }
    }
}
