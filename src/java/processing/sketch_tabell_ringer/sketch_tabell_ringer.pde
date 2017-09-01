/*
Et program som lager noen ringer, igjen basert på musepekerens
posisjon, med hjelp av en tabell.
I motsetning til de andre eksemplene med tabeller, består dette
eksempelet av en egen klasse, Ring, istedenfor en primitiv datatype.
For å lage en ring, trykker man på en av museknappene.
Ringene vil vokse seg større og større.
*/

class Ring
{
  float x,y, diameter;
  boolean on = false;
  void start(float xpos, float ypos)
  {
    x = xpos;
    y = ypos;
    diameter = 1;
    on = true;
  }
  void grow()
  {
    if(on)
    {
      diameter += 0.5;
      if(diameter > 400)
      {
        on = false;
        diameter = 1;
      }
    }
  }
  void display()
  {
    if(on)
    {
      noFill();
      strokeWeight(4);
      stroke(204,153);
      ellipse(x,y,diameter, diameter);
    }
  }
}

Ring[] rings;
int numRings = 50;
int currentRing = 0;
void setup()
{
  size(500,500);
  rings = new Ring[numRings];
  int i = 0;
  while(i < rings.length)
  {
    rings[i] = new Ring();
    i++;
  }
}

void draw()
{
  background(0);
  for(int i = 0; i < rings.length; i++)
  {
    rings[i].grow();
    rings[i].display();
  }
}
void mousePressed()
{
  rings[currentRing].start(mouseX,mouseY);
  currentRing++;
  if(currentRing >= numRings)
    currentRing = 0;
}

