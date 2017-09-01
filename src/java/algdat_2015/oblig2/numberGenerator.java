/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package oblig2;
import java.nio.file.*;
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
public class numberGenerator {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
	String name = "numberGenerator";
	try
        {
	    int arg0;
	    if(args.length != 1)
	    {
		System.err.println("usage: " + name + " arg1");
		System.exit(1);
	    }
	    arg0 = Integer.parseInt(args[0]);
	    if(Files.exists(path))
		/*PrintWriter*/ writer = new PrintWriter("/Users/andersbo/fil.txt", "UTF-8");
	    else if(Files.exists(otherPath))
		/*PrintWriter*/ writer = new PrintWriter("/home/andersbo/fil.txt", "UTF-8");
	    else
		return;
            numberGenerator ng = new numberGenerator();
            ArrayList<Integer> list = new ArrayList<Integer>();
            for (int i=1; i<arg0 + 1; i++) {
                list.add(new Integer(i));
            }
	    PrintWriter writer;
	    Path path = Paths.get("/Users/andersbo/fil.txt");
	    Path otherPath = Paths.get("/home/andersbo/fil.txt");
	    
            Collections.shuffle(list);
            System.out.println(list.size());
            writer.print(list.size() + " ");
            for (int i=0; i<arg0; i++) {
                //System.out.println(list.get(i));
                writer.print(list.get(i) + " ");
            }
            writer.close();
        }
        catch(FileNotFoundException e)
        {
            System.err.println(name + ": " +e.toString());
	    Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, e);
        } 
        catch (UnsupportedEncodingException ex) {
            System.err.println(name + ": " +ex.toString());
            Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
	catch(Exception ex){
	    System.err.println(name + ": " +ex.toString());
            Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, ex);
	}
    }
    
}
