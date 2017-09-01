class Mover
{
   PVector location;
   PVector velocity;
   PVector acceleration;
   float topspeed;
   
   //Konstruktør:
   Mover()
   {
     location = new PVector(random(width), random(height));
     velocity = new PVector(0,0);
     topspeed = 4;
   }
   void update()
   {
     // Dette er en algoritme som beregner akselerasjonen.
     PVector mouse = new PVector(mouseX, mouseY);
     PVector dir = PVector.sub(mouse,location);
     dir.normalize();
     dir.mult(0.5); // skaler vektoren (i dette tilfellet halver den).
     acceleration = dir;
     
     velocity.add(acceleration);
     velocity.limit(topspeed);
     location.add(velocity);
   }
   void display()
   {
     stroke(0);
     fill(75);
     ellipse(location.x, location.y,16,16);
   }
   void checkEdges()
   {
     if(location.x > width)
       location.x = 0;
     else if(location.x < 0)
       location.x = width;
     if(location.y > height)
       location.y = 0;
     else if(location.y < 0)
       location.y = height;
   }
}

Mover[] movers = new Mover[20];
void setup()
{
  size(200,200);
  smooth();
  background(255); // hvit bakgrunn, som vanlig...
  for(int i = 0; i < movers.length; i++)
    movers[i] = new Mover();
}

void draw()
{
  noStroke();
  fill(255,10);
  rect(0,0,width, height);
  for(int i = 0; i < movers.length; i++)
  {
    movers[i].update();
    movers[i].checkEdges();
    movers[i].display();
  }
}