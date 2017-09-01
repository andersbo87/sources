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
  // Ettersom at vi ikke bruker trigonometri i ungdomskolen, må vi forholde oss til rettvinklede trekanter.
  // Vi må da lage 2 trekanter som hver er 2.5 cm i grunnlinja og 6 cm i høyden.
  translate(3,0);
  triangle(6,1,8.5,7,6,7);
  triangle(6,1,6,7,3.5,7);
  translate(-2.5,7);
  triangle(0,2.5,6,2.5,6,0);
  triangle(0,2.5,6,2.5,6,5);
  translate(6,0);
  rect(0,0,kant,kant);
  translate(0,5);
  triangle(0,0,2.5,0,2.5,6);
  triangle(2.5,0,2.5,6,5,0);
  translate(5,-5);
  triangle(0,0,0,2.5,6,2.5);
  triangle(0,2.5,0,5,6,2.5);
  //rect(0,7,5,5);
}