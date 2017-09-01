/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oblig2;

import java.text.DecimalFormat;
import java.util.Random;

/**
 *
 * @author andersbo
 */
public class randomizeQuicksort {
    quicksort qs;
    void randomizeQuicksort()
    {
        qs = new quicksort();
    }
    public static void main(String[] args)
    {
        if(args.length != 1)
        {
            System.err.println("usage: quicksort file");
            System.exit(1);
        }
        ArrayIO aio = new ArrayIO();
        System.out.println("Kjører \"randomized-Quicksort…\"");
        randomizeQuicksort rqs = new randomizeQuicksort();
        int B[] = aio.readArray(args[0]);
        int l2 = B.length;
        System.out.print("Før sortering  : ");
        aio.printArray(B);
        double start = System.currentTimeMillis();
        rqs.randomizedQuicksort(B, 0, l2-1);
        double stop = System.currentTimeMillis();
        System.out.print("Etter sortering: ");
        aio.printArray(B);
        double tot = (stop-start)/1000;
        DecimalFormat df = new DecimalFormat("#.##");
        df.format(tot);
        System.out.println("Systemet brukte " + df.format(tot) + " sekunder på randomized quicksort.");
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
