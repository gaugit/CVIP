#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "fft2d.h"

#define CUTOFF 40.0
#define ORDER  80.0

void main(void)
{
 FILE *fps, *fpd;
 unsigned char pixel;
 float data_c[256][256],fft[256][512],spec[256][256],data[256][256],hu[256][256],Gu[256][512];
 char filename[20],cmd[20];
 int i,j,fri=0,x=256,y=256;
 
 /*
 printf("Enter the File to be processed:\n");
 scanf("%s",&filename);
 printf("Enter X:\n");
 scanf("%d",&x);
 printf("Enter Y:\n");
 scanf("%d",&y);
 */

 sprintf(filename,"%s","images/mri");
 fps = fopen(filename,"rb");
 if(fps==NULL)
 {
  printf("file error");
  return;
 }
 
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   data[i][j] = fgetc (fps);
  }
 }
 
 fclose(fps);
  
 //centering
 Center_sp(data_c, data, x, y);

 //adding zero
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   fft[i][fri] = data_c[i][j];
   fri++;
   fft[i][fri] = 0.0;
   fri++;
  }
  fri = 0;
 }

 fft2d(fft,x,y,1);

 //Sep spectrum
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   spec[i][j] = sqrt(pow(fft[i][j*2],2.0) + pow(fft[i][(j*2)+1],2.0));
  }
 }

 norm_spec(data, spec, x, y);

 fpd = fopen("part1","wb");
 for(i=0;i<x;i++)
  {
   for(j=0;j<y;j++)
   {
    pixel = data[i][j];
    fputc ( pixel , fpd );
   }
  }
 fclose(fpd);

 //creating filter
 for(i=0;i<x;i++)
  {
   for(j=0;j<y;j++)
   {
    //LPF
    hu[i][j] = 1/(1+pow((sqrt(pow((i-(x/2)),2.0) + pow((j-(y/2)),2.0))/CUTOFF),2*ORDER));
    //HPF
    //hu[i][j] = 1/(1+pow(10/(sqrt(pow((i-(x/2)),2.0) + pow((j-(y/2)),2.0))),4.0));
   }
  }

 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   Gu[i][j*2]=fft[i][j*2] * hu[i][j];
   Gu[i][(j*2)+1]=fft[i][(j*2)+1] * hu[i][j];
  }
 }
 
 //reverse fourier
 fft2d(Gu,x,y,-1);

 //Sep spectrum
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   spec[i][j] = sqrt(pow(Gu[i][j*2],2.0) + pow(Gu[i][(j*2)+1],2.0));
  }
 }

 norm_spec(data, spec, x, y);

 fpd = fopen("part2","wb");
 for(i=0;i<x;i++)
 {
  for(j=0;j<y;j++)
  {
   pixel = data[i][j];
   fputc ( pixel , fpd );
  }
 }
 fclose(fpd);

 sprintf(cmd,"(echo P5; echo %d %d; echo 127; cat part1)|xv -&",x,y);
 system(cmd);
 printf("The output file is generated by name 'part1'\n");

 sprintf(cmd,"(echo P5; echo %d %d; echo 255; cat part2)|xv -&",x,y);
 system(cmd);
 printf("The output file is generated by name 'part2'\n");
}
