using System;
using System.Collections.Generic;
namespace ProceduralProgramming
{
	public class ProceduralProgramming2
	{
		static void Main(string[] args)
		{
			List<int> liste = new List<int>();
			while (true)
			{
				Console.Write("Vennligst skriv inn et tall: ");
				string ans = Console.ReadLine().ToLower();
				if (string.Compare(ans, "quit") == 0)
				{
					break;
				}
				liste.Add(int.Parse(ans));
			}
			Console.WriteLine("Unike numre:");
			foreach (int i in getUniqueNumbers(liste))
				Console.Write(i + " ");
			Console.WriteLine("");
		}

		static List<int> getUniqueNumbers(List<int> numbers)
		{
			List<int> uniques = new List<int>();
			foreach (int i in numbers)
			{
				if(!uniques.Contains(i))
					uniques.Add(i);
			}
			return uniques;
		}
	}
}
