public class radixSort {
    int BITS_PER_BYTE;
    // LSD sort an array of integers, treating each int as 4 bytes
    // assumes integers are nonnegative
    // [ 2-3x faster than Arrays.sort() ]
    public void sort(int[] a) {
        int BITS = 32;                 // each int is 32 bits 
        int W = BITS / BITS_PER_BYTE;  
        int R = 1 << BITS_PER_BYTE;    // each bytes is between 0 and 255
        int MASK = R - 1;              // 0xFF

        int N = a.length;
	System.out.println("Lengde: " + N);
        int[] aux = new int[N];

        for (int d = 0; d < W; d++) {         

            // compute frequency counts
            int[] count = new int[R+1];
            for (int i = 0; i < N; i++) {           
                int c = (a[i] >> BITS_PER_BYTE*d) & MASK;
                count[c + 1]++;
            }

            // compute cumulates
            for (int r = 0; r < R; r++)
                count[r+1] += count[r];

            // for most significant byte, 0x80-0xFF comes before 0x00-0x7F
            if (d == W-1) {
                int shift1 = count[R] - count[R/2];
                int shift2 = count[R/2];
                for (int r = 0; r < R/2; r++)
                    count[r] += shift1;
                for (int r = R/2; r < R; r++)
                    count[r] -= shift2;
            }

            // move data
            for (int i = 0; i < N; i++) {
                int c = (a[i] >> BITS_PER_BYTE*d) & MASK;
                aux[count[c]++] = a[i];
            }

            // copy back
            for (int i = 0; i < N; i++)
                a[i] = aux[i];
        }
    }

    public static void main(String[] args) {
	String name = "radixSort";
	radixSort rs = new radixSort();
	try{
	    if(args.length != 2){
		System.err.println(name + ": usage: " + name + "file1 arg1\nfile1: a file containing the indexes to be sorted\narg1: an integer containing bits per digits (e.g. 8)");
		System.exit(1);
	    }
	    ArrayIO aio = new ArrayIO();
	    int a[] = aio.readArray(args[0]);
	    rs.BITS_PER_BYTE = Integer.parseInt(args[1]);
	    int N = a.length;
	    int W = a[0];
	    System.out.println("Før sortering: ");
	    aio.printArray(a); 
	    long start = System.nanoTime(); // Starter måling av tidsforbruket av radixsort.
	    rs.sort(a);
	    long stop = System.nanoTime();
	    System.out.println("Etter sortering: "); // Stopp måling av tidsforbruket av radixsort.
	    aio.printArray(a);
	    double nanototal = stop - start;
	    double micrototal = nanototal / 1000;
	    double millitotal = micrototal / 1000;
	    double sectotal = millitotal / 1000;
	    System.out.println("Systemet brukte:\n" + nanototal + " nanosekunder\n" + micrototal + " mikrosekunder\n" + millitotal + " millisekunder\n" + sectotal + " sekunder på radixsort med " + rs.BITS_PER_BYTE + " bits.");
	}
	catch(Exception e){
	    System.err.println(name + ": error: " + e.toString());
	}
    }
}
