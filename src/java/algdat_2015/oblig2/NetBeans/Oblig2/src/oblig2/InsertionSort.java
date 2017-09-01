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
public class InsertionSort {
    void insertionSort(int[] t)
    {
        for(int j = 1; j<t.length; j++)
        {
            int bytt = t[j];
            int i = j - 1;
            while(i>=0 && t[j] > bytt){
                t[i+1] = t[i];
                i--;
            }
            t[i+1]=bytt;
        }
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        InsertionSort is = new InsertionSort();
        String name = "insertionSort";
        if(args.length!=1)
        {
            System.err.println("usage: " + name + " arg1");
            System.exit(1);
        }
        ArrayIO aio = new ArrayIO();
        int A[] = aio.readArray(args[0]);
        System.out.print("Før sortering  : ");
        aio.printArray(A);
        int l = A.length;
        double start1 = System.currentTimeMillis();
        //qs.quicksort(A, 0, l-1);
        is.insertionSort(A);
        double stop1 = System.currentTimeMillis();
        System.out.print("Etter sortering: ");
        aio.printArray(A);
        double tot1 = (stop1-start1)/1000;
        System.out.println("Systemet brukte " + tot1 + " sekunder på vanlig quicksort.");
    }
    
}
