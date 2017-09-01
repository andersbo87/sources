// Et program som flytter en ut ifra musepekerens posisjon
// med hjelp av noen tabeller (tror jeg da)

int num = 50;
int[] x = new int[num];
int[] y = new int[num];
int indeksposisjon = 0;

void setup()
{
  size(100,100);
  noStroke();
  fill(255,102);
}

void draw()
{
  background(0);
  x[indeksposisjon] = mouseX;
  y[indeksposisjon] = mouseY;
  
  indeksposisjon = (indeksposisjon + 1) % num; // % = modulo, resten etter en heltallsdivisjon.
  for(int i = 0; i < num; i++)
  {
    int pos = (indeksposisjon + 1) % num;
    float radius = (num-i) / 2;
    ellipse(x[pos], y[pos], radius, radius);
  }
}
