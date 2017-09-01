// Egentlig ikke så mye nytt sammenlignet med språk som Java, C og C++, men dog...

int data[];
void setup()
{
  size(100,100);
  data = new int[5];
  data[0] = 19;
  data[1] = 40;
  data[2] = 27;
  data[3] = 93;
  data[4] = 1010;
  int i = 0;
  while(i<=data.length-1)
  {
    println(data[i]);
    i++;
  }
  println("Done.");
}

