/*
Forventer ikke at så mange skal få til denne her, hvis noen i det hele tatt.
Dette er kun ment som en ekstraoppgave for de som har lyst på en ekstra utfordring.
*/

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
  // Skriv kode her
  size(686,843);
  fill(255);
  translate(1,1);
}

void draw()
{
  // Skriv kode her
  lagA4();
  textSize(18/sfactor);
  fill(0);
  textAlign(LEFT);
  text("Klikk på vinduet for å lagre bilde som kan skrives ut.",0,0.5);
  translate(0,1);
  mittSvar();
}

void mouseClicked()
{
  save("rugbybane.png");
}