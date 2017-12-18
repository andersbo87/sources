using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sorteringsprogram
{
    /*
     * Koden i metodene NextLong og Next er hentet fra https://gist.github.com/subena22jf/c7bb027ea99127944981.
     * Ellers arver denne klassen fra System.Random.
     */
    class LongRandom : Random
    {
        public long NextLong(long min, long max)
        {
            System.Random rd = new System.Random();
            if (max <= min)
                throw new ArgumentOutOfRangeException("max", "max must be greater than min!");
            ulong uRange = (ulong)(max - min);
            ulong ulongRand;
            do
            {
                byte[] buf = new byte[8];
                rd.NextBytes(buf);
                ulongRand = (ulong)BitConverter.ToInt64(buf, 0);
            } while (ulongRand > ulong.MaxValue - ((ulong.MaxValue % uRange) + 1) % uRange);
            return (long)(ulongRand % uRange) + min;
        }

        public long Next(long max)
        {
            return NextLong(0, max);
        }
    }
}
