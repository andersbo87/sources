
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
  drawBox(170, 2, 8); // Tallet må deles på 6, siden det er 6 rektangler i en terning.
}

void setup()
{
  size(596,843);
  frameRate(30);
}

/*
v = volum
h = høyde
l = lengde
*/
void drawBox(float v, float h, float l)
{
  float b = v/(l*h);
  rect(0, 0, h, b);
  rect(h, 0, l, b);
  rect(h + l, 0, h, b);
  translate(h, b);
  rect(0, 0, l, h);
  translate(0, h);
  rect(0, 0, l, b);
  translate(0, b);
  rect(0, 0, l, h);
}