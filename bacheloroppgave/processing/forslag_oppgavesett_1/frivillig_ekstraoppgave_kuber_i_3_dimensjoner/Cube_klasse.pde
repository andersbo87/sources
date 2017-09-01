/*
  Programkode for å generere selve kuba. IKKE REDIGER DENNE FILEN, 
  med mindre du vet hva du gjør.
  Hvis du likevel vil eksperimentere, så sørg for å ha en
  sikkerhetskopi av filen i tilfelle ting går galt.
  
  Koden er basert på en kodesnutt fra https://processing.org/examples/spacejunk.html
*/

class Kube
{
  /*
  Kubens egenskaper:
  b = bredde 
  h = høyde
  d = dybde
  */
  float b, h, d;
  int shiftX, shiftY, shiftZ;
  Side foran;
  Side bak;
  Side venstre;
  Side hoyre;
  Side bunn;
  Side topp;
  
  Kube(Side nyForan, Side nyBak, Side nyVenstre, Side nyHoyre, Side nyTopp, Side nyBunn)
  {
    foran   = nyForan;
    bak     = nyBak;
    venstre = nyVenstre;
    hoyre   = nyHoyre;
    topp    = nyTopp;
    bunn    = nyBunn;
    
    // Definerer bredden til å være lik høyresiden sin lengde. Dette for å slippe å angi bredden til hver eneste sideflate.
    d = hoyre.hentBredde();
  }
  
  // En funksjon som tegner alle kantene og som setter dem sammen til det som skal bli en kube.
  // Alle vertex-funksjonene er hentet fra https://processing.org/examples/spacejunk.html
  void tegn()
  {
    beginShape(QUADS);
    b = foran.hentBredde();
    h = foran.hentHoyde();
    vertex(-b/2 + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(b + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(b + shiftX, h + shiftY, -d/2 + shiftZ); 
    vertex(-b/2 + shiftX, h + shiftY, -d/2 + shiftZ);
    
    b = bak.hentBredde();
    h = bak.hentHoyde();
    vertex(-b/2 + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(b + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(b + shiftX, h + shiftY, d + shiftZ); 
    vertex(-b/2 + shiftX, h + shiftY, d + shiftZ);
    
    b = venstre.hentBredde();
    h = venstre.hentHoyde();
    vertex(-b/2 + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(-b/2 + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(-b/2 + shiftX, h + shiftY, d + shiftZ); 
    vertex(-b/2 + shiftX, h + shiftY, -d/2 + shiftZ);
    
    b = hoyre.hentBredde();
    h = hoyre.hentHoyde();
    vertex(b + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(b + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(b + shiftX, h + shiftY, d + shiftZ); 
    vertex(b + shiftX, h + shiftY, -d/2 + shiftZ);
    
    b = topp.hentBredde();
    h = topp.hentHoyde();
    vertex(-b/2 + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(b + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(b + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(-b/2 + shiftX, -h/2 + shiftY, d + shiftZ);
    
    b = bunn.hentBredde();
    h = bunn.hentHoyde();
    vertex(-b/2 + shiftX, h + shiftY, -d/2 + shiftZ); 
    vertex(b + shiftX, h + shiftY, -d/2 + shiftZ); 
    vertex(b + shiftX, h + shiftY, d + shiftZ); 
    vertex(-b/2 + shiftX, h + shiftY, d + shiftZ); 
    
    endShape();
  }
}