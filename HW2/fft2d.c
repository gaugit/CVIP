#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "testfft.h"

#include "fft2d.h"

void Center_sp(float *cdata, float *data, int row, int col)
{
 int i,j;
 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   *cdata = *data * pow(-1,(i+j));
    data++;
    cdata++;
  }
 }
 return;
}


void norm_spec(float *data, float *mag, int row, int col)
{
 float min, max, *omag;
 int i,j;
 omag = mag;
 min = *mag;
 max = *mag;
 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   if(min > *omag)
     min = *omag;
   
   if(max < *omag)
     max = *omag;
   
   omag++;
  }
 }

 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   *data = ((*mag - min)/(max-min))*255;
    data++;
    mag++;
  }
 }

}

void fft2d(float *data, int row, int col, int sign)
{
 int fri=0,i,j;
 float *frow,*fcol,*odata;
 float fdata[1024][1024];
 frow =(float *) calloc (2*col, sizeof (float));
 fcol =(float *) calloc (2*row, sizeof (float));
 odata = data;

 for(i=0;i<row;i++)
 {
  for(j=0;j<col*2;j++)
  {
   fdata[i][j] = *odata;
   odata++;
  }
 }
  
 //1st time FFT
 for(i=0;i<row;i++)
 {
  for(j=0;j<col*2;j++)
  {
   frow[j] = fdata[i][j];
  }
  four1(frow-1, col, sign);
  for(j=0;j<col*2;j++)
  {
   fdata[i][j] = frow[j];
  }
 }

 //2nd time FFT
 for(j=0;j<col;j++)
 {
  fri = 0;
  for(i=0;i<row;i++)
  {
   fcol[fri] = fdata[i][j*2];
   fri++;
   fcol[fri] = fdata[i][(j*2)+1];
   fri++;
  }
  four1(fcol-1, row, sign);
  fri = 0;
  for(i=0;i<row;i++)
  {
   fdata[i][j*2] = fcol[fri];
   fri++;
   fdata[i][(j*2)+1] = fcol[fri];
   fri++;
  }
 }

 for(i=0;i<row;i++)
 {
  for(j=0;j<col*2;j++)
  {
   *data++ = fdata[i][j];
  }
 }
}
