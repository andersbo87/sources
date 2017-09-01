float sfactor;
void lagA4()
{
  sfactor = 28; // originalt: 28.4
  scale(sfactor, sfactor);
  strokeWeight(1/sfactor);
  background(150);
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
  text("Oppgave 8A",1,1);
  translate(0,0.5);
  noFill();
  oppgave8A();
  // Må flytte origo nærmere midten av vinduet/arket.
  translate(0,10);
  text("Oppgave 8B", 1,1);
  translate(0,0.5);
  oppgave8B();
}

void mouseClicked()
{
  try{
    save("oppgave8.png");
    println("Bildet lagret som \"oppgave8.png\"");
  }
  catch(Exception e){
    println("Kunne ikke lagre bildet: " + e.getMessage());
  }
}