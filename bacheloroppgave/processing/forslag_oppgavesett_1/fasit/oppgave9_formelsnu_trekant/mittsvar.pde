void oppgave9()
{
  float grunnflate = 12;
  float hoyde = 2;
  trekant(grunnflate,hoyde);
  svarAreal = regnAreal(grunnflate,hoyde);
}

float regnAreal(float grunnlinje, float trekantHoyde)
{
  // Skriv kode her.
  float areal = (grunnlinje*trekantHoyde)/2;
  //println("Arealet av trekanten er (" + grunnlinje + " cm * " + trekantHoyde + " cm)/2 = " + areal + " cm2");
  return areal;
}