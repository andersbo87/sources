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
public class oppgave3_submatrix {
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
	oppgave3_submatrix ob = new oppgave3_submatrix();
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
             SubMatrix[] dela = a.partition();
             SubMatrix[] delb = b.partition();
             SubMatrix[] delc = c.partition();
             SubMatrix.add(SquareMatrixMultiplyRecursive(dela[0], delb[0]), SquareMatrixMultiplyRecursive(dela[1], delb[2]), delc[0]);
             SubMatrix.add(SquareMatrixMultiplyRecursive(dela[0], delb[1]), SquareMatrixMultiplyRecursive(dela[2], delb[3]), delc[1]);
             SubMatrix.add(SquareMatrixMultiplyRecursive(dela[2], delb[0]), SquareMatrixMultiplyRecursive(dela[3], delb[2]), delc[2]);
             SubMatrix.add(SquareMatrixMultiplyRecursive(dela[2], delb[1]), SquareMatrixMultiplyRecursive(dela[3], delb[3]), delc[3]);
         }
         return c;
    } 
}
