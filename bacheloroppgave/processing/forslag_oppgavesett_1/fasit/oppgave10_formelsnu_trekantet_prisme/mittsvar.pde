float g = 12, th = 2; // g = grunnlinje, th = trekanthøyde
void oppgave10()
{
  brukerAreal = regnAreal(g,th);
  float ph = svarVolum/brukerAreal;
  brukerVolum = regnVolum(brukerAreal, ph);
  tegn(g, th, ph);
  
}
void tegn(float grunnlinje, float trekantHoyde, float prismeHoyde)
{
  translate(trekantHoyde,0);
  triangle(0,0, 0, trekantHoyde, grunnlinje, trekantHoyde);
  translate(-trekantHoyde,trekantHoyde);
  rect(0,0, trekantHoyde, prismeHoyde);
  translate(trekantHoyde,0);
  rect(0,0, grunnlinje, prismeHoyde);
  translate(grunnlinje,0);
  rect(0,0,sqrt((grunnlinje*grunnlinje)+(trekantHoyde*trekantHoyde)),prismeHoyde);
  translate(-grunnlinje,prismeHoyde);
  triangle(0,0, 0, trekantHoyde, grunnlinje, 0);
}