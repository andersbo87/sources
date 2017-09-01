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
  drawDice();
}

void setup()
{
  size(596,843);
  frameRate(30);
}

void drawDice()
{
  translate(5,5);
  rect(0,0,5,5);
  translate(0,5);
  rect(0,0,5,5);
  translate(-5,0);
  rect(0,0,5,5);
  translate(10,0);
  rect(0,0,5,5);
  translate(-5,5);
  rect(0,0,5,5);
  translate(0,5);
  rect(0,0,5,5);
}