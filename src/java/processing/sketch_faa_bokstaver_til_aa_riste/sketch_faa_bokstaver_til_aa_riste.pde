/*
Et program som skriver teksten "Klikk for å riste bokstavene."
Når brukeren klikker med musa inne i vinduet, begynner alle 
bokstavene å riste i tilfeldige retninger.

Programmet bruker en objektorientert tilnærming for å løse oppgaven.
*/

PFont f;
Bokstav[] bokstaver;
String melding = "Klikk for å riste bokstavene.";

class Bokstav
{
  char bokstav;
  float hjemX, hjemY;
  float x,y;
  // Konstruktør:
  Bokstav(float nyX, float nyY, char nyBokstav)
  {
    hjemX = nyX;
    hjemY = nyY;
    bokstav = nyBokstav;
  }
  void vis()
  {
    fill(0);
    textAlign(LEFT);
    text(bokstav, x, y);
  }
  
  void rist()
  {
    x += random(-2,2);
    y += random(-2,2);
  }
  
  void hjem()
  {
    x = hjemX;
    y = hjemY;
  }
}
void setup()
{
  size(350,200); // størrelsen på vinduet
  f = createFont("Verdana", 13, true);
  textFont(f);
  
  bokstaver = new Bokstav[melding.length()];
  int x = 16;
  int i = 0;
  while(i < melding.length())
  {
    bokstaver[i] = new Bokstav((float)x,(float)100,melding.charAt(i));
    x+= textWidth(melding.charAt(i));
    i++;
  }
}

void draw()
{
  background(255);
  int i = 0;
  while(i<bokstaver.length)
  {
    bokstaver[i].vis();
    if(mousePressed)
      bokstaver[i].rist();
    else
      bokstaver[i].hjem();
    i++;
  }
}


