using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextString
{
    public class StringUtility
    {
        public static string summarize(string text, int maksLengde = 20)
        {
            if (text.Length < maksLengde)
            {
                return text;
            }
            string[] ord = text.Split(' ');
            int totalChars = 0;
            List<string> ordListe = new List<string>();
            foreach (string s in ord)
            {
                ordListe.Add(s);
                totalChars += s.Length + 1;
                if (totalChars > maksLengde)
                {
                    break;
                }
            }
            return String.Join(" ", ordListe) + "...";
        }
    }
}
