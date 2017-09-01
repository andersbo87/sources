
void oppgave3A()
{
  // Skriv kode her:
  rect(0,0,4,4);
}

void oppgave3B()
{
  // Skriv kode her
  // Flytter origo noen cm bortover X-aksen
  translate(foran.v,0);
  //rect(0,0,4,4);
  rect(0,0,foran.h, foran.v);
  translate(0,foran.h);
  rect(0,0,bunn.h,bunn.v);
  translate(-bunn.v,0);
  rect(0,0,venstre.h,venstre.v);
  translate(venstre.v*2,0);
  rect(0,0,hoyre.h,bak.v);
  translate(-hoyre.v,hoyre.h);
  rect(0,0,bak.h,bak.v);
  translate(0,bak.h);
  rect(0,0,topp.h,topp.v);
}