void mittSvar()
{
  /*
    Må finne en måte å omgå regning med trigonometri, siden dette ikke er del
    av pensum i ungdomskolen. Tenker her, som i oppgave 9, å lage 2 trekanter
    per side i pyramiden.
  */
  float volum = 100; // "cm"3
  float side = 8; // cm, som definert i oppgaven
  float grunnlinje = side/2;
  /*
    Ifølge oppgaveteksten skal bunnen av pyramiden være en likesidet trekant.
    Det betyr at vinklene må være 60 grader.
    For å jobbe oss rundt trigonometrien, må vi dele trekanten i 2 rettvinklkede trekanter
    som hver har en grunnlinje (en av kartetene) på 4 cm og en hypotenus på 8 cm.
    Den gjenstående kateten er da høyden på trekanten. Dette kan vi bruke til å regne ut
    arealet av trekanten.
  */
  // Siden vi nå har 2 rettvinklede trekanter, kan vi bruke pytagoras
  float trekanthoyde = sqrt((side*side)-(grunnlinje*grunnlinje));
  float areal = trekanthoyde * grunnlinje; // "cm"2
  if(i == 0){
     println("Høyden på trekanten\t" + trekanthoyde + "\nArealet til trekanten:\t" + areal);
     i++;
  }
   
   //float pyramideHoyde = 11;
   /*
     I følge http://matematikk.net/matteprat/viewtopic.php?t=314817
     er formelen for å regne ut høyden på pyramiden lik 3V/G, der V = volum og G = Grunnflate/areal.
   */
   float pyramideHoyde = (3*volum)/areal;
   float brukerVolum = (areal*pyramideHoyde)/3;
   if(j == 0){
     println("Volumet til pyramiden: " + brukerVolum);
     j++;
   }
   
   /*
     Tegner nå den utbrettede pyramiden
   */
   translate(8,0);
   // La oss begynne med den øverste trekanten.
   triangle(0,6.9,4,0,8,6.9);
   translate(0,6.9);
   // La oss deretter tegne trekanten som er grunnflata
   // Jeg deler den i 2 for å kunne tegne streken som viser "høyden" på trekanten.
   // Dette for å visualisere det jeg gjorde i koden over.
   triangle(0,0,4,6.9,4,0);
   triangle(4,0,4,6.9,8,0);
   // La oss deretter tegne trekanten som er lengst til venstre
   triangle(0,0,-4,6.9,4,6.9);
   // Og til slutt den som er lengst til høyre.
   translate(8,0);
   triangle(0,0,-4,6.9,4,6.9);
}