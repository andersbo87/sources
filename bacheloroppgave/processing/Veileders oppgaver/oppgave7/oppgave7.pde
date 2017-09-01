float sfactor = 28.4; // ca antall piksler per cm på et A4-ark

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
  fill(0,0,255);
  rect(0,0,22,16);
  fill(255);
  rect(0,0,7,7);
  fill(150,0,0);
  //fill(#EF2B2D);
  rect(0,0,6,6);
  translate(0,9);
  fill(255);
  rect(0,0,7,7);
  fill(150,0,0);
  rect(0,1,6,6);
  translate(9,-9);
  fill(255);
  rect(0,0,13,7);
  fill(150,0,0);
  rect(1,0,13,6);
  translate(0,9);
  fill(255);
  rect(0,0,13,7);
  fill(150,0,0);
  rect(1,1,12,6);
}