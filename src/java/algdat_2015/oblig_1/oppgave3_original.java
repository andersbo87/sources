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
public class oppgave3 {
    private static final long mb = 1024L * 1024L; // mb = megabyte.
    public static long bytesToMegabytes(long b){
	return b/mb;
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        if(args.length != 2)
        {
            System.err.println("usage: program file1 file2");
            return;
        }
	long mem_copy, mem_index;
	Runtime rt = Runtime.getRuntime();
	oppgave3 ob = new oppgave3();
        MatrixIO io = new MatrixIO();
        double startTime1, startTime2, runTime1, runTime2;
	startTime1 = System.currentTimeMillis();
        Matrix a = io.readMatrix(args[0]);
        Matrix b = io.readMatrix(args[1]);
        Matrix res_copy = ob.SquareMatrixMultiplyRecursive(a, b);
        System.out.println("Matrise ved kopiering:                      " + res_copy.toString());
	runTime1 = System.currentTimeMillis() - startTime1;
        mem_copy = rt.totalMemory() - rt.freeMemory();
	mem_copy = ob.bytesToMegabytes(mem_copy);
	startTime2 = System.currentTimeMillis();
        SubMatrix sa = io.readSubMatrix(args[0]);
        SubMatrix sb = io.readSubMatrix(args[1]);
        SubMatrix res_index = ob.SquareMatrixMultiplyRecursive(sa, sb);
        System.out.println("Matrise ved innsetting med indeksvariabler: " + res_index.toString());
	runTime2 = System.currentTimeMillis() - startTime2;
	mem_index=rt.totalMemory() - rt.freeMemory();
	mem_index = ob.bytesToMegabytes(mem_index);
	System.out.println("Tid for matrisekopiering (i sekunder) : " + runTime1/1000 + "\nTid for matriseinnsetting (i sekunder): " + runTime2/1000);
	System.out.println("Minnebruk ved matrisekopiering: " + mem_copy + " MB");
	System.out.println("Minnebruk ved matriseindekser : " + mem_index + " MB");
    }
    
    Matrix SquareMatrixMultiplyRecursive(Matrix a, Matrix b)
    {
        int n = a.n;
         Matrix c = new Matrix(n);
         if(n==1)
         {
             c.set(0, 0, a.get(0, 0)*b.get(0, 0));
         }
         else if(n>1)
         {
             Matrix[] partsa = a.partition();
             Matrix[] partsb = b.partition();
             Matrix[] partsc = c.partition();
             Matrix.add(SquareMatrixMultiplyRecursive(partsa[0], partsb[0]), SquareMatrixMultiplyRecursive(partsa[1], partsb[2]), partsc[0]);
             Matrix.add(SquareMatrixMultiplyRecursive(partsa[0], partsb[1]), SquareMatrixMultiplyRecursive(partsa[2], partsb[3]), partsc[1]);
             Matrix.add(SquareMatrixMultiplyRecursive(partsa[2], partsb[0]), SquareMatrixMultiplyRecursive(partsa[3], partsb[2]), partsc[2]);
             Matrix.add(SquareMatrixMultiplyRecursive(partsa[2], partsb[1]), SquareMatrixMultiplyRecursive(partsa[3], partsb[3]), partsc[3]);
             c.unPartition(partsc);
         }
         return c;
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
