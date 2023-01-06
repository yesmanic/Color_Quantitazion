#include "quantization.h"
#include "cluster.h"

#include <png.h>
#include <stdio.h>
#include <stdlib.h>

png_bytep readImage(char *filename, ImageInfo *imageInfo, png_bytepp *rp);
void generateImage(png_bytepp rowPointers, int width, int height);

void quantize(char *filename, int k, int maxIterations) {
   ImageInfo info;
   int i;
   png_bytep data;
   png_bytepp rowPointers; 
   Cluster *clusters;
   Pixel *pix, *head, *prox;

   info.k = k;
   info.maxInterations = maxIterations;

   data = readImage(filename, &info, &rowPointers);
   printf("Running...\n");
   clusters = lloydsAlgorithm(data, &info, &head);

   pix = head;
   while (pix) {
      for (i = 0; i < info.channels; i++) {
         pix->colors[i] = clusters[pix->centroidIndex].centroid[i];
      }
      pix = pix->successor;
   }

   generateImage(rowPointers, info.width, info.height);

   for (i = 0; i < info.k; i++) {
      free(clusters[i].centroid);
   }
   free(clusters);

   pix = head;
   while (pix) {
      prox = pix->successor;
      free(pix);
      pix = prox;
   }

   free(data);
}

png_bytep readImage(char *filename, ImageInfo *imageInfo, png_bytepp *rp) {
   png_FILE_p file;
   png_structp png;
   png_infop info;
   png_bytep data;
   png_bytepp rowPointers;
   int width, height, channels, i;

   file = fopen(filename, "rb");
   if (!file) return NULL;

   png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   if (!png) {
      fclose(file);
      return NULL;
   }

   info = png_create_info_struct(png);
   if (!info) {
      fclose(file);
      png_destroy_read_struct(&png, NULL, NULL);
      return NULL;
   }

   if (setjmp(png_jmpbuf(png))) {
      fclose(file);
      png_destroy_read_struct(&png, &info, NULL);
      return NULL;
   }

   png_init_io(png, file);
   png_read_info(png, info);

   width = png_get_image_width(png, info);
   height = png_get_image_height(png, info);
   channels = png_get_channels(png, info);

   imageInfo->width = width;
   imageInfo->height = height;
   imageInfo->channels = channels;

   data = (png_bytep)malloc(width * height * channels);
   rowPointers = (png_bytepp)malloc(height * sizeof(png_bytep));
   *rp = rowPointers;

   for (i = 0; i < height; i++)
      rowPointers[i] = data + (width * channels * i);


   png_read_image(png, rowPointers);
   png_destroy_read_struct(&png, &info, NULL);
   fclose(file);

   return data;
}

void generateImage(png_bytepp rowPointers, int width, int height) {
   png_structp png;
   png_infop info;
   png_FILE_p file;

   png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   if (!png) {
      return;
   }

   info = png_create_info_struct(png);
   if (!info) {
      png_destroy_write_struct(&png, NULL);
      return;
   }

   if (setjmp(png_jmpbuf(png))) {
      png_destroy_write_struct(&png, &info);
      return;
   }

   file = fopen("output.png", "wb");
   if (!file) {
      png_destroy_write_struct(&png, &info);
      return;
   }

   png_init_io(png, file);
   png_set_IHDR(png, info, width, height, 8, 
                  PNG_COLOR_TYPE_RGB_ALPHA, 
                  PNG_INTERLACE_NONE, 
                  PNG_COMPRESSION_TYPE_BASE, 
                  PNG_FILTER_TYPE_BASE);

   png_write_info(png, info);

   png_write_image(png, rowPointers);
   png_write_end(png, NULL);

   png_destroy_write_struct(&png, &info);
   fclose(file);

   free(rowPointers);
}