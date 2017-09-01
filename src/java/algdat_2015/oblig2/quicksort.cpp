#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <unistd.h>
using namespace std;
string status;
int currItem;
int allItems;
int remainingItems;
double percent;
void printInfo(int, int, int);
#ifdef SIGINFO
void catch_siginfo(int sig_num)
{
  signal(SIGINFO, catch_siginfo);
  printInfo(currItem, allItems, remainingItems);
}
void printInfo(int curr, int all, int remaining)
{
  percent = curr/all;
  if(status.compare("partition") == 0)
    fprintf(stdout, "Partition: %d of %d items (%g%% complete -- %d items remaining)\n", curr, all, (((double)curr)/all)*100, remaining);
  else if(status.compare("quicksort") == 0)
    fprintf(stdout, "QuickSorting %d of %d\n", curr, all);
  else
    fprintf(stdout, "Doing an operation\n");
}
#endif
class quickSort
{
public:
  void quicksort(int A[], int p, int r)
  {
    #ifdef SIGINFO
    status = "quicksort";
    currItem = p;
    remainingItems = r;
    signal(SIGINFO, catch_siginfo);
    #endif
    if(p < r){
      int q = partition(A, p, r);
      quicksort(A, p, q-1);
      quicksort(A, q+1, r);
    }
  }
  int partition(int A[], int p, int r){
    #ifdef SIGINFO
    status = "partition";
    currItem = p;
    remainingItems = r;
    signal(SIGINFO, catch_siginfo);
    #endif
    //int x = atoi(A[r].c_str());
    int x = A[r];
    int i = p-1;
    int j, tmp1, tmp2;
    for(j = p; j <= r-1; j++)
    {
      //if(atoi(A[j].c_str()) <= x)
      if(A[j] <= x)
      {
	i = i + 1;
	//tmp1 = atoi(A[i].c_str());
	//tmp2 = atoi(A[j].c_str());
	tmp1 = A[i];
	tmp2 = A[j];
	A[i] = tmp2;
	A[j] = tmp1;
      }
    }
    /*tmp1 = atoi(A[i+1].c_str());
      tmp2 = atoi(A[r].c_str());*/
    tmp1 = A[i+1];
    tmp2 = A[r];
    A[r] = tmp1;
    A[i+1] = tmp2;
    return i + 1;
  }
};
const char *prog_name;
class ArrayIO
{
    string *myString;
public:
    ArrayIO()
    {
        myString = 0x0;
    }
    /**
     * Funksjon som leser tekst fra fil og som kopierer denne teksten i en streng.
     * @param filename Filnavnet det skal leses fra
     * @return En streng med innholdet i filen
     */
    string *readArray(const char *filename)
    {
        /*Les fra fil*/
        ifstream in(filename);
        if(!in)
        {
            fprintf(stderr, "%s: Kan ikke lese filen %s.\n", prog_name, filename);
            exit(1); // avslutter programmet istedenfor å returnere en tom tabell.
        }
        string str2 = " ";
        stringstream buffer;
        buffer << in.rdbuf();
        string test = buffer.str();
        int last = test.size() -1;
        if(last >= 0 && test[last] != ' ') // dersom innholdet i filen ikke ender med mellomrom
        {
            /*
             * Legger til et mellomrom på slutten av strengen.
             * Dette fordi funksjonen genererer en nullpointer dersom strengen ikke ender
             * med et mellomrom. 
             */
            string spc = " ";
            test.append(spc);
        }
        size_t pos1 = 0;
        size_t pos2;
        size_t str_pos1 = 0;// str_pos2;
        int count = 0;
        while((str_pos1 = test.find(str2, str_pos1)) < test.length())
        {
            str_pos1 += str2.length();
            count++;
        }
        static string *str; str = new string[count];
        //fprintf(stdout, "Lengden på tabellen: %d\n", count);
        if(count == 0)
        {
            fprintf(stderr, "%s: Lengden på tabellen er for liten. Lengden på tabellen må være >= 0.\n", prog_name);
            exit(1); // avlsutter programmet istedenfor å returnere en tom tabell.
        }
        for(int x = 0; x < count; x++){
            pos2 = test.find(" ", pos1);
            str[x] = test.substr(pos1, (pos2-pos1));
            //if(x != 0){
            //    long l = strtol(str[x].c_str(), NULL, 10);
            //}
            pos1 = pos2+1;
        }
        myString = str;
        return myString;
    }
};

int main(int argc, const char **argv)
{
  prog_name = "qs";
  quickSort *qs = new quickSort();
  if(argc != 2){
    fprintf(stderr, "usage: qs file\n");
    return 1;
  }
  ArrayIO *aio = new ArrayIO();
  string *a = aio->readArray(argv[1]);
  int l = atoi(a[0].c_str());
  allItems = l;
  int arr[l];
  int i = 0;
  /*Følgende 2 while-løkker skulle optimalt vært plassert i samme
   klasse som readArray, men etter å ha kjørt quicksort gikk arrayen
  "tapt" inne i denne print-funksjonen. (Det er mulig det er min feil.)
  Derfor tar jeg utskriften i main-funksjonen isteden.*/
  while(i<l){
    arr[i] = atoi(a[i+1].c_str());
    i++;
  }
  i = 0;
  while(i<l){
    fprintf(stdout, "%d ", arr[i]);
    i++;
  }
  fprintf(stdout, "\n");
  qs->quicksort(arr,0,l-1);
  fprintf(stdout, "Sortert rekkefølge etter kjøring av quicksort: \n");
  i = 0;
  while(i<l){
    fprintf(stdout, "%d ", arr[i]);
    i++;
  }
  fprintf(stdout, "\n");
}
