void oppgave6A()
{
  triangle(1,1,1,4,5,4);
}

void oppgave6B()
{
  
  triangle(1,4,5,4,5,1);
  translate(4,0);
  triangle(1,1,1,4,5,4); // Samme trekant som i oppgave A.
  translate(-4,3);
  triangle(1,1,5,1,5,4);
  translate(4,0);
  triangle(5,1,1,1,1,4);
}