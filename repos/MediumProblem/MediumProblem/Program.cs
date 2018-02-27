using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MediumProblem
{
    class Program
    {
        static void Main(string[] args)
        {
            string line;
            int max = Int32.Parse(Console.ReadLine());
            if (max <= 100)
            {
                int i = 0, j=0;
                string firstLine = Console.ReadLine();
                string[] firstSplit = firstLine.Split(new char[] { ' ' }, StringSplitOptions.None);
                int n = Int32.Parse(firstSplit[0]);
                if (1 <= n && n <= 20000)
                {
                    int m = Int32.Parse(firstSplit[1]);
                    if (0 <= m && m <= 50000)
                    {
                        while (i <= max)
                        {
                            line = Console.ReadLine();
                            string[] split = line.Split(new char[] { ' ' }, StringSplitOptions.None);
                            int s1 = Int32.Parse(split[0]);
                            int s2 = Int32.Parse(split[1]);
                            //if (1 <= s1 && s2 <= n && s1 != s2)
                            if(1 <= s1)
                            {
                                if(s2 <= n)
                                {
                                    if (s1 != s2)
                                        j++;
                                }
                                //j++;
                            }
                            i++;
                        }
                        Console.WriteLine(n);
                        Console.WriteLine(j);
                    }
                }
            }
        }
    }
}
