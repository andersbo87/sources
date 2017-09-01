float sfactor;
void lagA4()
{
  sfactor = 28.4;
  scale(sfactor, sfactor);
  strokeWeight(1/sfactor);
  background(150); // Grå bakgrunn
}

void setup()
{
  size(596,843);
  fill(255);
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
  text("Oppgave 5A",1,1);
  translate(0,0.5);
  noFill();
  oppgave5A();
  translate(4,6);
  text("Oppgave 5B", 1,1);
  translate(0,0.5);
  oppgave5B();
}

void mouseClicked()
{
  try{
    save("oppgave5.png");
    println("Bildet lagret som \"oppgave5.png\"");
  }
  catch(Exception e){
    println("Kunne ikke lagre bildet: " + e.getMessage());
  }
}
