
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "routine.h"


void makecake(void)
{
 FILE *fpd;
 unsigned char cake[256][256];
 float noiseval, ncake[256][256],noiselev;
 int i,j;

 printf("Enter the Noise Level for Noisy Cake:\n");
 scanf("%f",&noiselev);

 for(i=0;i<256;i++)
 {
  for(j=0;j<256;j++)
  {
   if(sqrt(pow(i-127,2)+pow(j-127,2))<20)
    cake[i][j] = 150;
   else if(sqrt(pow(i-127,2)+pow(j-127,2))<40)
    cake[i][j] = 100;
   else if(sqrt(pow(i-127,2)+pow(j-127,2))<80)
    cake[i][j] = 50;
   else
    cake[i][j] = 0;
  }
 }

 fpd = fopen("edge_image","wb");
 for(i=0;i<(256);i++)
 {
  for(j=0;j<(256);j++)
  {
   fputc ( cake[i][j] , fpd );
  }
 }
 fclose(fpd);

for(i=0;i<256;i++)
 {
  for(j=0;j<256;j++)
  {
   noiseval = (((2*(float)rand())/RAND_MAX)-1) * noiselev;
   ncake[i][j]=  cake[i][j] + noiseval;
  }
 }

normalise(cake, ncake, 256, 256); //normalizing the image


 fpd = fopen("noisy_egde_image","wb");
 for(i=0;i<(256);i++)
 {
  for(j=0;j<(256);j++)
  {
   fputc ( cake[i][j] , fpd );
  }
 }
 fclose(fpd); 

 system("(echo P5; echo 256 256; echo 255; cat edge_image)|xv -&");
 system("(echo P5; echo 256 256; echo 255; cat noisy_egde_image)|xv -&");
}
