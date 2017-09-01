class Car
{
  color c;
  float xpos;
  float ypos;
  float xspeed;
  Car(color newC, float newXpos, float newYpos, float newXspeed)
  {
    c = newC;
    xpos = newXpos;
    ypos = newYpos;
    xspeed = newXspeed;
  }
  void display()
  {
    rectMode(CENTER);
    fill(c);
    rect(xpos,ypos,20,10);
  }
  void drive()
  {
    xpos = xpos + xspeed;
    if(xpos > width)
      xpos = 0;
  }
  void driveY()
  {
    ypos = ypos + xspeed;
    if(ypos > height)
      ypos = 0;
  }
} // End of class

Car car1;
Car car2;
Car car3;
void setup()
{
  car1 = new Car(color(255,255,0),0,10,1);
  car2 = new Car(color(255,0,0),10,20,2);
  car3 = new Car(color(0,0,255),20,40,10);
}
void draw()
{
  background(255);
  car1.drive();
  car1.display();
  car2.drive();
  car2.display();
  car3.driveY();
  car3.display();
}
