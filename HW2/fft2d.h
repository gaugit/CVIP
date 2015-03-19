#ifdef FFT2D_H
#undef FFT2D_H

void Center_sp(float *cdata, float *data int row, int col);
void norm_spec(float *data, float *mag, int row, int col);
void fft2d(float *data, int row, int col, int sign);

#endif
