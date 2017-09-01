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
  fill(0,255,0);
  rect(0,0, 3, 6);
  fill(255);
  rect(3,0,3,6);
  fill(255,0,0);
  rect(6,0,3,6);
}