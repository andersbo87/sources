/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oblig2;

/**
 *
 * @author andersbo
 */
public class quicksort 
{
    public static void main(String[] args)
    {
        if(args.length != 1)
        {
            System.err.println("usage: quicksort file");
            System.exit(1);
        }
        quicksort qs = new quicksort();
        ArrayIO aio = new ArrayIO();
        int A[] = aio.readArray(args[0]);
        System.out.print("Før sortering  : ");
        aio.printArray(A);
        int l = A.length;
        double start1 = System.currentTimeMillis();
        qs.quicksort(A, 0, l-1);
        double stop1 = System.currentTimeMillis();
        System.out.print("Etter sortering: ");
        aio.printArray(A);
        double tot1 = (stop1-start1)/1000;
        System.out.println("Systemet brukte " + tot1 + " sekunder på vanlig quicksort.");
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
