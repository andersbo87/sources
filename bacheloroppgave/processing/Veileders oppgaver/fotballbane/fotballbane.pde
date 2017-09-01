float sfactor; // ca antall piksler per cm på et A4-ark
int i = 0,j = 0; // ikke nødvendig for å løse problemet i programmet, men kjekk å ha når jeg bare vil skrive ut en ting en gang.

void lagA4()
{
  sfactor = 28.4;
  scale(sfactor,sfactor);
  strokeWeight(1/sfactor);
  background(#00FF00);
}

void setup()
{
  frameRate(30); // strengt talt ikke nødvendig med 30 fps, (siden dette ikke er en animasjon), men hvorfor ikke...
  size(596, 843);
  //println("Overflate:\t\t\t" + overflate + "\nAreal av sidekanter:\t\t" + overflate/6 + "\nLengde på sidekanter:\t" + sqrt(overflate/6));
}

void draw()
{
  lagA4();
  mittSvar();
}