using System;

namespace ProceduralProgramming
{
	class ProceduralProgramming
	{
		/*public static void Main(string[] args)
		{
			Console.WriteLine("Hello World!");
			Console.Write("Hva heter du? ");
			string res = Console.ReadLine();
			Console.WriteLine("I reversert rekkefølge blir navnet ditt " + reverseUsername(res));
		}*/

		static string reverseUsername(string name)
		{
			char[] array = new char[name.Length];
			for (int i = name.Length; i > 0; i--)
			{
				array[name.Length - i] = name[i - 1];
			}
			return new string(array);
		}
	}
}
