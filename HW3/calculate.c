#include <stdio.h>
#include <math.h>
#include "routine.h"

int compare(char *filename)
{
 FILE *fps;
 unsigned char true_img[256][256],noisy[256][256],sobel[256][256];
 int i,j,k,op_thres;
 int x=256,y=256;
 int T=0,total=0;
 float acc[256];

 fps = fopen("filter","rb");
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   sobel[i][j] = fgetc (fps);
  }
 }
 fclose(fps);

 fps = fopen("binary_edge_image","rb");
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   true_img[i][j] = fgetc (fps);
  }
 }
 fclose(fps);

for(k=0;k<256;k++)
{

 Create_bin(sobel, x, y,k);

 fps = fopen("binary","rb");
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   noisy[i][j] = fgetc (fps);
  }
 }
 fclose(fps);

 for(i=0;i<256;i++)
 {
  for(j=0;j<256;j++)
  {
   if(sqrt(pow(i-127,2)+pow(j-127,2))<80)
   {
    //if(true_img[i][j] == 255)
    //{
     total++;
     if(true_img[i][j] == noisy[i][j])
      T++;
    //}
   }
  }
 }
 acc[k]=((float)T/(float)total)*100;
   //acc[k]=T;
T=0;
total=0;

}
 
 fps = fopen(filename,"wb");
 for(i=0; i<256; i++)
 {
 fprintf(fps,"%d\t%f\n",i,acc[i]);
 }
 fclose(fps);
 
 op_thres = 0;
 for(k=0;k<256;k++)
 {
  if(acc[op_thres] < acc[k])
    op_thres = k;
 }

 printf("Optimal Threshold = %d\n",op_thres);

 return op_thres;
}

/*
unsigned char cake[256][256];
for(i=0;i<N;i++)
    {
      for(j=0;j<M;j++)
    {
if(sqrt(pow(i-127,2)+pow(j-127,2))<25)
cake[i][j] = 150;
else if(sqrt(pow(i-127,2)+pow(j-127,2))<50)
cake[i][j] = 100;
else if(sqrt(pow(i-127,2)+pow(j-127,2))<100)
cake[i][j] = 50;
else
cake[i][j] = 0;
}
}
*/
