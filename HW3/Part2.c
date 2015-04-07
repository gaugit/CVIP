#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "routine.h"

void main(void)
{
 FILE *fpd;
 int i,j,threshold;
 int row=256,col=256;
 float final[row][col];
 unsigned char nordata[row][col],ori_data[row][col],pixel;
 int gfilter[9]={1,2,1,
                 2,4,2,
                 1,2,1};
 float vfout[row][col];

 makecake();
 App_Sobel("edge_image", row, col, final);
 normalise(nordata, final, row, col);
 Create_bin(nordata, row, col,2);
 rename("binary","binary_edge_image");

 system("(echo P5; echo 256 256; echo 255; cat binary_edge_image)|xv -&");

 printf("binary_edge_image\n");
 scanf("%d",pixel);

 App_Sobel("noisy_egde_image", row, col, final);
 //App_Sobel("GApp", row, col, final);
 normalise(nordata, final, row, col);

 fpd = fopen("filter","wb");
 for(i=0;i<(row);i++)
 {
  for(j=0;j<(col);j++)
  {
   pixel = nordata[i][j];
   fputc ( pixel , fpd );
  }
 }
 fclose(fpd);
 system("(echo P5; echo 256 256; echo 255; cat filter)|xv -&");
 printf("Sobel_noisy\n");
 scanf("%d",pixel);
 threshold=compare("acc.xls");
 
 Create_bin(nordata, row, col,threshold);
 system("(echo P5; echo 256 256; echo 255; cat binary)|xv -&");
 printf("opt_binary\n");
 scanf("%d",pixel);
/*******************************************************************/
 fpd = fopen("noisy_egde_image","rb");
 if(fpd==NULL)
 {
  printf("file error");
  return;
 }

for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   ori_data[i][j] = fgetc (fpd);
  }
 }
 fclose(fpd);
 
 App_Gausian(ori_data, row, col, gfilter, vfout);
 

 normalise(nordata, vfout, row, col);

 fpd = fopen("Gaus_egde_image","wb");
 for(i=0;i<(row);i++)
 {
  for(j=0;j<(col);j++)
  {
   pixel = nordata[i][j];
   fputc ( pixel , fpd );
  }
 }
 fclose(fpd);
system("(echo P5; echo 256 256; echo 255; cat Gaus_egde_image)|xv -&");
 App_Sobel("Gaus_egde_image", row, col, final);
 //App_Sobel("GApp", row, col, final);
 normalise(nordata, final, row, col);

 fpd = fopen("filter","wb");
 for(i=0;i<(row);i++)
 {
  for(j=0;j<(col);j++)
  {
   pixel = nordata[i][j];
   fputc ( pixel , fpd );
  }
 }
 fclose(fpd);
 system("(echo P5; echo 256 256; echo 255; cat filter)|xv -&");
 threshold=compare("gacc.xls");
 
 Create_bin(nordata, row, col,threshold);
 system("(echo P5; echo 256 256; echo 255; cat binary)|xv -&");
}
