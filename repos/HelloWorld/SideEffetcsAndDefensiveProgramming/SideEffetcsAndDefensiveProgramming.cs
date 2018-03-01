using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SideEffetcsAndDefensiveProgramming
{
    class SideEffetcsAndDefensiveProgramming
    {
        /*
         * Program som skal vise "side effects" og hvordan man jobber med
         * defensiv programmering. Kode som er kommentert ut er den opprinnelige
         * koden som inneholder flere feil.
         */
        static void Main(string[] args)
        {
            // Opprinnelig kode

            List<int> numbers = new List<int> { 1, 2, 3, 4, 5, 6 };
            List<int> smallests = getSmallests(numbers, 3);
            foreach(var number in numbers)
                Console.WriteLine(number);
        }

        public static List<int> getSmallests(List<int> list, int count)
        {
            // Opprinnelig kode:
            /*
            List<int> smallests = new List<int>();
            while(smallests.Count < count)
            {
                var min = getSmallest(list);
                smallests.Add(min);
                list.Remove(min);
            }
            return smallests;
            */
            if (list == null)
                throw new ArgumentNullException("list", "Du kan ikke sende en ikke-eksisterende liste som argument.");
            if (count > list.Count)
                throw new ArgumentOutOfRangeException("count", "Størrelsen på listen er for liten.");
            else if (count < 1)
                throw new ArgumentOutOfRangeException("count", "Verdien til count må være større enn 0.");
            List<int> smallests = new List<int>();
            List<int> temp = new List<int>(list);
            while (smallests.Count < count)
            {
                var min = getSmallest(temp);
                smallests.Add(min);
                temp.Remove(min);
            }
            return smallests;
        }

        public static int getSmallest(List<int> list)
        {
            // Opprinnelig kode:

            // Anta at det første tallet er det minste
            int min = list[0];
            for(int i = 0; i < list.Count; i++)
            {
                if (list[i] < min)
                    min = list[i];
            }
            return min;
        }
    }
}
