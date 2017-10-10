using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sorteringsprogram
{
    class quicksort
    {
        private long partition(long[] arr, long p, long r)
        {
            long x = arr[r];
            long i = p-1;
            long j, tmp1, tmp2;
            for( j = p; j <= r - 1; j++)
            {
                if(arr[j] <= x)
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

        public void sort(long[] arr, long p, long r)
        {
            if(p < r)
            {
                long q = partition(arr, p, r);
                sort(arr, p, q - 1);
                sort(arr, q + 1, r);
            }
        }
    }
}
