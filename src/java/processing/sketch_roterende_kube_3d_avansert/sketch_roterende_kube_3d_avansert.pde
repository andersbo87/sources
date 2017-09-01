/*
Følgende kode ble funnet her: http://www.openprocessing.org/sketch/128715
*/

PFont f;
void setup()
{
  size(640, 480, P3D);
  f = createFont("Arial",20, true); // Prøver å få til en lesbar font med en lesbar størrelse..
}

int faktor_z_rotering = 0; // variabel for å styre faktoren for rotering rundt Z-aksen. Styres av piltastene.
int bredde = 200;
int hoyde = 300;
int dybde = 150;


void draw()
{
  //translate(0,1);
  float roterX = (mouseX/360.0)*-2*PI+PI;
  float roterY = (mouseY/420.0)*2*PI-PI;
  float roterZ = faktor_z_rotering*PI/36;
  
  background(0);
  
  fill(255);
  textFont(f,20);
  text("rotateX(" + roterX + " pi)"+", rotateY(" + roterY/PI+" pi), rotateZ(" + faktor_z_rotering + "pi/36)", 0, 25);
  stroke(0, 0, 200);
  line(0, 30, width, 30);//orig:line(0,20,420,20);
  fill(0, 0, 200);
  text("Musa kontrollerer X og Y-akse, piltastene kontrollerer Z-aksen\n", 0, 52);
  
  //translate(210, 180, 0);
  translate(width/2, height/2, -130);
  strokeWeight(1);
  stroke(50);
  line(-60, 0, 60, 0);
  line(0, 60, 0, -60);
  line(0, 0, -60, 0, 0, 60);
  strokeWeight(1);
  stroke(0, 150, 0);
  noFill();
  //box(140); // størrelse 140 på alle kanter. metoden box kan også ta 3 argumenter, en for høyde, lengde og bredde.
  box(bredde, hoyde, dybde);
  
  rotateX(roterX);
  rotateY(roterY);
  rotateZ(roterZ);
  strokeWeight(2);
  stroke(255);
  line(-150, 0, 150, 0);
  line(0, 150, 0, -150);
  line(0, 0, -150, 0, 0, 150);
  strokeWeight(2);
  stroke(255, 0, 0);
  noFill();
  //box(140);
  box(bredde, hoyde, dybde);
}

void keyPressed()
{
  if(key == CODED)
  {
    if(keyCode == UP)
    {
      faktor_z_rotering++;
    }
    else if(keyCode == DOWN)
    {
      faktor_z_rotering--;
    }
  }
}
