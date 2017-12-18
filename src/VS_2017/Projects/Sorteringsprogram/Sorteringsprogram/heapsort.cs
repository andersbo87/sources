using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sorteringsprogram
{
    class heapsort
    {
        private long heapSize;

        void buildMaxHeap(long[] arr)
        {
            heapSize = arr.LongLength-1;
            for (long i = heapSize / 2; i >= 0; i--)
                maxHeapify(arr, i);
        }

        void swap(long[] arr, long a, long b)
        {
            long tmp = arr[a];
            arr[a] = arr[b];
            arr[b] = tmp;
        }

        void maxHeapify(long[] arr, long index)
        {
            long left = 2 * index;
            long right = 2 * index + 1; 
            long largest = index;

            if(left <= heapSize && arr[left] > arr[index])
            {
                largest = left;
            }

            if (right <= heapSize && arr[right] > arr[largest])
            {
                largest = right;
            }

            if(largest != index)
            {
                swap(arr, index, largest);
                maxHeapify(arr, largest);
            }
        }
        
        public void heapSort(long[] arr)
        {
            buildMaxHeap(arr);
            for (long i = arr.LongLength-1; i >= 0; i--)
            {
                swap(arr, 0, i);
                heapSize--;
                maxHeapify(arr, 0);
            }
        }

        /*private long heapSize;

        private void BuildHeap(long[] arr)
        {
            heapSize = arr.LongLength - 1;
            for (long i = heapSize / 2; i >= 0; i--)
            {
                Heapify(arr, i);
            }
        }

        private void Swap(long[] arr, long x, long y)//function to swap elements
        {
            long temp = arr[x];
            arr[x] = arr[y];
            arr[y] = temp;
        }
        private void Heapify(long[] arr, long index)
        {
            long left = 2 * index;
            long right = 2 * index + 1;
            long largest = index;

            if (left <= heapSize && arr[left] > arr[index])
            {
                largest = left;
            }

            if (right <= heapSize && arr[right] > arr[largest])
            {
                largest = right;
            }

            if (largest != index)
            {
                Swap(arr, index, largest);
                Heapify(arr, largest);
            }
        }
        public void heapSort(long[] arr)
        {
            BuildHeap(arr);
            for (long i = arr.LongLength - 1; i >= 0; i--)
            {
                Swap(arr, 0, i);
                heapSize--;
                Heapify(arr, 0);
            }
            //DisplayArray(arr);
        }*/
    }
}
