/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package oblig2;

/**
 *
 * @author andersbo
 */
public class InsertionSort {
    void insertionSort(int[] t)
    {
        for(int i = 1; i<t.length; i++)
        {
            int bytt = t[i];
            int j = i - 1;
            //while(i>=0 && t[j] > bytt){
	    while(j >= 0 && bytt < t[j]){
                t[j+1] = t[j];
                j--;
            }
            t[j+1]=bytt;
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
        //double start1 = System.currentTimeMillis();
        long start = System.nanoTime();
        is.insertionSort(A);
	long stop = System.nanoTime();
	double nanototal = stop - start;
	double micrototal = nanototal/1000;
	double millitotal = micrototal/1000;
	double sectotal = millitotal/1000;
        System.out.print("Etter sortering: ");
        aio.printArray(A);
	System.out.println("Systemet brukte:\n" + nanototal + " nanosekunder\n" + micrototal + " mikrosekunder\n" + millitotal + " millisekunder\n" + sectotal + " sekunder på insertionsort.");
    }
    
}
