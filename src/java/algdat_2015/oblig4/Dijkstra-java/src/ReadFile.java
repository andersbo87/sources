
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.StreamTokenizer;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.Scanner;
/**
 *
 * @author anders
 */
public class ReadFile 
{
    String uOrD;
    // Klasse som skal lese fra fil og forhåpentligvis sette inn verdier i nodene…
    public Integer readFileInput(String filename) throws FileNotFoundException, Exception
    {
        Integer numberOfNodes = 0;
        try
        {
            FileReader fr = new FileReader(filename);
            BufferedReader br = new BufferedReader(fr);
            numberOfNodes = Integer.parseInt(br.readLine());
            numberOfNodes--;
            //uOrD = br.readLine(); // tror ikke jeg trenger denne.
            String nodeLine;
            ArrayList<Edge> edgeList = null;
            while((nodeLine = br.readLine()) != null)
            {
                Scanner scanner = new Scanner(nodeLine);
                //Edge edge = new Edge();
            }
        }
        catch(FileNotFoundException fnfe)
        {
            throw fnfe;
        }
        catch(Exception e)
        {
            throw e;
        }
        return numberOfNodes;
    }
}
