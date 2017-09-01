/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package oblig2;
import java.util.*;
/**
 *
 * @author andersbo
 */
public class Oppgave2 {
    void radixSort(int A[], int d)
    {
        //int i;
        List<Integer>[] liste = new ArrayList[d];
        for(int i=0; i<d; i++)
        {
            // do something.
            liste[i] = new ArrayList<Integer>();
        }
        // Sortering:
        boolean makslengde = false;
        int temp = -1, plassering = 1;
        while(!makslengde)
        {
            makslengde = true;
            for (Integer i: A)
            {
                temp = i/plassering;
                liste[temp % d].add(i);
                if(makslengde && temp > 0){
                    makslengde = false;
                }
            }
            int a = 0;
            for(int b = 0; b < d; b++)
            {
                for(Integer i : liste[b])
                {
                    A[a++] = i;
                }
                liste[b].clear();
            }
            plassering *= d;
        }
    }
    public static void main(String[] args) {
        // TODO code application logic here
	String name = "Oppgave2";
	try{
	    if(args.length != 2){
		System.err.println("usage: " + name + " file1 arg1");
		System.err.println("file1 the file containing the array to be sorted\narg1: an integer to calculate number of bits per digit.");
		System.exit(1);
	    }
	    ArrayIO aio = new ArrayIO();
	    Oppgave2 o2 = new Oppgave2();
	    int A[] = aio.readArray(args[0]);
	    int r = Integer.parseInt(args[1]);
	    aio.printArray(A);
	    // Starter måling av tidsforbruket til radixSort...
	    long start = System.nanoTime();
	    o2.radixSort(A, 7);
	    // Stopper måling av tidsforbruket til radixSort...
	    long stop = System.nanoTime();
	    System.out.println("Sortert utgave: ");
	    aio.printArray(A);
	    double nanototal = stop - start;
	    double micrototal = nanototal / 1000;
	    double millitotal = micrototal / 1000;
	    double sectotal = millitotal / 1000;
	    System.out.println("Systemet brukte:\n" + nanototal + " nanosekunder\n" + micrototal + " mikrosekunder\n" + millitotal + " millisekunder\n" + sectotal + " sekunder på radixsort.");
	}
	catch(Exception e){
	    System.err.println(name + ": Error:  " + e.getMessage());
	}
    }
}
