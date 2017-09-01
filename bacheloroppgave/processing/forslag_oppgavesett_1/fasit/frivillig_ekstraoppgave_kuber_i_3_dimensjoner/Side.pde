/*
  En klasse som brukes til å ta vare på hver kant/side sin lengde og bredde.
  IKKE REDIGER DENNE FILEN, 
  med mindre du vet hva du gjør.
  Hvis du likevel vil eksperimentere, så sørg for å ha en
  sikkerhetskopi av filen i tilfelle ting går galt.
  
  v = vidde eller bredde
  h = høyde
  Greia med å gange verdiene med 28,4 er basert på tankegangen i funksjonen lagA4
  som brukes for å lage 2-dimensjonale utbrettede figurer.
*/
class Side
{
   private float b, h;
   Side(float bredde, float hoyde)
   {
     b = bredde * 28.4;
     h = hoyde * 28.4;
   }
   
   // En funksjon som henter bredden/vidden til siden
   public float hentBredde()
   {
     return b;
   }
   
   //En funksjon som henter høyden til siden
   public float hentHoyde()
   {
     return h;
   }
   
   // En funksjon som setter vidden (eller hva du vil kalle det for) til siden. Parameteren er den nye vidden.
   public void settBredde(float bredde)
   {
     b = bredde * 28.4;
   }
   
   // En funksjon som setter høyden til siden. Parameteren er den nye høyden.
   public void settHoyde(float hoyde)
   {
     h = hoyde * 28.4;
   }
}