float sfactor; // ca antall piksler per cm på et A4-ark

void lagA4()
{
  sfactor = 28.4;
  scale(sfactor,sfactor);
  strokeWeight(1/sfactor);
  background(255);
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

void mittSvar()
{
  triangle(0.9,3.7,2.6,1,3.9,3.7);
  translate(0,5);
  triangle(1,1,1,3,3,3);
  translate(0,5);
  triangle(6,0,1,3,4,1);
}