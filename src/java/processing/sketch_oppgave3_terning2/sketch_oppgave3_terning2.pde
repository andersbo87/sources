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
  drawDice(220/6); // Tallet må deles på 6, siden det er 6 rektangler i en terning.
}

void setup()
{
  size(596,843);
  frameRate(30);
}

void drawDice(float o)
{
  
  float side = sqrt(o);
  translate(side,0);
  rect(0,0,side,side);
  translate(-side,side);
  rect(0,0,side,side);
  translate(side,0);
  rect(0,0,side,side);
  translate(side,0);
  rect(0,0,side,side);
  translate(-side,side);
  rect(0,0,side,side);
  translate(0,side);
  rect(0,0,side,side);
}