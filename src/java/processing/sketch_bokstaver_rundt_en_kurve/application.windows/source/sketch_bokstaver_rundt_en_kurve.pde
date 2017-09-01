/*
Et program som viser tekst rundt en kurve.
Oppgaven løses med mye bruk av trigonometri.
*/

PFont f;
// Radiusen til en sirkel
float r = 100;
String melding = "Tekst langs/rundt en kurve";

void setup()
{
  size(340,280);
  f = createFont("Arial", 24, true);
  textFont(f);
  textAlign(CENTER);
  smooth();
}

void draw()
{
  background(255,0,0);
  translate(width/2, height/2);
  noFill();
  stroke(0,255,0);
  ellipse(0,0,r*2,r*2);
  
  // Det er nødvendig å lagre posisjonen i kurven:
  float arclength = 0;
  int i = 0;
  while(i<melding.length())
  {
    char gjeldendeBokstav = melding.charAt(i);
    float w = textWidth(gjeldendeBokstav); 
    arclength += w/2; // legger til halve lengden til bokstavens bredde.
    /*
    Vinkelen i radianer er arclength dividert på radius.
    Man starter på venstre side av sirkelen ved å legge til PI.
    */
    float theta = PI + arclength / r;
    pushMatrix();
    
    translate(r*cos(theta), r*sin(theta));
    
    rotate(theta+PI/2);
    // vis karakteren eller bokstaven.
    fill(0);
    text(gjeldendeBokstav,0,0);
    popMatrix();
    arclength += w/2;
    i++;
  }
}
