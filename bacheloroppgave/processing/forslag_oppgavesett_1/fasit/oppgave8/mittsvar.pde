void oppgave8A()
{
  quad(3,1,6,1,6.8,4,2.4,4);
  triangle(4.5,6,2.4,4,6.8,4);
}

void oppgave8B()
{
  float sidekant = 3;
  translate(4,0);
  // Toppen på prismen
  triangle(4.5,1,2.3,3,6.4,3);
  quad(2.3,3,3,6,6,6,6.4,3);
  translate(sidekant,6);
  // En av sidene mellom bunnen og toppen er et kvadrat.
  rect(0,0,sidekant,sidekant);
  rect(3,0,sidekant,sidekant);
  rect(6,0,sidekant,sidekant);
  rect(-3,0,sidekant,sidekant);
  rect(-6,0,sidekant,sidekant);
  translate(-sidekant,2);
  // Bunnen på prismen
  quad(3,1,6,1,6.8,4,2.4,4);
  triangle(4.5,6,2.4,4,6.8,4);
  // De andre sidene er romber.
  /*quad(3,1,0.1,0.4,-0.5,3.3,2.4,4);
  quad(2.4,4,0.1,6,2.2,8,4.5,6);
  quad(4.5,6,6.8,8,9,6,6.8,4);
  quad(6,1,6.8,4,9.8,3.1,8.8,0.1);*/
}