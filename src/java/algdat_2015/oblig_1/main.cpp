#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <assert.h>
using namespace std;
const char *progname = "main";

class Matrix
{
public:
  double **m;
  int n;
  /*oppretter en nxn-matrise*/
  Matrix(int n)
  {
    this->m = new double*[n*n];
    this->n = n;
  }
  /*Oppretter en ny dataspesifisert matrise*/
  Matrix(int n, double** m)
  {
    long m_length = sizeof(m)/4;
    assert(n*n==m_length);
    this->m = m;
    this->n = n;
  }
  /*Returnerer elementet på rad i og kolonne j.*/
  double get(int i,  int j){
    assert(i>= 0 && i<n && j>= 0 && j<n);
    return *m[i*n+j];
  }
  /*Setter elementet på rad i og kolonne j til x.*/
  void set(int i, int j, double x){
    assert(i>=0 && i<n && j>=0 && j<n);
    *m[i*n+j] = x;
  }
  /*Partisjonerer en matrise til fire nye delmatriser med størrelse n/2 x n/2.
    Det allokeres nytt minne for hver delmatrise og innholdet fra 
    foreldrematrisen kopieres inn.*/
  Matrix **partition(){
    int partN = n/2;
    Matrix **parts;
    parts[0] = new Matrix(partN);
    parts[1] = new Matrix(partN);
    parts[2] = new Matrix(partN);
    parts[3] = new Matrix(partN);
    if(parts[4] != 0x0)
      parts[4] = 0x0;
    int i,j,p;
    long parts_length = sizeof(parts)/4;
    for(p=0; p < parts_length; p++){
      int pI = p/2;
      int pJ = p%2;
      for(i=0;i<partN;i++){
	for(j=0;j<partN;j++){
	  parts[p]->set(i,j,get((pI * partN + i),(pJ*partN+j)));
	}
      }
    }
    return parts;
  }
  /*Setter sammen fire delmatriser i en matrise. Den kopierer innholdet fra
    delmatrisene i parts inn i matrisen.*/
  Matrix unPartition(Matrix **parts){
    int partN = n/2;
    int i, j, p;
    long parts_len = sizeof(parts)/4;
    /*Kopierer inn innholdet fra delmatrisene inn på korrekt plass*/
    for(p=0;p<parts_len; p++){
      assert(partN=parts[p]->n);
      int pI=p/2;
      int pJ=p%2;
      for(i=0;i<partN;i++){
	for(j=0;j<partN;j++){
	  set((pI*partN+i),(pJ*partN+j),parts[p]->get(i,j));
	}
      }
    }
    return *this;
  }
  /*Adderer innholdet i a og b, og legger resultatet i c.*/
  Matrix add(Matrix a, Matrix b, Matrix c)
  {
    int i;
    long am_length = sizeof(a.m);
    for(i=0; i < am_length;i++){
      c.m[i]=a.m[i] + b.m[i];
    }
  }
};

int readFile(char *file)
{
  char *inname = file;
  FILE *infile;
  char line_buffer[BUFSIZ];
  char line_number;
  infile = fopen(inname, "r");
  if(!infile){
    fprintf(stderr, "%s: Could not open file %s for reading.\n", progname, file);
    return 2;
  }
  line_number = 0;
  while(fgets(line_buffer, sizeof(line_buffer), infile)){
      line_number++;
      fprintf(stdout, "%s", line_buffer);
  }
  return 0;
}

int main(int argc, char **argv)
{
  if(argc != 3){
    fprintf(stderr, "%s: usage: %s file1 file2\n", progname, progname);
    return 0;
  }
  else{
    readFile(argv[1]);
    readFile(argv[2]);
    return 0;
  }
}
