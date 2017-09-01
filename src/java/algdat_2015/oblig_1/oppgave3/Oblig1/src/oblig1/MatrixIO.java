package oblig1;

import java.io.*;

class MatrixIO {

  /*
  * Les inn en matrise fra fil
  */
  public static Matrix readMatrix(String filename) {
    try {
      StreamTokenizer tokens = new StreamTokenizer(new FileReader(filename));
      int n = readN(tokens);
      return new Matrix(n, readData(tokens, n*n)); 
    }
    catch (Exception e) {
      return null;
    }
  }

  /*
  * Les inn en delmatrise fra fil
  */
  public static SubMatrix readSubMatrix(String filename) {
    try {
      StreamTokenizer tokens = new StreamTokenizer(new FileReader(filename));
      int n = readN(tokens);
      return new SubMatrix(n, readData(tokens, n*n)); 
    }
    catch (Exception e) {
      return null;
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
