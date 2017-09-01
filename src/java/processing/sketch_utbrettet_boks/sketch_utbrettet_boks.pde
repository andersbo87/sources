void draw()
{
  makeA4();
  translate(1,1);
  drawBox(5); // 5 cm
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

void drawBox(float side) // side i cm
{
  translate(side,0);
  rect(0,0,side,side);
  translate(0,side);
  rect(0,0,side,side);
  translate(0,side);
  rect(0,0,side,side);
  translate(0,side);
  rect(0,0,side,side);
  translate(-side,-2*side);
  rect(0,0,side,side);
  translate(2*side,0);
  rect(0,0,side,side);
}