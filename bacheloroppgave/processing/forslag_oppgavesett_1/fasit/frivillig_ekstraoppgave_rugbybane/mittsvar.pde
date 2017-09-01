void mittSvar()
{
  // Skriv inn kode her
  float h = (height/sfactor)/4-2; // trekker fra 2 av den enkle grunnen at det første rektangelet går 2 punkter på Y-aksen
  float b = width/sfactor;
  translate(0,2);
  fill(0,255,0);
  stroke(255);
  // Try-zone
  rect(0,0,b,2);
  translate(0,2);
  // Nederste punkt i rektangelen markerer 22-metersstreken
  //rect(0,0,b,h/4-2);
  rect(0,0,b,h);
  
  // Horisontale linjer. Disse markerer 5 meter fra målstreken
  line(1,1,3,1);
  line(5,1,7,1);
  line(9,1,11,1);
  line(13,1,15,1);
  line(17,1,19,1);
  line(21,1,23,1);
  
  // Vertikale linjer. Disse markerer 5 og 15 meter fra sidelinja.
  line(2,1,2,2);
  line(6,1,6,2);
  line(b-6,1,b-6,2);
  line(b-2,1,b-2,2);
  
  // Øverste del av striper på 22-metersstreken
  line(2,5,2,5.5);
  line(6,5,6,5.5);
  line(b-6,5,b-6,5.5);
  line(b-2,5,b-2,5.5);
  
  //translate(0,h/4-2);
  translate(0,h);
  /*
  Nederste streken i rektangelet utgjør midtstreken.
  Av en eller annen merkelig grunn kan man ikke tegne
  linje gjennom nederste delen av et rektangel når man bruker
  translate-funksjonen. Dette fører til at man må bruke
  et slags dobbelt sett med line().
  */
  //rect(0,0,b,h/4-2);
  rect(0,0,b,h);
  
  // Nederste del av 22-meterstreken
  line(2,0,2,0.5);
  line(6,0,6,0.5);
  line(b-6,0,b-6,0.5);
  line(b-2,0,b-2,0.5);
  
  // 10-metersstreker (horisontale)
  line(1,3.6,3,3.6);
  line(5,3.6,7,3.6);
  line(9,3.6,11,3.6);
  line(13,3.6,15,3.6);
  line(17,3.6,19,3.6);
  line(21,3.6,23,3.6);
  
  // Vertikale streker som krysser 10-meterstrekene
  line(2,3,2,4.2);
  line(6,3,6,4.2);
  line(b-6,3,b-6,4.2);
  line(b-2,3,b-2,4.2);
  
  // Øverste del av midtstreken
  line(2,5,2,5.5);
  line(6,5,6,5.5);
  line(b-6,5,b-6,5.5);
  line(b-2,5,b-2,5.5);
  //translate(0,h/4-2);
  translate(0,h);
  
  // Andre banehalvdel
  //rect(0,0,b,h/4-2);
  rect(0,0,b,h);
  
  // Nederste del av midstreken
  line(2,0,2,0.5);
  line(6,0,6,0.5);
  line(b-6,0,b-6,0.5);
  line(b-2,0,b-2,0.5);
  
  // 10 meter (horisontalt)
  line(1,1.9,3,1.9);
  line(5,1.9,7,1.9);
  line(9,1.9,11,1.9);
  line(13,1.9,15,1.9);
  line(17,1.9,19,1.9);
  line(21,1.9,23,1.9);
  
  // Vertikale linjer som krysser 10-meterslinjene
  line(2,1.4,2,2.4);
  line(6,1.4,6,2.4);
  line(b-6,1.4,b-6,2.4);
  line(b-2,1.4,b-2,2.4);
  
  // Øverste del av 22-metersstreken
  line(2,5,2,5.5);
  line(6,5,6,5.5);
  line(b-6,5,b-6,5.5);
  line(b-2,5,b-2,5.5);
  //translate(0,h/4-2);
  translate(0,h);
  // Øverste del av rektangelet er 22-meterstreken. Nederste del er mållinja.
  //rect(0,0,b,h/4-2);
  rect(0,0,b,h);
  // Nederste del av 22-metersstreken
  line(2,0,2,0.5);
  line(6,0,6,0.5);
  line(b-6,0,b-6,0.5);
  line(b-2,0,b-2,0.5);
  
  // Horisontale linjer på 5-metersstreken
  line(1,h-1,3,h-1);
  line(5,h-1,7,h-1);
  line(9,h-1,11,h-1);
  line(13,h-1,15,h-1);
  line(17,h-1,19,h-1);
  line(21,h-1,23,h-1);
  
  // Vertikale streker som går ut fra 5-metersstrekene
  line(2,h-1,2,h-2);
  line(6,h-1,6,h-2);
  line(b-6,h-1,b-6,h-2);
  line(b-2,h-1,b-2,h-2);
  
  //translate(0,h/4-2);
  translate(0,h);
  // Try-zone
  rect(0,0,b,2);
}