void setup()
{
  size(300,300);
  background(255);
  rectMode(CENTER);
}

void draw()
{
  int r = int(random(0,255));
  int g = int(random(0,255));
  int b = int(random(0,255));
  
  int opacity = int(random(100,255));
  int nSides = int(random(3,9));
  
  int cx = 25 + 50 * int(random(0,6));
  int cy = 25 + 50 * int(random(0,6));
  
  boolean isPolygon = int(random(2)) == 0;
  float proportion;
  stroke(255);
  fill(255);
  rect(cx, cy, 50, 50);
  stroke(r,g,b);
  fill(r,g,b,opacity);
  if(isPolygon)
    polygon(nSides,cx,cy,24);
  else
  {
    proportion = random(0.2,0.8) * cos(PI/nSides);
    star(nSides,cx,cy,24,proportion);
  }
}

void polygon(int n, float cx, float cy, float r) {
  float angle = 360.0 / n;
  beginShape();
  for (int i = 0; i < n; i++) {
    vertex(cx + r * cos(radians(angle * i)),
      cy + r * sin(radians(angle * i)));
  }
  endShape(CLOSE);
}

void star(int n, float cx, float cy, float r, float proportion) {
  star(n, cx, cy, 2.0 * r, 2.0 * r, 0.0, proportion);
}

void star(int n, float cx, float cy, float w, float h,
  float startAngle, float proportion) {
  if (n > 2) {
    float angle = TWO_PI/ (2 *n);  // twice as many sides
    float dw; // draw width
    float dh; // draw height
    
    w = w / 2.0;
    h = h / 2.0;
    
    beginShape();
    for (int i = 0; i < 2 * n; i++)
    {
      dw = w;
      dh = h;
      if (i % 2 == 1) // for odd vertices, use short radius
      {
        dw = w * proportion;
        dh = h * proportion;
      }
      vertex(cx + dw * cos(startAngle + angle * i),
        cy + dh * sin(startAngle + angle * i));
    }
    endShape(CLOSE);
  }
}

