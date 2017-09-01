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
public class oppgave3_kopier {
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
	oppgave3_kopier ob = new oppgave3_kopier();
        MatrixIO io = new MatrixIO();
        double startTime, runTime;
	startTime1 = System.currentTimeMillis();
        Matrix a = io.readMatrix(args[0]);
        Matrix b = io.readMatrix(args[1]);
        Matrix res = ob.SquareMatrixMultiplyRecursive(a, b);
        System.out.println("Matrise ved kopiering:                      " + res.toString());
	runTime = System.currentTimeMillis() - startTime;
        mem_copy = rt.totalMemory() - rt.freeMemory();
	mem_copy = ob.bytesToMegabytes(mem_copy);
	System.out.println("Tid for matrisekopiering (i sekunder) : " + runTime1/1000);
	System.out.println("Minnebruk ved matrisekopiering: " + mem_copy + " MB");
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
}
