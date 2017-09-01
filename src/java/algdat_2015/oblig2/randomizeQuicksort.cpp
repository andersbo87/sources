#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <unistd.h>

using namespace std;
string status;
const char *prog_name;
int allItems;
ifstream in;
#ifdef SIGINFO
int currItem,  remainingItems;
void printInfo(int, int, int);
void catch_siginfo(int sig_num)
{
  signal(SIGINFO, catch_siginfo);
  printInfo(currItem, allItems, remainingItems);
}

void printInfo(int curr, int all, int remaining)
{
  //percent = curr/all;
  if(status.compare("partition") == 0){
    fprintf(stdout, "Partition: %d of %d items (%g%% complete -- %d items remaining\n", curr, all, (((double)curr)/all)*100, remaining);
  }
  else if(status.compare("quicksort") == 0){
    fprintf(stdout, "quicksorting (randomized) %d of %d\n", curr, all);
  }
  else {
    fprintf(stdout, "Doing some other operation.\n");
  }
}
#endif

// Definisjoner av ulike klasser

// Siden programmet bruker såkalt "randomized" quicksort, må vi kunne
// ha noen metoder for å lage noen tilfeldige tall.
// For å få til dette, lager jeg klassen Random selv.
class Random
{
public:
  Random(unsigned int seed)
  {
    srand(seed);
  }
  Random()
  {
    Random(time(NULL));
  }
  int next(int min, int max)
  {
    return rand() % ((max+1)-min) + min;
  }
  int next(int max)
  {
    return next(0, max);
  }
  int next()
  {
    return next(RAND_MAX);
  }
  double nextDouble()
  {
    return ((double)next() / (double)RAND_MAX);
  }
  float nextFloat()
  {
    return (float)nextDouble();
  }
};


class randomizedQuickSort
{
public:
  void randomizedQuicksort(int A[], int p, int r)
  {
    #ifdef SIGINFO
    status = "quicksort";
    currItem = p;
    remainingItems = r;
    signal(SIGINFO, catch_siginfo);
    #endif
    if(p<r){
      int q = randomizedPartition(A, p, r);
      randomizedQuicksort(A, p, q-1);
      randomizedQuicksort(A, q+1, r);
    }
  }
private:

  // Funksjon som splitter og hersker
  int randomizedPartition(int A[], int p, int r)
  {
    Random *ra = new Random();
    int i = ra->next(r-p)+p;
    int t = A[i];
    int j = A[r];
    A[r] = t;
    A[i] = j;
    return partition(A, p, r);
  }
  int partition(int A[], int p, int r)
  {
    #ifdef SIGINFO
    status = "partition";
    currItem = p;
    remainingItems = r;
    signal(SIGINFO, catch_siginfo);
    #endif
    int x = A[r];
    int i = p-1;
    int j, tmp1, tmp2;
    for(j = p; j <= r-1; j++){
      if(A[j] <= x){
	i = i + 1;
	tmp1 = A[i];
	tmp2 = A[j];
	A[i] = tmp2;
	A[j] = tmp1;
      }
    }
    tmp1 = A[i+1];
    tmp2 = A[r];
    A[r] = tmp1;
    A[i+1] = tmp2;
    return i+1;
  }
};

class ArrayIO
{
private:
  string *myString;
public:
  ArrayIO()
  {
    myString = 0x0;
  }

  string *readArray(const char *filename)
  {
    // Leser innholdet i filen som angis i parameteren filename:
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
      in.open(filename);
      /*if(!in) {
	fprintf(stderr, "%s: Kan ikke lese filen %s.\n", prog_name, filename);
	exit(1);
	}*/
      string str2 = " ";
      stringstream buffer;
      buffer << in.rdbuf();
      string test = buffer.str();
      int last = test.size() -1;
      /* 
	 Sjekker om innholdet i filen ender med et mellomrom.
	 Hvis den ikke gjør det, legges det til et mellomrom på slutten av strengen.
	 Dette fordi funksjonen genererer en nullpointer dersom tekststrengen
	 ikke ender med et mellomrom.
      */
      if(last >= 0 && test[last] != ' ') {
	string spc = " ";
	test.append(spc);
      }
      size_t pos1 = 0, pos2, str_pos1 = 0;
      int count = 0;
      while((str_pos1 = test.find(str2, str_pos1)) < test.length()){
	str_pos1 += str2.length();
	count++;
      }
      static string *str;
      str = new string[count];
      if(count == 0) {
	fprintf(stderr, "%s: Lengden på tabellen er for liten. Den må være >= 1\n", prog_name);
	exit(1);
      }
      for(int x = 0; x < count; x++){
	pos2 = test.find(" ", pos1);
	str[x] = test.substr(pos1, (pos2-pos1));
	pos1 = pos2+1;
      }
      myString = str;
      return myString;
    }
    catch(std::system_error& e){
      string error = prog_name;
      error.append(": Noe gikk galt: ");
      error.append(filename);
      perror(error.c_str());
      exit(1);
    }
    
  }
};

int main(int argc, char **argv)
{
  // Do something...
  prog_name = "rqs";
  randomizedQuickSort *rqs = new randomizedQuickSort();
  ArrayIO *aio = new ArrayIO();
  if(argc != 2){
    fprintf(stderr, "usage: %s file\n", prog_name);
    return 1;
  }
  string *a = aio->readArray(argv[1]);
  int l = atoi(a[0].c_str());
  allItems = l;
  int arr[allItems];
  int i = 0;
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
  rqs->randomizedQuicksort(arr, 0, l-1);
  fprintf(stdout, "Sortert rekkefølge etter kjøring av quicksort (randomized):\n");
  i = 0;
  while(i < l){
    fprintf(stdout, "%d ", arr[i]);
    i++;
  }
  fprintf(stdout, "\n");
  return 0;
}
