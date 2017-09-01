void mittSvar()
{
  fill(#00FF00);
  stroke(#FFFFFF);
  float bredde = width/sfactor-2;
  float hoyde = height/sfactor-2;
  rect((bredde/2)-1,0,2,1);
  translate(1,1);
  rect(0,0,bredde, hoyde);
  rect((bredde/2)-3,0,4,1);
  ellipse((bredde/2)-1,2,0.1,0.1);
  noFill();
  rect((bredde/2)-4,0,6,2.5);
  // Tegner en halvsirkel på en eller annen måte...
  arc((bredde/2)-1,2.5,1.5,1.5,0,HALF_PI+HALF_PI);
}