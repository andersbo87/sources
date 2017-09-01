PFont f;

void setup()
{
  size(400,400);
  f = createFont("Verdana",16, true);
}

void draw()
{
  background(255);
  stroke(175);
  line(width/2,0,width/2,height);
  textFont(f);
  fill(0);
  textAlign(CENTER);
  text("Dette er en midtstilt tekst.", width/2,60);
  textAlign(LEFT);
  text("Dette er en venstrestilt tekst.",width/2,100);
  textAlign(RIGHT);
  text("Dette er en høyrestilt tekst.",width/2,140);
}

