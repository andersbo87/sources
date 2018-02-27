using System;

namespace Converters
{
    class Converters
    {
        static void Main(string[] args)
        {
            string st = "1";
            byte b = 1;
            short s = 256;
            int i = 32768;
            long l = 4294967296;


            // konvertere
            short s1 = b;
            short s2 = 200;
            byte b1 = (byte)s; // casting -- vil i dette tilfellet føre til tap av data.
            byte b2 = (byte)s2; // casting -- vil ikke føre til tap av data.
            int res1 = int.Parse(st);
            int res2 = Convert.ToInt32(st); // Samme oppgave som linjen over.
            Console.WriteLine("Viser ulike typer heltall:\nByte: b = {0}\nShort: s = {1}\nVanlig heltall: i = {2}\nLangt heltall: l = {3}", b, s, i, l);
            Console.WriteLine("Viser ulike typer heltall etter konvertering: byte --> short: {0}\nshort --> byte (for stort tall): {1}\nshort --> byte (uten tap av data): {2}\ntekststreng --> vanlig heltall (via int.Parse()): {3}\ntekststreng --> vanlig heltall (vha. Convert.ToInt32()): {4}",s1,b1, b2,res1, res2);
        }
    }
}
