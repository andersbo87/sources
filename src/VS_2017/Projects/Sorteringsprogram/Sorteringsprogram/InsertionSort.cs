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
            for(long i = 1; i < A.LongLength; i++)
            {
                long key = A[i];
                long j = i - 1;
                while(j >= 0 && key < A[j])
                {
                    A[j + 1] = A[j];
                    j--;
                }
                A[j + 1] = key;
            }
        }
    }
}
