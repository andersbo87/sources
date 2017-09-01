/*
  Programkode for å generere selve kuba. Ikke rediger denne
  filen, med mindre du vet hva du gjør.
  Hvis du likevel vil eksperimentere, så sørg for å ha en
  sikkerhetskopi av filen i tilfelle ting går galt.
  
  Koden er basert på en kodesnutt fra https://processing.org/examples/spacejunk.html
  
*/

class Kube
{
  /*
  Kubens egenskaper:
  w = vidde (det samme som bredde)
  h = høyde
  d = dybde
  */
  float w, h, d;
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
    d = hoyre.v;
  }
  
  // En funksjon som tegner alle kantene og som setter dem sammen til det som skal bli en kube.
  // Alle vertex-funksjonene er hentet fra https://processing.org/examples/spacejunk.html
  void tegn()
  {
    beginShape(QUADS);
    w = foran.v;
    h = foran.h;
    vertex(-w/2 + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(w + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(w + shiftX, h + shiftY, -d/2 + shiftZ); 
    vertex(-w/2 + shiftX, h + shiftY, -d/2 + shiftZ);
    
    w = bak.v;
    h = bak.h;
    vertex(-w/2 + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(w + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(w + shiftX, h + shiftY, d + shiftZ); 
    vertex(-w/2 + shiftX, h + shiftY, d + shiftZ);
    
    w = venstre.v;
    h = venstre.h;
    vertex(-w/2 + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(-w/2 + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(-w/2 + shiftX, h + shiftY, d + shiftZ); 
    vertex(-w/2 + shiftX, h + shiftY, -d/2 + shiftZ);
    
    w = hoyre.v;
    h = hoyre.h;
    vertex(w + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(w + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(w + shiftX, h + shiftY, d + shiftZ); 
    vertex(w + shiftX, h + shiftY, -d/2 + shiftZ);
    
    w = topp.v;
    h = topp.h;
    vertex(-w/2 + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(w + shiftX, -h/2 + shiftY, -d/2 + shiftZ); 
    vertex(w + shiftX, -h/2 + shiftY, d + shiftZ); 
    vertex(-w/2 + shiftX, -h/2 + shiftY, d + shiftZ);
    
    w = bunn.v;
    h = bunn.h;
    vertex(-w/2 + shiftX, h + shiftY, -d/2 + shiftZ); 
    vertex(w + shiftX, h + shiftY, -d/2 + shiftZ); 
    vertex(w + shiftX, h + shiftY, d + shiftZ); 
    vertex(-w/2 + shiftX, h + shiftY, d + shiftZ); 
    
    endShape();
  }
}
