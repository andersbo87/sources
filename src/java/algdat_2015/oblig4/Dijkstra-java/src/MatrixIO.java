/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
import java.io.*;

class MatrixIO {

  /*
  * Les inn en matrise fra fil
  */
  public static Matrix readMatrix(String filename) throws FileNotFoundException, Exception{
    try {
      StreamTokenizer tokens = new StreamTokenizer(new java.io.FileReader(filename));
      int n = readN(tokens);
      return new Matrix(n, readData(tokens, n*n)); 
    }
    catch (FileNotFoundException ex)
    {
        throw new FileNotFoundException("Filen " + filename + " ble ikke funnet.\n");
    }
    catch (Exception e) {
        throw e;
      //return null;
    }
  }

  /*
  * Les inn en delmatrise fra fil
  */
  public static SubMatrix readSubMatrix(String filename) throws FileNotFoundException, Exception{
    try {
      StreamTokenizer tokens = new StreamTokenizer(new java.io.FileReader(filename));
      int n = readN(tokens);
      return new SubMatrix(n, readData(tokens, n*n)); 
    }
    
    catch (FileNotFoundException ex)
    {
        throw new FileNotFoundException("Filen " + filename + " ble ikke funnet.\n");
    }
    catch (Exception e) {
        throw e;
    }
  }

  private static int readN(StreamTokenizer tokens) throws Exception {
    int token = tokens.nextToken();
    assert(token==StreamTokenizer.TT_NUMBER);
    return (int)tokens.nval;
  }

  private static float[] readData(StreamTokenizer tokens, int num) 
      throws Exception {
    int i = 0;
    float[] data = new float[num];
    while (i<num) {
      int token = tokens.nextToken();
      assert(token==StreamTokenizer.TT_NUMBER);
      data[i++] = (float)tokens.nval;
    }
    return data;
  }

}

