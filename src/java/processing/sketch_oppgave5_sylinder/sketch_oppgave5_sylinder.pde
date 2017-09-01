void makeA4(String name)
{
  float sfactor = 28.4; // pixels per centimeter
  scale(sfactor,sfactor);
  strokeWeight(1/sfactor);
  textSize(18/sfactor);
  fill(0);
  textAlign(RIGHT);
  text(name,20,1);
  textAlign(LEFT);
  fill(255);
}

void draw()
{
  makeA4("Anders");
  translate(1,1);
  drawCylinder(200,5);
}

void setup()
{
  size(596,843);
  frameRate(30);
}

/*
v = volum
d = diameter
*/
void drawCylinder(float v, float d)
{
  float r = d/2, o = d*PI, l=v/(r*r*PI);
  ellipse(10,d/2,d,d);
  rect(10-o/2,d,o,l);
  ellipse(10,d+l+d/2,d,d);
}