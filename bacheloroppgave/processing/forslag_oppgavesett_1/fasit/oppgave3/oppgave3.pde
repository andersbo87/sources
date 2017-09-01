float sfactor;
void lagA4()
{
  sfactor = 28;
  // Skalerer det slik at det blir noenlunde rette mål (i alle fall på papir)
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
  text("Oppgave 3A",1,1);
  translate(1,1.5);
  noFill();
  oppgave3A();
  translate(0,4);
  text("Oppgave 3B",1,1);
  translate(5,1.5);
  oppgave3B();
}

void mouseClicked()
{
  try{
    save("oppgave3.png");
    println("Bildet lagret som \"oppgave3.png\"");
  }
  catch(Exception e){
    println("Kunne ikke lagre bildet: " + e.getMessage());
  }
}