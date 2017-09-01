#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define length(a) (sizeof a/sizeof a[0]);

using namespace std;

class binSearch
{
public:
  void input(int ar[], int size)
  {
    // ar = {3,9,42,88,7};
    int i;
    for(i = 0; i < size; i++)
      cin>>ar[i];
  }
  void sort(int ar[], int size)
  {
    fprintf(stdout, "Sorting...\n");
    int tmp;
    int i,j;
    for(i = 0; i < size; i++)
    {
      for(j = 0; j < size-i-1; j++)
      {
	if(ar[j] > ar[j+1])
	{
	  tmp = ar[j];
	  ar[j] = ar[j+1];
	  ar[j+1] = tmp;
	}
      }
    }
  }
  int binarysearch(int ar[], int size, int elm)
  {
    int start = 0, end=size, mid;
    while(start < end)
    {
      mid=(start + end)/2;
      if(ar[mid] == elm)
      {
	return mid;
      }
      else if(ar[mid] < elm)
      {
	start = mid-1;
      }
      else
      {
	end = mid+1;
      }
    }
    return -1;
  }
};

  int main()
  {
    int size;
    printf("Enter the required numbers of elements in the array: ");
    scanf("%d",&size);
    int *ar = new int(size);
    //input(ar,size);
    //ar = {3,9,42,88,7};
    binSearch *bs = new binSearch();
    bs->input(ar, size);
    bs->sort(ar,size);
    int elm = 42;
    int idx = bs->binarysearch(ar, size, elm);
    fprintf(stdout, "Value: %d. Index: %d\n", elm, idx);
    return 0;
  }
