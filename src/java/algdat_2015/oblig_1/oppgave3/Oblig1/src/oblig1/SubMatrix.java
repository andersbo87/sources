import java.util.Arrays;

/*
* Denne klassen brukes til å representere enten en matrise eller en 
* delmatrise.
*
* En nxn matrise a: 
*   i=0, j=0, n=n, mn=n, m=new float[n*n] 
* En topright delmatrise av matrisen a: 
*   i=0, j=(a.n/2), n=(a.n/2), mn=a.mn, m=a.m
*/
class SubMatrix {

  public int i, j, n, mn; // Startrad, 
                          // Startkolonne, 
                          // DelmatriseStørrelse
                          // MatriseStørrelse
  public float[] m;       // Matrisen lagret som en array


  /* 
  * Lager en ny nxn matrise
  */
  public SubMatrix(int n) {
    this.i = 0;
    this.j = 0;
    this.n = n;
    this.mn = n;
    this.m = new float[n*n];
  }
  /*
  * Lager en ny nxn matrise med spesifersert data
  */
  public SubMatrix(int n, float[] m) {
    assert(n*n==m.length);
    this.i = 0;
    this.j = 0;
    this.m = m;
    this.mn = n;
    this.n = n;
  }

  /*
  * Lager en nxn delmatrise som begynner på rad i og kolonne j
  */
  public SubMatrix(int i, int j, int n, SubMatrix m) {
    this.i = i;
    this.j = j;
    this.n = n;  
    this.m = m.m;
    this.mn = m.mn;
  }

  /*
  * Returnerer elementet på rad i og kolonne j
  */
  public float get(int i, int j) {
    assert( i>=0 && i<n && j>=0 && j<n );
    return m[(this.i+i)*mn+this.j+j];
  }

  /*
  * Setter elementet på rad i og kolonne j til x
  */
  public void set(int i, int j, float x) {
    assert( i>=0 && i<n && j>=0 && j<n );
    m[(this.i+i)*mn+this.j+j] = x;
  }

  /*
  * Tar en (del)matrise og deler den opp i fire deler. Delene blir returnert i
  * et array i følgende rekkefølge: topleft, topright, bottomleft, bottomright.
  */
  public SubMatrix[] partition() {
   
    int partN = n / 2;
    SubMatrix[] parts = {
      new SubMatrix(i, j, partN, this),
      new SubMatrix(i, partN + j, partN, this),
      new SubMatrix(partN + i, j, partN, this),
      new SubMatrix(partN + i, partN + j, partN, this)
    };

    return parts;

  }

  /*
  * Adderer innholdet i delmatrisene a og b og legger resultatet på riktig plass
  * i delmatrisen c
  */
  public static SubMatrix add(SubMatrix a, SubMatrix b, SubMatrix c) {

    for (int i = 0; i < a.n; i++)
      for (int j = 0; j < a.n; j++)
        c.m[(c.i + i) * c.mn + c.j + j] =
          a.m[(a.i + i) * a.mn + a.j + j] + b.m[(b.i + i) * b.mn + b.j + j];

    return c;

  }

  public String toString() {
    return Arrays.toString(m);
  }

}
