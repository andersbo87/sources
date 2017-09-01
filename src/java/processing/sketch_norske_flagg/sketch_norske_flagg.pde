void setup()
{
  size(596,843);
  frameRate(1);
}

void draw()
{
  makeA4();
  translate(1,1);
  drawFlag(15);
  translate(0,15);
  drawFlag(5);
  translate(10,0);
  drawFlag(5);
}

void makeA4()
{
  float sfactor = 28.4;
  scale(sfactor,sfactor);
  strokeWeight(1/sfactor);
  background(255);
}

void drawFlag(float l)
{
  float unit = l/22;
  float h = unit * 16; // hvorfor 16?
  
  /*
  De røde delene i flagget vårt:
  */
  fill(255,0,0);
  stroke(0);
  rect(0,0,l,h);
  
  /*
  Den hvite, ytre delen av korset
  */
  fill(255);
  stroke(255);
  rect(0,6*unit,l,4*unit);
  rect(6*unit,0,4*unit,16*unit);

  /*
  Den blå, indre delen av korset
  */
  fill(0,0,255);
  stroke(0,0,255);
  rect(0,7*unit,l,2*unit);
  rect(7*unit,0,2*unit,16*unit);

  /*Kanten på flagget*/
  noFill();
  stroke(0);
  rect(0,0,l,h);
}