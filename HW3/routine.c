#include <stdio.h>
#include <math.h>
#include "routine.h"

void normalise(unsigned char *data, float *mag, int row, int col)
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

void App_mask(unsigned char *data, int row, int col, int *filter, float *filter_out)
{
 int i,j;
 unsigned char output[row+2][col+2];
 float fout[row][col];


 for(i=0;i<(row+2);i++)
 {
  for(j=0;j<(col+2);j++)
  {
   output[i][j] = 0;
  }
 }

//padding 
 for(i=1;i<(row+1);i++)
 {
  for(j=1;j<(col+1);j++)
  {
   output[i][j] = *data;
   data++;
  }
 }

 for(i=1;i<row+1;i++)
 {
  for(j=1;j<col+1;j++)
  {
   fout[i-1][j-1]=abs((output[i-1][j-1]* filter[0])+(output[i-1][j]* filter[1])+(output[i-1][j+1]* filter[2])+
                        (output[i][j-1]* filter[3])+(output[i][j]* filter[4])+(output[i][j+1]* filter[5])+
                        (output[i+1][j-1]* filter[6])+(output[i+1][j]* filter[7])+(output[i+1][j+1]* filter[8]));
  }
 }
 for(i=0;i<(row);i++)
 {
  for(j=0;j<(col);j++)
  {
   *filter_out=fout[i][j];
   filter_out++;
  }
 }

}


void histogram(unsigned char *data, int row, int col)
{
 FILE *fps, *fpd;
 int i,j;
 int hist_g[256];
 unsigned char ori_data[row][col];

 for(i=0; i<255; i++)
  hist_g[i] = 0;

 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   ori_data[i][j]= *data++ ;
  }
 }

 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   (hist_g[ori_data[i][j]])++;
  }
 }
 fpd = fopen("histogram.xls","wb");
 for(i=0; i<256; i++)
 {
 fprintf(fpd,"%d\t%d\n",i,hist_g[i]);
 }
 fclose(fpd);
}


void Create_bin(unsigned char *data, int row, int col, unsigned char thold)
{
 int i,j;
 FILE *fpd;
 unsigned char ori_data[row][col];
 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   if((*data++)>thold)
   ori_data[i][j]=255;
   else
   ori_data[i][j]=0;
  }
 }
 
 fpd = fopen("binary","wb");
 for(i=0;i<row;i++)
 {
  for(j=0;j<col;j++)
  {
   fputc ( ori_data[i][j] , fpd );
  }
 }
 fclose(fpd);
}



void App_Gausian(unsigned char *data, int row, int col, float *filter, float *filter_out)
{
 int i,j;
 unsigned char output[row+2][col+2];
 float fout[row][col];


 for(i=0;i<(row+2);i++)
 {
  for(j=0;j<(col+2);j++)
  {
   output[i][j] = 0;
  }
 }

//padding 
 for(i=1;i<(row+1);i++)
 {
  for(j=1;j<(col+1);j++)
  {
   output[i][j] = *data;
   data++;
  }
 }

 for(i=1;i<row+1;i++)
 {
  for(j=1;j<col+1;j++)
  {
   fout[i-1][j-1]=((output[i-1][j-1]* filter[0])+(output[i-1][j]* filter[1])+(output[i-1][j+1]* filter[2])+
                        (output[i][j-1]* filter[3])+(output[i][j]* filter[4])+(output[i][j+1]* filter[5])+
                        (output[i+1][j-1]* filter[6])+(output[i+1][j]* filter[7])+(output[i+1][j+1]* filter[8]))/16;
  }
 }
 for(i=0;i<(row);i++)
 {
  for(j=0;j<(col);j++)
  {
   *filter_out=fout[i][j];
   filter_out++;
  }
 }

}



/*
filter_out[i-1][j-1]=abs((output[i-1][j-1]*-1)+(output[i-1][j]*0)+(output[i-1][j+1]*1)+
                        (output[i][j-1]*-2)+(output[i][j]*0)+(output[i][j+1]*2)+
                        (output[i+1][j-1]*-1)+(output[i+1][j]*0)+(output[i+1][j+1]*1)) + 
			abs((output[i-1][j-1]*-1)+(output[i-1][j]*-2)+(output[i-1][j+1]*-1)+
                        (output[i][j-1]*-0)+(output[i][j]*0)+(output[i][j+1]*0)+
                        (output[i+1][j-1]*1)+(output[i+1][j]*2)+(output[i+1][j+1]*1));
*/
