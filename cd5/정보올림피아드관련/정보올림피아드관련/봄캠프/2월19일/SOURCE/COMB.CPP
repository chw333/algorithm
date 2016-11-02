#include <math.h>
#include <fstream.h>

int S, Loop1, Loop2, N, k, Sw, Tot;
int Prime[10001], Num[10001];

main()
{
 ifstream InFile("Comb.Inp");
 InFile >> k >> N;
 for (Loop1 = 2; Loop1 <= N - 1; Loop1++)
 {
  Sw = 0;
  for (Loop2 = 2; Loop2 <= sqrt(Loop1); Loop2++)
  {
   if (Loop1 % Loop2 == 0) { Sw = 1; break; }
  }
  if (Sw == 0) { Tot++; Prime[Tot] = Loop1; }
 }
 for (Loop1 = 1; Loop1 <= Tot; Loop1++)
 {
  for (Loop2 = 1; Loop2 <= (N - 1) / Prime[Loop1]; Loop2++)
  {
   Num[Loop1] = Num[Loop1] + (N - 1) / int(pow(Prime[Loop1], Loop2));
  }
 }
 for (Loop1 = 1; Loop1 <= Tot; Loop1++)
 {
  for (Loop2 = 1; Loop2 <= ((N - 1) - (N - k)) / Prime[Loop1]; Loop2++)
  {
   Num[Loop1] = Num[Loop1] - ((N - 1) - (N - k)) / int(pow(Prime[Loop1], Loop2));
  }
 }
 for (Loop1 = 1; Loop1 <= Tot; Loop1++)
 {
  for (Loop2 = 1; Loop2 <= (N - k) / Prime[Loop1]; Loop2++)
  {
   Num[Loop1] = Num[Loop1] - (N - k) / int(pow(Prime[Loop1], Loop2));
  }
 }
 S = 1;
 for (Loop1 = 1; Loop1 <= Tot; Loop1++)
 {
  for (Loop2 = 1; Loop2 <= Num[Loop1]; Loop2++)
  {
   S = S * Prime[Loop1];
   if (S > 9)
   {
    do
    {
     Sw = 0;
     if (S % 10 == 0) { S = S / 10; Sw = 1; }
    }while(Sw == 1);
    S = S % 10;
   }
  }
 }
 ofstream OutFile("Comb.Out");
 OutFile << S;
}
