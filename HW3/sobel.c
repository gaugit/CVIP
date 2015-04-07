#include <stdio.h>
#include <math.h>
#include "routine.h"

void App_Sobel(char *filename, int row, int col, float *filter_out)
{
 FILE *fps, *fpd;
 int i,j;
 unsigned char ori_data[row][col];
 unsigned char nordata[row][col];
 float vfout[row][col],hfout[row][col];
 int vfilter[9]={-1,0,1,
		 -2,0,2,
                 -1,0,1};
 int hfilter[9]={-1,-2,-1,
                  0,0,0,
                  1,2,1};

 fps = fopen(filename,"rb");
 if(fps==NULL)
 {
  printf("file error");
  return;
 }

 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   ori_data[i][j] = fgetc (fps);
  }
 }
 fclose(fps);
 
 App_mask(ori_data, row, col, vfilter, vfout);
 App_mask(ori_data, row, col, hfilter, hfout);
 
 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   //final[i][j]=vfout[i][j]+hfout[i][j];
    *filter_out++ = vfout[i][j]+hfout[i][j];
  }
 }
}
