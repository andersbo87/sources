void tegnKube()
{
  // Skriv inn koden din her:
  // Vi må angi hvor stor hver sideflate er. Parameterne for å oppnå dette er: lengden, høyde. 
  foran = new Side(3,3);
  bak = new Side(3,3);
  venstre = new Side(3,3);
  hoyre = new Side(3,3);
  topp = new Side(3,3);
  bunn = new Side(3,3);
  kube = new Kube(foran, bak, venstre, hoyre, topp, bunn);
  kube.tegn();
}