void oppgave4A()
{
  // Skriv kode her
  ellipse(0,0,4,4);
}

void oppgave4B()
{
  // Skriv kode her
  float r = 2; // r = radius
  float d = r * 2; // d = diameter
  float v = 100; // volum
  float o = d*PI; // o = omkrets
  float l = v/(r*r*PI); // l = lengde i cm
  ellipse(5,d/2,d,d);
  rect(5-o/2,d,o,l);
  ellipse(5,d+l+d/2,d,d);
}