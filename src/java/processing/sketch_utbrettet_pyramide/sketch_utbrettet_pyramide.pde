
void draw()
{
  makeA4();
  drawPyramide(5,5);
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

void drawPyramide(float ps, float ph)
{
  float pth = sqrt((ps/2)*(ps/2)+ph*ph);
  translate(pth+ps/2,pth+ps/2);
  rect(-ps/2,-ps/2,ps,ps);
  triangle(-ps/2, -ps/2, -pth-ps/2, 0, -ps/2, ps/2); //venstre
  triangle(ps/2, -ps/2, pth+ps/2, 0, ps/2, ps/2); //høyre
  triangle(-ps/2, -ps/2, 0, -ps/2-pth, ps/2, -ps/2); //oppe
  triangle(-ps/2, ps/2, 0, ps/2+pth, ps/2, ps/2); // nede
}