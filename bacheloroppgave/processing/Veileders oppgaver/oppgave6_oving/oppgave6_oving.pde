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
  float volum = 200; // "cm" 2
  float diameter = 5; // "cm" -- avstand fra en kant til den andre gjennom sentrum
  float radius = diameter/2; // avstand fra kanten til sentrum
  float omkrets = diameter*PI;
  float lengde = volum/(radius*radius*PI);
  ellipse(10,radius,diameter,diameter);
  rect(10-omkrets/2,diameter,omkrets,lengde);
  ellipse(10,diameter+lengde+radius,diameter,diameter);
}