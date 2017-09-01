float sfactor, svarAreal = 0;
float korrektAreal = 12; // 12 cm2, som oppgaven spesifiserer
int fargeKode = 150, i = 0;
void lagA4(){
  sfactor=28.4;
  scale(sfactor,sfactor);
  strokeWeight(1/sfactor);
  background(fargeKode);
}

void setup()
{
  // Skriv kode her
  lagA4();
  fill(255);
  size(596, 843);
}

void draw()
{
  lagA4();
  textSize(18/sfactor);
  fill(0);
  textAlign(LEFT);
  text("Klikk på vinduet for å lagre bilde som kan skrives ut.",0,1);
  translate(0,2);
  text("Oppgave 9",1,1);
  translate(1,2);
  fill(fargeKode);
  oppgave9();
  if(i == 0){
    if(svarAreal == korrektAreal)
    {
      println("Du har svart riktig!");
    }
    else
    {
      println("Arealet på trekanten din er feil. Endre på høyden og/eller grunnflata til trekanten (dette gjøres i fanen \"mittsvar\").");
    }
    i++;
  }
}
void trekant(float grunnflate, float hoyde)//, float hypotenus)
{
  triangle(0,0, grunnflate, 0, 0, hoyde);
}