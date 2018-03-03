/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package oblig2;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.io.UnsupportedEncodingException;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author andersbo
 */
public class numberGenerator_reversedSort {
    
    Integer[] reverseSort(String filename) 
    {
        try
        {
            StreamTokenizer st = new StreamTokenizer(new FileReader(filename));
            int n = readN(st);
            return readData(st, n); 
        }
        catch(Exception e)
        {
            System.err.println("System made a noob move: " + e.toString());
            return null;
        }
    }
    private static int readN(StreamTokenizer tokens) throws Exception {
    int token = tokens.nextToken();
    assert(token==StreamTokenizer.TT_NUMBER);
    return (int)tokens.nval;
  }

  private static Integer[] readData(StreamTokenizer tokens, int num) 
      throws Exception {
    int i = 0;
    Integer[] data = new Integer[num];
    while (i<num) {
      int token = tokens.nextToken();
      assert(token==StreamTokenizer.TT_NUMBER);
      data[i++] = (int)tokens.nval;
    }
    Arrays.sort(data, Collections.reverseOrder());
    return data;
  }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
	String name = "numberGenerator_reversedSort";
        try
        {
	    if(args.length != 1){
		System.err.println("usage: " + name + " arg1");
		System.exit(1);
	    }
	    int arg0 = Integer.parseInt(args[0]);
            numberGenerator_reversedSort ng = new numberGenerator_reversedSort();
            ArrayList<Integer> list = new ArrayList<Integer>();
            for (int i=1; i<arg0+1; i++) {
                list.add(new Integer(i));
            }
            PrintWriter writer = new PrintWriter("/Users/andersbo/fil.txt", "UTF-8");
            Collections.shuffle(list);
            System.out.println(list.size());
            writer.print(list.size() + " ");
            for (int i=0; i<arg0; i++) {
                //System.out.println(list.get(i));
                writer.print(list.get(i) + " ");
            }
            writer.close();
            Integer arr[] = ng.reverseSort("/Users/andersbo/fil.txt");
            PrintWriter writer2 = new PrintWriter("/Users/andersbo/reversedsortedfil.txt", "UTF-8");
            writer2.print(arr.length + " ");
            for(int i = 0; i < arr.length; i++ )
            {
                writer2.print(arr[i] + " ");
            }
            writer2.close();
        }
        catch(FileNotFoundException ex)
        {
            System.err.println(ex.toString());
	    Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, ex);
        } 
        catch (UnsupportedEncodingException ex) {
            System.err.println(ex.toString());
            Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
	catch (Exception ex){
	    System.err.println(ex.toString());
            Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, ex);
	}
    }
    
}