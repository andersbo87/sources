using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LettProblem
{
    /*
     * George has bought a pizza. George loves cheese. George thinks the pizza does not have enough cheese. George gets angry.
     * George’s pizza is round, and has a radius of R cm. The outermost C cm is crust, and does not have cheese. What percent of George’s pizza has cheese?
     * Input
     * The input consists of a single line with two space separated integers, R and C.
     * Output
     * Output the percentage of the pizza that has cheese. Your answer must have an absolute or relative error of at most 10−6.
     * Limits 
     * 1≤C≤R≤100
     */
    class Program
    {
        static void Main(string[] args)
        {
            string line;
            while ((line = Console.ReadLine()) != null)
            {
                string[] split = line.Split(new char[] { ' ' }, StringSplitOptions.None);
                float R = float.Parse(split[0]);// Radius
                float C = float.Parse(split[1]); // Området som er uten ost
                if(1 <= C)
                {
                    if(C <= R)
                    {
                        if(R <= 100)
                        {
                            // prosent: PI * (R-C)^2 / (PI*R^2)*100
                            double pct = 3.14 * ((R - C) * (R - C)) / (3.14 * R * R)*100;
                            if(pct == 100)
                            {
                                Console.WriteLine(String.Format("{0:0.000000000}", pct - 100));
                            }
                            else {
                                Console.WriteLine(pct);
                            }
                        }
                    }
                }
            }
        }
    }
}
