void draw()
{
  makeA4();
  translate(1,1);
  drawCylinder(5,10); // diameter på 5, høyde på 10
}

void setup()
{
  size(596,843);
  frameRate(1);
}

void makeA4()
{
  float sfactor = 28.4;
  scale(sfactor,sfactor);
  strokeWeight(1/sfactor);
  background(255);
}

void drawCylinder(float d, float h)
{
  float r = d/2; // r = radius
  float w = d*PI; // w = witdth = bredde
  translate(w/2, r);
  ellipse(0, 0, d, d);
  translate(0, r);  
  rect(-w/2, 0, w, h);
  translate(0, h+r);
  ellipse(0, 0, d, d);
}