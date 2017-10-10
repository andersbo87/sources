// radixSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// radixSort.cpp
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#ifndef WIN32
#include <unistd.h>
#include <sys/time.h>
#else
#include <process.h>
#endif
#include <system_error>

using namespace std;
// Globale variabler for hele programmet:
const char *prog_name;
ifstream in;

class ArrayIO
{
private:
	string *myString;
public:
	ArrayIO() {
		myString = 0x0;
	}

	string *readArray(const char *filename) {
		in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			in.open(filename);
			string str2 = " ";
			stringstream buffer;
			buffer << in.rdbuf();
			string test = buffer.str();
			int last = test.size() - 1;
			// La oss sjekke om innholdet i filen ender med et mellomrom.
			// Om det ikke gj�r det, legges det til et mellomrom p� slutten av strengen.
			// Det er fordi funksjonen genererer en null-pointer dersom tekststrengen ikke ender med et mellomrom,
			if (last >= 0 && test[last] != ' ') {
				string spc = " ";
				test.append(spc);
			}
			size_t pos1 = 0, pos2, str_pos1 = 0;
			int count = 0;
			while ((str_pos1 = test.find(str2, str_pos1)) < test.length()) {
				str_pos1 += str2.length();
				count++;
			}
			static string *str;
			str = new string[count];
			if (count == 0) {
				fprintf(stderr, "%s: Lengden p� tabellen er for liten. Lengden m� v�re >= 1\n", prog_name);
				exit(1);
			}
			for (int x = 0; x < count; x++) {
				pos2 = test.find(" ", pos1);
				str[x] = test.substr(pos1, (pos2 - pos1));
				pos1 = pos2 + 1;
			}
			myString = str;
			return myString;
		}
		catch (std::system_error& e) {
			string error = prog_name;
			error.append(": Noe gikk galt: ");
			error.append(filename);
			perror(error.c_str());
			exit(1);
		}
	}
	/*
	F�lgende funksjon skriver ut en array:
	*/
	void print(int arr[], int n)
	{
		for (int i = 0; i < n; i++) {
			fprintf(stdout, "%d ", arr[i]);
		}
		fprintf(stdout, "\n");
	}
};

class radixSort
{
private:
	int BITS_PER_BYTE;
public:
	void setBitsPerByte(int newBits)
	{
		BITS_PER_BYTE = newBits;
	}
	int getBitsPerByte()
	{
		return BITS_PER_BYTE;
	}

	// Legger til et ekstra parameter, int s som er st�rrelsen p� arrayet (I C++ kan man ikke bruke array.length, som man kan i Java).
	void sort(int a[], int s) {
		try {
			// Datatypen "int" er et 32-biters heltall.
			// Hver byte kan ha verdier mellom 0 og 255.
			int BITS = 32;
			int W = BITS / getBitsPerByte();
			int R = 1 << getBitsPerByte();
			int MASK = R - 1;

			int N = s;//a[0];
			printf("Lengde: %d\n", N);
			int *aux = new int[N];

			for (int d = 0; d < W; d++) {

				// compute frequency counts
				int *count = new int[R + 1];
				for (int i = 0; i < N; i++) {
					int c = (a[i] >> getBitsPerByte()*d) & MASK;
					count[c + 1]++;
				}

				// compute cumulates
				for (int r = 0; r < R; r++)
					count[r + 1] += count[r];

				// I den viktigste byte kommer 0x80-0xFF f�r 0x00-0x7F
				if (d == W - 1) {
					int shift1 = count[R] - count[R / 2];
					int shift2 = count[R / 2];
					for (int r = 0; r < R / 2; r++)
						count[r] += shift1;
					for (int r = R / 2; r < R; r++)
						count[r] -= shift2;
				}

				// F�lgende flytter data
				for (int i = 0; i < N; i++) {
					int c = (a[i] >> getBitsPerByte()*d) & MASK;
					aux[count[c]++] = a[i];
				}

				// Kopier tilbake
				for (int i = 0; i < N; i++)
					a[i] = aux[i];
			}
		}
		catch (std::system_error& e)
		{
			string error = prog_name;
			error.append(": Noe gikk galt: ");
			perror(error.c_str());
			exit(1);
		}
		catch (std::exception& e)
		{
			string error = prog_name;
			error.append(": Noe gikk galt: ");
			perror(error.c_str());
			exit(1);
		}
	}
};


void segFault(int sig_num)
{
	signal(SIGSEGV, segFault);
	signal(sig_num, SIG_DFL);
#ifndef WIN32
	fprintf(stderr, "%s must quit because of a segmentation violation. If core dumps are enabled, a core dump will be created.\n", prog_name);
	syslog(LOG_ERR, "%s must quit because of a segmentation violation.\n", prog_name);
	exitApp(sig_num);
	kill(getpid(), sig_num);
#else
	fprintf(stderr, "A segmentation violation has occurred and %s must quit.\n", prog_name);
	exit(sig_num);
#endif // !WIN32
}



int main(int argc, char **argv)
{
	// Definerer noen variabler som skal brukes i forbindelse med tidtagning:
	signal(SIGSEGV, segFault);
#ifndef WIN32
	struct timeval start, end;
	long mtime;
#endif
	prog_name = "radixsort";
	if (argc != 3)
	{
		fprintf(stderr,
			"%s: bruk: %s arg1 arg2\n"
			"arg1 er en eksisterende fil p� datamaskinen.\n"
			"arg2 er et heltall som tilsvarer antall bits per siffer.\n", prog_name, prog_name);
		return 1;
	}
	radixSort *rs = new radixSort();
	ArrayIO *aio = new ArrayIO();
	printf("argv[0]: %s\nargv[1]: %s\nargv[2]: %s\n", argv[0], argv[1], argv[2]);
	string *a = aio->readArray(argv[1]);
	// The atoi() function converts the initial portion of the string pointed to by nptr to int representation.:
	int l = atoi(a[0].c_str()); // Det f�rste elementet er st�rrelsen p� arrayet.
	int r = atoi(argv[2]);
	rs->setBitsPerByte(r);
	int allItems = l;
#ifndef WIN32
	int arr[allItems];
#else
	int *arr = new int[allItems];
#endif
	int i = 0;
	fprintf(stdout, "Klargj�r...\n");
	while (i<l) {
		arr[i] = atoi(a[i + 1].c_str());
		i++;
	}
	i = 0;
	fprintf(stdout, "F�r sortering:\n");
	for (i = 0; i < l; i++) {
		fprintf(stdout, "%d ", arr[i]);
	}
	fprintf(stdout, "\n");
#ifndef WIN32
	gettimeofday(&start, NULL);
#endif
	rs->sort(arr, l);
#ifndef WIN32
	gettimeofday(&end, NULL);
#endif	
	fprintf(stdout, "Etter sortering:\n");
	for (i = 0; i < l; i++) {
		fprintf(stdout, "%d ", arr[i]);
	}
	fprintf(stdout, "\n");
#ifndef WIN32
	mtime = end.tv_sec - start.tv_sec;
	if (mtime == 0) {
		long mtime_usec = end.tv_usec - start.tv_usec;
		fprintf(stdout, "Systemet brukte %ld mikrosekunder p� radixSort med %d bits.\n", mtime_usec, rs->getBitsPerByte());
	}
	else
	{
		fprintf(stdout, "Systemet brukte %ld sekunder p� radixSort med %d bits.\n", mtime, rs->getBitsPerByte());
	}
#endif
	return 0;
}

