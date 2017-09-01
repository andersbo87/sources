/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
/**
 *
 * @author andersbo
 * Created on a MacBook Pro running FreeBSD 11-CURRENT.
 */
public class oppgave3_indeks {
    private static final long mb = 1024L * 1024L; // mb = megabyte.
    public static long bytesToMegabytes(long b){
	return b/mb;
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        if(args.length != 2)
        {
            System.err.println("usage: program file1 file2");
            return;
        }
	long mem_index;
	Runtime rt = Runtime.getRuntime();
	oppgave3_indeks ob = new oppgave3_indeks();
        MatrixIO io = new MatrixIO();
        double startTime, runTime;
	startTime = System.currentTimeMillis();
        SubMatrix sa = io.readSubMatrix(args[0]);
        SubMatrix sb = io.readSubMatrix(args[1]);
        SubMatrix res_index = ob.SquareMatrixMultiplyRecursive(sa, sb);
        System.out.println("Matrise ved innsetting med indeksvariabler: " + res_index.toString());
	runTime = System.currentTimeMillis() - startTime;
	mem_index=rt.totalMemory() - rt.freeMemory();
	mem_index = ob.bytesToMegabytes(mem_index);
	System.out.println("Tid ved matriseinnsetting (i sekunder): " + runTime/1000);
	System.out.println("Minnebruk ved matriseindekser : " + mem_index + " MB");
    }
    public SubMatrix SquareMatrixMultiplyRecursive(SubMatrix a,SubMatrix b)
    {
         int n = a.n;
         SubMatrix c = new SubMatrix(n);
         if(n==1)
         {
             c.set(0, 0, a.get(0, 0)*b.get(0, 0));
         }
         else if(n>1)
         {
             SubMatrix[] partsa = a.partition();
             SubMatrix[] partsb = b.partition();
             SubMatrix[] partsc = c.partition();
             SubMatrix.add(SquareMatrixMultiplyRecursive(partsa[0], partsb[0]), SquareMatrixMultiplyRecursive(partsa[1], partsb[2]), partsc[0]);
             SubMatrix.add(SquareMatrixMultiplyRecursive(partsa[0], partsb[1]), SquareMatrixMultiplyRecursive(partsa[2], partsb[3]), partsc[1]);
             SubMatrix.add(SquareMatrixMultiplyRecursive(partsa[2], partsb[0]), SquareMatrixMultiplyRecursive(partsa[3], partsb[2]), partsc[2]);
             SubMatrix.add(SquareMatrixMultiplyRecursive(partsa[2], partsb[1]), SquareMatrixMultiplyRecursive(partsa[3], partsb[3]), partsc[3]);
         }
         return c;
    } 
}
