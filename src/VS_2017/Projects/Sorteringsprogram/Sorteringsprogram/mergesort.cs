using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sorteringsprogram
{
    /// <summary>
    /// Mergesort fungerer slik at de usorterte dataene splittes opp for så å settes sammen igjen mens sorteringen foregår.
    /// </summary>
    class mergesort
    {
        private long[] array;
        private long[] tempMergArr;
        private long length;

        private void merge(long lowerIndex, long middle, long higherIndex)
        {
            for (long a = lowerIndex; a <= higherIndex; a++)
            {
                tempMergArr[a] = array[a];
            }
            long i = lowerIndex;
            long j = middle + 1;
            long k = lowerIndex;
            while (i <= middle && j <= higherIndex)
            {
                if (tempMergArr[i] <= tempMergArr[j])
                {
                    array[k] = tempMergArr[i];
                    i++;
                }
                else
                {
                    array[k] = tempMergArr[j];
                    j++;
                }
                k++;
            }
            while (i <= middle)
            {
                array[k] = tempMergArr[i];
                k++;
                i++;
            }

        }
        public void sort(long[] inputArr)
        {
            this.array = inputArr;
            this.length = inputArr.Length;
            this.tempMergArr = new long[length];
            mergeSort(0, length - 1);
        }

        public void mergeSort(long p, long r)
        {
            if (p < r)
            {
                long middle = p + (r - p) / 2;
                // Below step sorts the left side of the array
                mergeSort(p, middle);
                // Below step sorts the right side of the array
                mergeSort(middle + 1, r);
                // Now merge both sides
                merge(p, middle, r);
            }

        }
    }
}
