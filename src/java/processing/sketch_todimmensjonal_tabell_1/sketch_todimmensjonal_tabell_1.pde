/*
Dette er det første av to eksempler på "programmer" som bruker
2-dimmensjonale tabeller for å lage et "gråskalabilde".
*/

int cols;
int rows;
int [][]myArray;
void setup()
{
  size(200,200);
  cols = width;
  rows = height;
  myArray = new int[cols][rows];
}
void draw()
{
  for(int i = 0; i < cols; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      myArray[i][j] = int(random(255));
    }
  }
  
  // tegn opp punktene
  for(int i = 0; i < cols; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      stroke(myArray[i][j]);
      point(i,j);
    }
  }
}
