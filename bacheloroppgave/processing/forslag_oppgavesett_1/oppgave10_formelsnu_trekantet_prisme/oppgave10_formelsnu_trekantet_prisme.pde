float sfactor;
float brukerAreal, brukerVolum;
String filnavn = "oppgave10.png";
int i = 0;
final float svarVolum = 60; // Ordet "final" betyr at det er en konstant.
void lagA4()
{
  sfactor=28.4;
  scale(sfactor,sfactor);
  strokeWeight(1/sfactor);
  background(150);
}

float regnVolum(float areal, float prismeHoyde)
{
  float volum = areal * prismeHoyde;
  return volum;
}

float regnAreal(float grunnlinje, float trekantHoyde)
{
  float areal = (grunnlinje*trekantHoyde)/2;
  return areal;
}

void setup()
{
  size(843,596);
}
void draw()
{
  lagA4();
  translate(1,1);
  textSize(18/sfactor);
  fill(0);
  textAlign(LEFT);
  text("Klikk på vinduet for å lagre bilde som kan skrvies ut.",0,1);
  translate(0,2);
  text("Oppgave 10",1,1);
  translate(0,2.5);
  noFill();
  oppgave10();
  if(i == 0){
    if(brukerVolum == svarVolum)
    {
      println("Korrekt! Volumet er på " + svarVolum + " cm3");
    }
    else{
      println("Svaret " + brukerVolum + " er feil. Endre på koden i mittsvar for å endre størrelsen på trekanten eller høyden på prismen");
    }
    i++;
  }
}


void mouseClicked()
{
  try{
    save(filnavn);
    println("Bildet lagret som " + filnavn);
  }
  catch(Exception e)
  {
    println("Kunne ikke lagre bildet: " + e.getMessage());
  }
}