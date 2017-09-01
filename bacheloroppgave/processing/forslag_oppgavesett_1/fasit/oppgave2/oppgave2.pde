float sfactor;
void lagA4()
{
  sfactor = 28.4; 
  scale(sfactor, sfactor);
  strokeWeight(1/sfactor);
  background(255);
}

void setup()
{
  size(596,843);
  fill(255);
  translate(1,1);
  frameRate(2);
}

void draw()
{
  lagA4();
  textSize(18/sfactor);
  fill(0);
  textAlign(LEFT);
  text("Klikk på vinduet for å lagre bilde som kan skrives ut.",0,1);
  translate(0,2);
  text("Oppgave 2A",1,1);
  translate(0,0.5);
  noFill();
  oppgave2A();
  translate(0,10);
  text("Oppgave 2B",1,1);
  translate(0,0.5);
  oppgave2B();
}

void mouseClicked()
{
  try{
    save("oppgave2.png");
    println("Bildet lagret som \"oppgave2.png\"");
  }
  catch(Exception e){
    println("Kunne ikke lagre bildet: " + e.getMessage());
  }
}
