#include <stdio.h>
#include <math.h>
#include "routine.h"

void main(void)
{
 FILE *fpd;
 char filename[20];
 int i,j,threshold;
 int row=256,col=256;
 float final[row][col];
 unsigned char nordata[row][col],pixel;


 printf("Enter the File to be processed:\n");
 scanf("%s",&filename);

 App_Sobel(filename, row, col, final);
 normalise(nordata, final, row, col);

 fpd = fopen("sobel","wb");
 for(i=0;i<(row);i++)
 {
  for(j=0;j<(col);j++)
  {
   pixel = nordata[i][j];
   fputc ( pixel , fpd );
  }
 }
 fclose(fpd);

 histogram(nordata, row, col);
 printf("Enter the threshold for Binarization:\n");
 scanf("%d",&threshold);
 Create_bin(nordata, row, col,threshold);
 system("(echo P5; echo 256 256; echo 255; cat sobel)|xv -&");
 system("(echo P5; echo 256 256; echo 255; cat binary)|xv -&");
}
