/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oblig2;
import java.util.*;
/**
 *
 * @author andersbo
 */
public class Oppgave2 {

    /**
     * @param args the command line arguments
     */
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
        if(args.length != 1)
        {
            System.err.println("usage: program file1");
            System.exit(1);
        }
        ArrayIO aio = new ArrayIO();
        Oppgave2 o2 = new Oppgave2();
        int A[] = aio.readArray(args[0]);
        int d = A.length;
        o2.radixSort(A, d);
    }
    
}
