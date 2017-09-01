/*
  En klasse som brukes til å ta vare på hver kant/side sin lengde og bredde.
  v = vidde eller bredde
  h = høyde
  Ikke rediger denne fila.
  Greia med å gange verdiene med 28,4 er basert på tankegangen i funksjonen lagA4
  som brukes for å lage 2-dimensjonale utbrettede figurer.
*/
class Side
{
   private float v, h, d;
   Side(float vidde, float hoyde)
   {
     v = vidde;// * 28.4;
     h = hoyde;// * 28.4;
   }
   
   // En funksjon som henter bredden/vidden til siden
   public float hentVidde()
   {
     return v;
   }
   
   //En funksjon som henter høyden til siden
   public float hentHoyde()
   {
     return h;
   }
   
   // En funksjon som setter vidden (eller hva du vil kalle det for) til siden. Parameteren er den nye vidden.
   public void settVidde(float vidde)
   {
     v = vidde * 28.4;
   }
   
   // En funksjon som setter høyden til siden. Parameteren er den nye høyden.
   public void settHoyde(float hoyde)
   {
     h = hoyde * 28.4;
   }
}