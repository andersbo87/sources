using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sorteringsprogram
{
    class InsertionSort
    {
        public void insertionSort(long []A)
        {
            for(long l = 2; l < A.LongLength; l++)
            {
                long key = A[l];
                long i = l - 1;
                while(i > 0 && A[i] > key)
                {
                    A[i + 1] = A[i];
                    i = i - 1;
                }
                A[i + 1] = key;
            }
        }
    }
}
