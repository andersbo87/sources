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
  drawSquare();
}

void setup()
{
  size(596,843);
  frameRate(30);
}

void drawSquare()
{
  float side1 = 3;
  float side2 = 5;
  rect(0,0,side1,side1);
  translate(0,side1+1);
  rect(0,0,side2,side2);
}