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
public class oppgave3_matrix {
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
	oppgave3_matrix ob = new oppgave3_matrix();
        MatrixIO io = new MatrixIO();
        double startTime, runTime;
	startTime = System.currentTimeMillis();
        Matrix a = io.readMatrix(args[0]);
        Matrix b = io.readMatrix(args[1]);
        Matrix res = ob.SquareMatrixMultiplyRecursive(a, b);
        System.out.println("Matrise ved kopiering:                      " + res.toString());
	runTime = System.currentTimeMillis() - startTime;
        mem_copy = rt.totalMemory() - rt.freeMemory();
	mem_copy = ob.bytesToMegabytes(mem_copy);
	System.out.println("Tid for matrisekopiering (i sekunder) : " + runTime/1000);
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
             Matrix[] dela = a.partition();
             Matrix[] delb = b.partition();
             Matrix[] delc = c.partition();
             Matrix.add(SquareMatrixMultiplyRecursive(dela[0], delb[0]), SquareMatrixMultiplyRecursive(dela[1], delb[2]), delc[0]);
             Matrix.add(SquareMatrixMultiplyRecursive(dela[0], delb[1]), SquareMatrixMultiplyRecursive(dela[2], delb[3]), delc[1]);
             Matrix.add(SquareMatrixMultiplyRecursive(dela[2], delb[0]), SquareMatrixMultiplyRecursive(dela[3], delb[2]), delc[2]);
             Matrix.add(SquareMatrixMultiplyRecursive(dela[2], delb[1]), SquareMatrixMultiplyRecursive(dela[3], delb[3]), delc[3]);
             c.unPartition(delc);
         }
         return c;
    }
}
