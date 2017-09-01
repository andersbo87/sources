import java.util.Random;

/**
 *
 * @author andersbo
 */
public class Oppgave1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        // Oppretter en ny instans av klassen:
        if(args.length != 1)
        {
            System.err.println("usage: program file1");
        }
        Oppgave1 o1 = new Oppgave1();
        ArrayIO aio = new ArrayIO();
        int A[] = aio.readArray(args[0]);
        System.out.print("Før sortering  : ");
        aio.printArray(A);
        int l = A.length;
        double start1 = System.currentTimeMillis();
        o1.quicksort(A, 0, l-1);
        double stop1 = System.currentTimeMillis();
        System.out.print("Etter sortering: ");
        aio.printArray(A);
        System.out.println("Kjører så \"randomized-Quicksort…\"");
        int B[] = aio.readArray(args[0]);
        int l2 = B.length;
        System.out.print("Før sortering  : ");
        aio.printArray(B);
        double start2 = System.currentTimeMillis();
        o1.randomizedQuicksort(B, 0, l2-1);
        double stop2 = System.currentTimeMillis();
        System.out.print("Etter sortering: ");
        aio.printArray(B);
        double tot1 = (stop1-start1)/1000;
        double tot2 = (stop2-start2)/1000;
        System.out.println("Systemet brukte " + tot1 + " sekunder på vanlig quicksort.");
        System.out.println("Systemet brukte " + tot2 + " sekunder på randomized quicksort.");
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
}
