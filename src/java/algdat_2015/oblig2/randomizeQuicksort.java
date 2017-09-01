/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package oblig2;

import java.util.Random;
import java.text.*;
/**
 *
 * @author andersbo
 */
public class randomizeQuicksort {
    public static void main(String[] args)
    {
	randomizeQuicksort rqs = new randomizeQuicksort();
	String name = "randomizeQuicksort";
	try{
	    if(args.length != 1){
		System.err.println("usage: " + name + " file");
		System.exit(1);
	    }
	    ArrayIO aio = new ArrayIO();
	    int B[] = aio.readArray(args[0]);
	    int l2 = B.length;
	    System.out.print("Før sortering  : ");
	    aio.printArray(B);
	    long start = System.nanoTime();
	    rqs.randomizedQuicksort(B, 0, l2-1);
	    long stop = System.nanoTime();
	    System.out.print("Etter sortering: ");
	    aio.printArray(B);
	    long nanototal = stop - start;
	    double micrototal = nanototal/1000;
	    double millitotal = micrototal/1000;
	    double sectotal = millitotal/1000;
	    System.out.println("Systemet brukte:\n" + nanototal + " nanosekunder\n" + micrototal + " mikrosekunder\n" + millitotal + " millisekunder\n" + sectotal + " sekunder på randomizeQuicksort.");
	}
	catch(StackOverflowError e){
	    System.err.println(name + ": Det ser ut til at det har oppstått en stack overflow. Prøv å øke callstacken ved å skrive -XssXm (f.eks. -Xss100m) som et java-argument. ");
	}
	catch(Exception e){
	    System.err.println(name + e.toString());
	}
    }
    void randomizedQuicksort(int A[], int p, int r)
    {
        if(p<r)
        {
            int q = randomizedPartition(A, p, r);
            randomizedQuicksort(A, p, q - 1);
            randomizedQuicksort(A, q + 1, r);
        }
    }
    int randomizedPartition(int A[], int p, int r)
    {
        Random rand = new Random();
        int i = rand.nextInt(r-p)+p;
        int t = A[i];
        int j = A[r];
        A[r] = t;
        A[i] = j;
        return partition(A, p, r);
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
