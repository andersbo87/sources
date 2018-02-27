using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stringCmp
{
    class Program
    {
        static void Main(string[] args)
        {
            // Internal strings that will never be localized.
            string root = @"C:\users";
            string root2 = @"C:\Users";

            // Use the overload of the Equals method that specifies a StringComparison.
            // Ordinal is the fastest way to compare two strings.
            bool result = root.Equals(root2, StringComparison.Ordinal);

            Console.WriteLine("Ordinal comparison: {0} and {1} are {2}", root, root2,
                                result);
        }
    }
}
