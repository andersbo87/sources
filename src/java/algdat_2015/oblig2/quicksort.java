/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package oblig2;
import java.text.*;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author andersbo
 */
public class quicksort 
{
    String name = "quicksort";
    public static void main(String[] args)
    {
	quicksort qs = new quicksort();
	try{
	    if(args.length != 1){
		System.err.println("usage: " + qs.name + " file");
		System.exit(1);
	    }
	    ArrayIO aio = new ArrayIO();
	    int A[] = aio.readArray(args[0]);
	    System.out.print("Før sortering  : ");
	    aio.printArray(A);
	    int l = A.length;
	    long start = System.nanoTime();
	    qs.quicksort(A, 0, l-1);
	    long stop = System.nanoTime();
	    System.out.print("Etter sortering: ");
	    aio.printArray(A);
	    long nanototal = stop - start;
	    double micrototal = nanototal/1000;
	    double millitotal = micrototal/1000;
	    double sectotal = millitotal/1000;
	    System.out.println("Systemet brukte:\n" + nanototal + " nanosekunder\n" + micrototal + " mikrosekunder\n" + millitotal + " millisekunder\n" + sectotal + " sekunder på insertionsort.");
	}
	catch(StackOverflowError ex){
	    System.err.println(qs.name + ": Det ser ut til at det har oppstått en stack overflow. Prøv å øke callstacken ved å skrive -XssXm (f.eks. -Xss100m) som et java-argument. ");
	}
	catch(Exception ex)
	{
	    System.err.println(qs.name + ": " + ex.toString());
            Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, ex);
	}
    } 
    void quicksort(int A[], int p, int r)
    {
        if(p < r)
        {
            int q = partition(A, p, r);
            quicksort(A, p, q - 1);
            quicksort(A, q + 1, r);
        }    
    }
    
    int partition(int A[], int p, int r)
    {
        int x = A[r];
        int i = p-1;
        int j, tmp1, tmp2;
        for(j = p; j <= r-1; j++)
        {
            if(A[j] <= x)
            {
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
        return i + 1;
    }
}
