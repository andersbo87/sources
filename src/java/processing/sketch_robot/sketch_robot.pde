int armAngle = 0;
int angleChange = 5;
final int ANGLE_LIMIT = 135;

void setup()
{
  size(200,200);
  smooth();
  frameRate(30);
}

void draw()
{
  background(255);
  pushMatrix();
  translate(50,50);
  drawRobot();
  armAngle += angleChange;
  /*Hvis armen beveger seg utenfor grensene, trekk armen inn igjen
  så den havner innenfor grensene.*/
  if(armAngle > ANGLE_LIMIT || armAngle < 0)
  {
    angleChange = -angleChange;
    armAngle += angleChange;
  }
  popMatrix();
}

void drawRobot()
{
  noStroke();
  fill(38,38,200);
  rect(20,0,38,30); // Robotens hode
  rect(14,32,50,50); // Kroppen til roboten
  drawLeftArm();
  drawRightArm();
  rect(22,84,16,50); // Venstre ben
  rect(40,84,16,50); // Høyre ben
  fill(222,222,249);
  ellipse(30,12,12,12); // Venstre øye
  ellipse(47,12,12,12); // Høyre øye
}

void drawLeftArm()
{
  pushMatrix();
  translate(12,32);
  rotate(radians(armAngle));
  rect(-12,0,12,37);
  popMatrix();
}

void drawRightArm()
{
  pushMatrix();
  translate(66,32);
  rotate(radians(-armAngle));
  rect(0,0,12,37);
  popMatrix();
}


