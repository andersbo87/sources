float diagonal, side, hoydeKvadrat, hoyde;
void setup()
{
  size(200,200);
  diagonal = 10;
  side = 8;
  hoydeKvadrat = diagonal*diagonal-side*side;
  hoyde = sqrt((int)hoydeKvadrat);
  println("Høyde: " + hoyde + " cm");
  // Arealet i dm:
  float arealDm = (side/10)*(hoyde/10);
  float arealm = (side/100)*(hoyde/100);
  println("Areal: " + nfs(arealDm,1,3) + " dm\nAreal: " + nfs(arealm,1,4) + " m");
  frameRate(1);
}
void draw()
{
  translate(1,1);
  scale(20,20);
  background(255);
  strokeWeight(1/10);
  drawTriangle();
}

void drawTriangle()
{
  rect(0,0,side,hoyde);
  triangle(0,0,0,hoyde, side, 0);
}