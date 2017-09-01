/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package week2;


/**
 *
 * @author andersbo
 */
public class assignment1 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        assignment1 a1 = new assignment1(); //oppretter en ny instanse av "assignment1" slik at metodene nedenfor kan kjøres…
        a1.countDownFor(10,0);
        a1.countDownWhile(20, 0);
        a1.countOdd(2, 8);
        a1.countOdd(3, 9);
        a1.countDownRecursive(30, 1);
        System.out.printf("Running method pow(2,4)\n", a1.pow(2,4));
        a1.reverseArrWithExtraArr(new int[10]);
        a1.reverseArrNoExtraArr(new int[10]);
        a1.reverseArrSwapValues(new Node[10]);
    }
    public void countDownFor(int from, int to)
    {
        for(int i = from; i >= to; i--)
        {
            System.out.println(i);
        }
    }
    public void countDownWhile(int from, int to){
        int i = from;
        while(i >= to){
            System.out.println(i);
            i--;
        }
    }
    public void countOdd(int from, int to)
    {
        //sjekke om from er delelig med 2:
        if(from % 2 == 0) //hvis from mod 2 = 0, dvs. hvis verdien til from kan deles på 2
        {
            from +=1; //øker verdien til from med 1
        }
        int i = from;
        while(i <= to)
        {
            System.out.println(i);
            i +=2;
        }
    }
    public void countDownRecursive(int from, int to){
        int i = from;
        System.out.println(i);
        if(i >= to){
            i--;
            countDownRecursive(i, to); //kaller metoden countDownRecursive rekursivt.
        }
    }
    
    //opgave 2:
    public int pow(int a, int n)
    {
        int base = a;
        int exponent = n;
        int result = base;

        if(exponent > 1){
            while(exponent > 1)
            {
                result = result * base;
                System.out.println(result + " = " + result/2 + " * " + base);
                exponent--;
            }
        }
        else if(exponent < 0)
        {
            while(exponent < 0)
            {
                result = result / base;
                exponent++;
            }
        }
        else if(exponent == 0)
        {
            result = 1;
        }
        return result;
    }
    
    //oppgave 3a
    void reverseArrWithExtraArr(int[] arr)
    {
        //arr = new int[10];
        System.out.println("\nOppgave 3a:");
        java.util.Random r = new java.util.Random();
        int i;
        int j;
        for(i = 0; i < arr.length; i++)
        {
            arr[i] = r.nextInt(100);
            if(i != arr.length -1)
                System.out.print(arr[i] + " - ");
            else
            {
                System.out.print(arr[i]);
                System.out.println();
            }
        }
        int[] f = new int[10];
        //System.out.println("\nReversing array...");
        for(j = 1; j<=arr.length; j++)
        {
            f[j-1] = arr[arr.length-j];
            int noe = f.length -1;
            if(j != f.length)
            {
                //System.out.println("j: " + j  + " arr.length: " + noe);
                System.out.print(f[j-1] + " - " );
            }
            else
            {
                System.out.print(f[j-1]);
                System.out.println();
            }
        }
    }
    void reverseArrNoExtraArr(int[] arr)
    {
        System.out.println("\nOppgave 3b");
        int i;
        java.util.Random r = new java.util.Random();
        for(i = 0; i < arr.length; i++)
        {
            arr[i] = r.nextInt(100);
            if(i != arr.length-1)
                System.out.print(arr[i] + " - ");
            else
            {
                System.out.print(arr[i]);
                System.out.println();
            }
        }
        int f = 0;
        //System.out.println("\nReversing array...");
        for(int j = 1; j<=arr.length; j++)
        {
            f = arr[arr.length-j];
            if(j != arr.length)
                System.out.print(f + " - ");
            else
            {
                System.out.print(f);
                System.out.println();
            }
        }
    }
    
    //oppgave 3c
    void reverseArrSwapValues(Node[] arr)
    {
        try
        {
            System.out.println("\033[01;32m Oppgave 3c");
            int i;
            java.util.Random r = new java.util.Random();
            for(i = 0; i< arr.length; i++)
            {
                Node n = new Node(r.nextInt(100));
                arr[i] = n;
                if(i != arr.length-1)
                    System.out.print(arr[i].value + " - ");
                else
                {
                    System.out.print(arr[i].value);
                    System.out.println();
                }
            }
            int j,f;
            for(j = 0; j < arr.length; j++)
            {
                f = arr[arr.length-1 - j].value;
                if(j != arr.length-1)
                    System.out.print(f + " - ");
                else
                {
                    System.out.print(f);
                    System.out.println();
                }
            }
        }
        catch(java.lang.NullPointerException e)
        {
            System.err.println("Error: " + e.getMessage() + ":" + e.toString());
            System.exit(1);
        }
        /*catch(Exception e)
        {
            System.err.println("Error: " + e.getMessage() + ": " + e.toString());
        }*/
        System.out.println();
    }
    public void reverseArrSwapReferences(Node[] arr)
    {
        /*
	  Do something
	 */
	int p = arr.length;
	Node tmp = new Node(1);
	int i,k;//foretrekker "C-metoden" fremfor a opprette tellere i for-lokker
        for(i = 0;i < p/2; i++)
	{
	    tmp = arr[i];
	    arr[i] = arr[p-1-i];
	    arr[p-1-i] = tmp;
	}
	for(k = 0; k < p; k++)
	{
	    System.out.print(arr[k].value + " ");
	}
	/*try
        {
            int i,j;
            java.util.Random r = new java.util.Random();
            for(i = 0; i<arr.length; i++)
            {
                Node n = new Node(r.nextInt(100));
                arr[i] = n;
		if(i != arr.length-1)
		{
		    System.out.print(arr[i].value + " - ");
		}
		else
		{
		    System.out.print(arr[i].value);
		    System.out.println();
		}
            }
	    //reverserer tabellen
	    for(j = 0; j < arr.length; j++)
	    {
		
	    }
        }
        catch(Exception e)
        {
        }*/
    }
}
