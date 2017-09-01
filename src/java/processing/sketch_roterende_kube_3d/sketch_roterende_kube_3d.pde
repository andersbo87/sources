/*
Kode som lager en gjennomsiktig kube på en svart bakgrunn.
Kuben roterer en vei når man klikker med musa
for så å rotere tilbake igjen når musa slippes.
Koden ble funnet her:
https://forum.processing.org/two/discussion/3080/rotating-cubes (bla ned til under
Answer #10081 by koogs from February 2014 -- der står det et svar fra Chrisir fra samme måned.
*/

//float sider = 200; // Denne kommenterte linja er opprinnelig kode fra nevnte side.
float vinkel1;

// Egenutviklet:
float side1 = 200;
float side2 = 300;
float side3 = 130;
// Slutt på egenutviklet kode

void setup()
{
  size(800, 800, P3D);
  smooth();
}

void draw()
{
  background(0);
  lights();
  
  /*
  Flytter origo til midten av vinduet
  */
  translate(width/2, height/2, -130);
  
  /*
  Kode som skal rotere kuben
  */
  noFill();
  if(mousePressed)
    vinkel1+=.01;
  else
    if(vinkel1 > 0)
      vinkel1-=.01;
  
  rotateY(vinkel1);
  stroke(255);
  
  // Kuben er transparent og bruker metoden box().
  
  //box(sider);
  
  // Egenutviklet kode:
  box(side1,side2,side3);
  // Slutt på egenutviklet kode
}