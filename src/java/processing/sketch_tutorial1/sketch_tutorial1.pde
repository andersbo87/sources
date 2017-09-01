void setup()
{
  size(480,120);
}
void draw()
{
  if(mousePressed) // Dersom man klikker på en av museknappene
  {
    fill(0);
  }
  else // Hvis ikke:
  {
    fill(255);
  }
  ellipse(mouseX, mouseY, 80,80);
}
