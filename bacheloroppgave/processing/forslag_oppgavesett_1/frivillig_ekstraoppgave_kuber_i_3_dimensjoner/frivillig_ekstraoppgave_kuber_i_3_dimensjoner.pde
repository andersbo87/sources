
/*
  Et program som er ment å lage en kube i 3 dimensjoner.
  Mye av koden er basert på en kodesnutt fra https://processing.org/examples/spacejunk.html
  IKKE REDIGER DENNE FILEN, 
  med mindre du vet hva du gjør.
  Hvis du likevel vil eksperimentere, så sørg for å ha en
  sikkerhetskopi av filen i tilfelle ting går galt.
*/


float vinkel;
Kube kube;
Side foran, bak, venstre, hoyre, topp, bunn;

void setup()
{
  frameRate(30);
  size(696,843,P3D);
  background(0);
  noStroke();
}

void draw()
{
 background(0);
 fill(200);
 // Hentet fra https://processing.org/examples/spacejunk.html:
 pointLight(51,102,255,65,60,100);
 pointLight(200, 40, 60, -65, -60, -150);
 ambientLight(70, 70, 10);
 stroke(0,0,200);
 translate(width/2, height/2, 0);
 // Slutt på innhentet kode
 rotateX(rotx);
 rotateY(roty);
 tegnKube();
}

// Følgende funksjon er hentet fra https://processing.org/examples/texturecube.html:
float rotx = PI/4;
float roty = PI/4;
void mouseDragged() {
  float rate = 0.01;
  rotx += (pmouseY-mouseY) * rate;
  roty += (mouseX-pmouseX) * rate;
}
// Slutt på hentet kode