using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReferenceTypes
{
    class Person
    {
        public int Alder;
    }
    class ReferenceTypes
    {
        static void Main(string[] args)
        {
            int nr = 1;
            oekAlder(nr);
            Console.WriteLine(nr);

            // En annen måte å vise at et objekt av en klasse er en referansetype
            // (se forklaring under FundamentalsInCSharp/person.cs for forklaring)
            Person person = new Person() { Alder = 30 };
            gjoerGammel(person);
            Console.WriteLine(person.Alder);
        }
        static void oekAlder(int alder)
        {
            alder += 1;
        }

        // Parameteren her er en referansetype ("peker" -- i dette tilfellet til et objekt av klassen Person)
        static void gjoerGammel(Person person)
        {
            person.Alder += 10;
        }
    }
}
