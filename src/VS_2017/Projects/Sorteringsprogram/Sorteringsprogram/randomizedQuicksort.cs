using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sorteringsprogram
{
    class randomizedQuicksort
    {
        private long partition(long[] arr, long p, long r)
        {
            try
            {
                long x = arr[r];
                long i = p - 1;
                long j, tmp1, tmp2;
                for (j = p; j <= r - 1; j++)
                {
                    if (arr[j] <= x)
                    {
                        i = i + 1;
                        tmp1 = arr[i];
                        tmp2 = arr[j];
                        arr[i] = tmp2;
                        arr[j] = tmp1;
                    }
                }
                tmp1 = arr[i + 1];
                tmp2 = arr[r];
                arr[r] = tmp1;
                arr[i + 1] = tmp2;
                return i + 1;
            }
            catch (Exception e)
            {
                throw e; // Kaster unntaket videre.
            }
        }

        long randomizedPartition(long[] arr, long p, long r)
        {
            try
            {
                LongRandom ra = new LongRandom();
                long l = ra.Next(r - p) + p;
                // Bytter ut arr[r] med arr[l];
                long tmp = arr[r];
                arr[r] = arr[l];
                arr[l] = tmp;
                return partition(arr, p, r);
            }
            catch(Exception e)
            {
                throw e;
            }
        }

        public void randomizedQuickSort(long[] arr, long p, long r)
        {
            if(p < r)
            {
                long q = randomizedPartition(arr, p, r);
                randomizedQuickSort(arr, p, q - 1);
                randomizedQuickSort(arr, q + 1, r);
            }
        }
    }
}
