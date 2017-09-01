float sfactor;
float v = 170; // "cm"^3
float h = 2, l = 8, b; // "cm", h = høyde, l = lengde, b = bredde/dybde
int i = 0;
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
  /* 
  Finner først bredden/dybden til esken.
  Formelen for det er som følger:
  bredde = volum / (lengde * høyde)
  */
  if(i < 1)
  {
    println("Volum: " + v + "\nFormel for å finne bredde: bredde = Volum/(lengde * høyde)\nBredde = " + v/(l*h));
    i++;
  }
  b = v/(l*h);
  translate(h,0);
  rect(0,0,l,h);
  translate(-h,h);
  rect(0,0,h,b);
  translate(h,0);
  rect(0,0,l,b);
  translate(l,0);
  rect(0,0,h,b);
  translate(-l,b);
  rect(0,0,l,h);
  translate(0,h);
  rect(0,0,l,b);
}