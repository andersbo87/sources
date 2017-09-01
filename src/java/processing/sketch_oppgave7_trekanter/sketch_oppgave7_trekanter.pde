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
  drawTriangles(10.4);
}

void setup()
{
  size(596,843);
  frameRate(30);
}

// a er den nederste linja i trekanten
void drawTriangles(float a)
{
  // bruker verdien til a for å flytte origo nedover Y-aksen
  translate(1,a);
  // h = høyde
  float h = a * sin(TWO_PI/6); // På den måten blir (visst) vinkelen 60 grader.
  fill(205,92,92);
  stroke(205,92,92);
  triangle(0,0, a, 0, a/2, -h);
  
  translate(1, 6);
  h = a * sin(TWO_PI/12);
  fill(255, 140, 0);
  stroke(255, 140, 0);
  triangle(0,0, a, 0, a/2, -h);
  
  translate(1,6);
  h = a / 2;
  fill(128, 128, 0);
  stroke(128, 128, 0);
  triangle(0, 0, a, 0, a / 4, -h);
}