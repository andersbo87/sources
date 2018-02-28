using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KursOppgave5
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = "";
            if (args.Count() == 0)
            {
                Console.Write("Skriv inn et navn til en ren tekstfil: ");
                path = Console.ReadLine();
                if(String.IsNullOrWhiteSpace(path))
                {
                    Console.WriteLine("Vennligst angi et filnavn.");
                    return;
                }
            }
            else
            {
                path = args[0];
            }
            if(!fileExists(path))
            {
                Console.WriteLine("Filen {0} finnes ikke.", path);
                return;
            }
            Console.WriteLine("Filen {0} består av {1} ord.", path, countWordsInFile(path));
            Console.WriteLine("Det lengste ordet i filen {0} er {1}.", path, getLongestWordInFile(path));
        }
        static bool fileExists(string fileName)
        {
            return File.Exists(fileName);
        }
        static int countWordsInFile(string fileName)
        {
            int wordCount = 0;
            string[] words = File.ReadAllText(fileName).Split(' ');
            foreach (string word in words)
            {
                if (word.Contains('\n')) // La oss telle newline som nytt ord.
                    wordCount += 2;
                else
                    wordCount++;
            }    
            return wordCount;
        }

        static string getLongestWordInFile(string fileName)
        {
            string longestWord = "";
            int longest = 0;
            string[] words = File.ReadAllText(fileName).Split(' ');
            foreach (string word in words)
            {
                if(word.Length > longest)
                {
                    longestWord = word;
                    longest = word.Length;
                }
            }
            return longestWord;
        }
    }
}
