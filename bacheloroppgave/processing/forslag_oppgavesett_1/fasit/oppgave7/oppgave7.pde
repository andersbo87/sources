float sfactor;
void lagA4()
{
  sfactor = 28.4;
  scale(sfactor, sfactor);
  strokeWeight(1/sfactor);
  background(150);
}

void setup()
{
  size(596,843);
  fill(255);
  frameRate(30);
}

void draw()
{
  lagA4();
  textSize(18/sfactor);
  fill(0);
  textAlign(LEFT);
  text("Klikk på vinduet for å lagre bilde som kan skrives ut.",0,1);
  translate(0,2);
  text("Oppgave 7",1,1);
  translate(0,0.5);
  noFill();
  translate(0,2);
  oppgave7();
}

void mouseClicked()
{
  try{
    save("oppgave7.png");
    println("Bildet lagret som \"oppgave7.png\"");
  }
  catch(Exception e){
    println("Kunne ikke lagre bildet: " + e.getMessage());
  }
}