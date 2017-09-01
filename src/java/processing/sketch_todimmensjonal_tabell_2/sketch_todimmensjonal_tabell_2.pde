/*
Dette er det andre eksempelet hvor et program benytter seg av
en dodimmensjonell tabell for å lage "gråskalabilde"
Denne gangen opererer vi med rektangler og en egen objektklasse
kalt Cell.
*/

class Cell
{
  float x,y; // stedet til x og y
  float w,h; // w = width (bredde), h = height (høyde)
  float angle; //"Vinkelen" som skal økes for å øke lysstyrken
  Cell(float newX, float newY, float newW, float newH, float newAngle)
  {
    x = newX;
    y = newY;
    h = newH;
    w = newH;
    angle = newAngle;
  }
  //Den egentlige tittelen på følgende funksjon er oscillate.
  void increaseAngle()
  {
    angle += 0.02;
  }
  void display()
  {
    stroke(255);
    fill(127+127*sin(angle));
    rect(x,y,w,h);
  }
}

Cell[][] grid;
// Antall kolonner og rader i rutefeltet
int cols = 10;
int rows = 10;

void setup()
{
  size(200,200);
  grid = new Cell[cols][rows];
  int i = 0;
  while(i < cols)
  {
    int j = 0;
    while(j < rows)
    {
      grid[i][j] = new Cell(i*20,j*20,20,20,i+j);
      j++;
    }
    i++;
  }
}

void draw()
{
  background(0);
  //Tellerne i og j er også rad- og kolonnenummer og blir også
  //brukt som argumenter til konstruktørene for hvert objekt i rutefeltet.
  int i = 0;
  while(i < cols)
  {
    int j = 0;
    while(j < rows)
    {
      grid[i][j].increaseAngle();
      grid[i][j].display();
      j++;
    }
    i++;
  }
}

