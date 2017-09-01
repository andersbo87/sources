
import java.util.Random;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author andersbo
 */
public class Assignment03Main
{
	static void writeOutArr(int[] arr)
	{
		int i;
		for(i = 0; i < arr.length; i++)
		{
			if(i != arr.length -1)
			{
				System.out.print(arr[i] + " - ");
			}
			else
			{
				System.out.println(arr[i] );
			}
		}
	}
	static void insertionSortWithIllustration(int[] arr)
	{

		int counter,temp;
		for( int i = 1; i < arr.length; i++)
		{
			System.out.println("--Uforandret tabell--");
			//System.out.println(writeOutArrIllustration(arr));
			writeOutArr(arr);
			temp = arr[i];
			System.out.println("\nFørste tempen er " + temp);
			counter = i;
			if (temp < arr[counter-1] == false)
				System.out.println("her kjøres ikke while da " + temp + " ikke er mindre enn " + arr[counter-1]);
			else
				System.out.println(temp + " er mindre enn " + arr[counter-1] + " så da kjøres while ");
			while( counter > 0 && temp < arr[counter-1])
			{
				//int temp2 = arr[counter];
				arr[counter] = arr[counter-1];
				System.out.println("her settes index " + counter + " til å bli " +arr[counter-1]);
				//System.out.println(writeOutArrIllustration(arr));
				writeOutArr(arr);
				counter--;
			}
			arr[counter] = temp;
			System.out.println("til slutt settes index " + counter + " til å være " + temp);
			System.out.println("--Forandret tabell--");
			//System.out.println(writeOutArrIllustration(arr));
			writeOutArr(arr);
			System.out.println("\n------------------------------------");
		}
	}

	/**
	 * @param args
	 */
	public static void insertion_srtWithIllustration(int[] arr, int val)
	{
		double starttime = System.currentTimeMillis();
		int i;
		//int arr2[] = {12, 3, 89, 42, 21, 11, 23};
		for(i = 1; i < arr.length; i++)
		{
			//System.out.print("Sorting " + i);
			int j = i;
			int k = arr[i];
			while((j > 0) && (arr[j-1] > k))
			{
				arr[j] = arr[j-1];
				j--;
			}
			arr[j] = k;
		}
		double endTime = System.currentTimeMillis();
		double time = endTime - starttime;
		double seconds = time/1000;
		System.out.println("\nTime (in seconds): " + seconds);
	}
	/**
	 * @param args
	 */
	public static void insertion_srt(int[] arr)
	{
		int i;
		for(i = 1; i < arr.length; i++)
		{
			int j = i;
			int k = arr[i];
			while((j > 0) && (arr[j-1] > k))
			{
				arr[j] = arr[j-1];
				j--;
				
			}
			arr[j] = k;
		}
	}
	//oppgave 1D
	public static void callInsertionSortWithIllustration()
	{
		int[] arr = {3,5,7,42,88,100,10};
		insertionSortWithIllustration(arr);
	}
	
	//oppgave 1E
	public static void callinsertion_srtWithIllustration()
	{
		java.util.Random r = new java.util.Random();
		int i;
		int arr[] = new int[50000];//{5,7,42,15,89,8};
		for(int counter = 0; counter < arr.length; counter++)
		{
			arr[counter] = r.nextInt(10000);
		}
		for(i = 0; i < arr.length; i++)
		{
			//System.out.print(arr[i]+" ");
		}
		System.out.println("Sorting " + arr.length + " elements.");
		insertion_srtWithIllustration(arr,6);
		//insertionSortWithIllustration(arr);
		for(i = 0; i < arr.length; i++)
		{
			//System.out.print(arr[i]+" ");
		}
		System.out.println();
		System.out.println("PAUSE");
	}
	public static int[] randArr(int n )
    {
        int[] arr = new int[n];
        Random rand = new Random();
        for(int i = 0; i < n; i++){
            arr[i] = rand.nextInt(100*n);
        }
        return arr;
    }
	public static void oppgave1e()
	{
		int[] arr  = {3,2,8,12,6};
		//Sort s = new Sort();
		int samples = 11;
		int incr = 100000;
		long start, stop, duration;
		for(int i = 0; i < samples; i++){
            int n = i*incr;
            arr = randArr(n);
            start = System.nanoTime();
            //s.selectionSort(arr);
            insertion_srt(arr);
            stop = System.nanoTime();
            duration = stop - start;
            System.out.println(""+ n +"\t" + duration);
        } 
	}
	
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		//Assignment03Main a03m = new Assignment03Main();
		System.out.println("\033[22;32m------------\nOppgave 1D\n------------\033[00;00m");
		callInsertionSortWithIllustration();
		System.out.println("\033[22;32m------------\nOppgave 1E\n------------\033[00;00m");
		//callinsertion_srtWithIllustration();
		oppgave1e();
	}

}
