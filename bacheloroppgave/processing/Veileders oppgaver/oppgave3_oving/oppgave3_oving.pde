float sfactor;
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
}

void draw()
{
  lagA4();
  mittSvar();
}

void mittSvar()
{
  // Flytter origo 5 "cm" bortover X-aksen
  translate(5,0);
  rect(0,0,5,5);
  // Flytter origo 5 "cm" bakover på X-aksen og 5 "cm" nedover Y-aksen
  translate(-5,5);
  rect(0,0,5,5);
  translate(5,0);
  rect(0,0,5,5);
  translate(5,0);
  rect(0,0,5,5);
  translate(-5,5);
  rect(0,0,5,5);
  translate(0,5);
  rect(0,0,5,5);
}