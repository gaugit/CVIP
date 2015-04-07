/*****r o u t i n e . h******
 Author: Gaurav Pitale */

#ifdef ROUTINE_H
#undef ROUTINE_H

void normalise(unsigned char *data, float *mag, int row, int col);
void App_mask(unsigned char *data, int row, int col, int *filter, float *filter_out);
void histogram(unsigned char *data, int row, int col);
void Create_bin(unsigned char *data, int row, int col, unsigned char thold);
void App_Gausian(unsigned char *data, int row, int col, float *filter, float *filter_out);

void App_Sobel(char *filename, int row, int col, float *filter_out);

void makecake(void);

int compare(char *filename);
#endif
