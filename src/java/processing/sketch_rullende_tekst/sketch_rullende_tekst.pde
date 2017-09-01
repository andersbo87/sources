// Et program som skal vise rullende tekst nederst i vinduet.

String[] tekst = {
  "Dette er en rullende tekst",
  "Dette er nok en tekst",
};
PFont f;
float x;
int i = 0;
void setup()
{
  size(400,180);
  f = createFont("Arial", 16, true);
  x = width;
}
void draw()
{
  /*
  Funksjonene background(int) og fill(int) er nødvendig for
  at teksten som produseres, skal bli synlig.
  */
  background(255);
  fill(0);
  textFont(f, 16);
  textAlign(LEFT);
  text(tekst[i],x,180);
  x=x-3;
  float w = textWidth(tekst[i]);
  // Sjekker om X er mindre enn den negative lengden til teksten.
  // I så fall regner jeg teksten som usynlig, og starter på nytt.
  if(x < -w){
    x = width;
    i = (i+1) % tekst.length;
  }
}
