/*
  Et program som er ment å lage en kube i 3 dimensjoner.
  Mye av koden er basert på en kodesnutt fra https://processing.org/examples/spacejunk.html
*/


float vinkel;
Kube kube;
Side foran, bak, venstre, hoyre, topp, bunn;

void setup()
{
  //frameRate(30);
  size(1280,843,P3D);
  //background(0);
  noStroke();
  // Vi må angi hvor stor hver sideflate er. Parameterne for å oppnå dette er: lengden, høyde. 
  foran = new Side(3,3);
  bak = new Side(3,3);
  venstre = new Side(3,3);
  hoyre = new Side(3,3);
  topp = new Side(3,3);
  bunn = new Side(3,3);
  kube = new Kube(foran, bak, venstre, hoyre, topp, bunn);
}

void draw()
{
  noFill();
  scale(28.5,28.5,28.5);
  strokeWeight(1/28.5);
 background(0);
 fill(200);
 translate(1,1);
 oppgave3A();
 translate(0,5);
 oppgave3B();
 // Hentet fra https://processing.org/examples/spacejunk.html:
 pointLight(51,102,255,65,60,100);
 pointLight(200, 40, 60, -65, -60, -150);
 ambientLight(70, 70, 10);
 stroke(0,0,200);
 translate(20,-10,-5);//originalt: translate(width/2, height/2, 0);
 // Slutt på innhentet kode
 rotateX(rotx);
 rotateY(roty);
 kube.tegn();
}

// Følgende funksjon er hentet fra https://processing.org/examples/texturecube.html:
float rotx = PI/4;
float roty = PI/4;
void mouseDragged() {
  float rate = 0.01;
  rotx += (pmouseY-mouseY) * rate;
  roty += (mouseX-pmouseX) * rate;
}