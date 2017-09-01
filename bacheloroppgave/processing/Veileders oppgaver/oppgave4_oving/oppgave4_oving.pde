float sfactor;
float overflate = 220; // "cm^2"
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
  println("Overflate:\t\t\t" + overflate + "\nAreal av sidekanter:\t\t" + overflate/6 + "\nLengde på sidekanter:\t" + sqrt(overflate/6));
}

void draw()
{
  lagA4();
  mittSvar();
}

void mittSvar()
{
  float sidekant = sqrt(overflate/6);
  translate(sidekant,0);
  rect(0,0,sidekant,sidekant);
  translate(-sidekant,sidekant);
  rect(0,0,sidekant, sidekant);
  translate(sidekant,0);
  rect(0,0,sidekant,sidekant);
  translate(sidekant,0);
  rect(0,0,sidekant,sidekant);
  translate(-sidekant,sidekant);
  rect(0,0,sidekant, sidekant);
  translate(0,sidekant);
  rect(0,0,sidekant,sidekant);
}