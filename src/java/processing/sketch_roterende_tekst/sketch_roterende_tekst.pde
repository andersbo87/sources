/*
Et program som viser roterende tekst.
*/
PFont f;
String tekst = "Dette er en spinnende tekst.";
float theta; // Theta er en bokstav i det greske alfabetet.
void setup()
{
  size(200,200);
  f = createFont("Arial",16, true);
}

void draw()
{
  background(255);
  fill(0);
  textFont(f);
  translate(width/2, height/2);
  rotate(theta);
  textAlign(CENTER);
  text(tekst, 0,0);
  theta = theta +0.5; // Alternativt: theta += 0.5
}
