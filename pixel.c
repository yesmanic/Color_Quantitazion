#include "pixel.h"

#include <math.h>
#include <stdlib.h>

int dissimilarity(Pixel *pixel, unsigned char *centroid, int channels) {
   int i, sum;
   
   sum = 0;
   for (i = 0; i < channels; i++) {
      sum += pow((pixel->colors[i] - centroid[i]), 2);
   }

   return sum;
}

Pixel *createPixel(unsigned char *colors) {
   Pixel *pix;

   pix = (Pixel *)malloc(sizeof(Pixel));
   pix->colors = colors;

   pix->next = NULL;
   pix->prev = NULL;

   return pix;
}