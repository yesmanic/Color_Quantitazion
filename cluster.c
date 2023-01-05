#include "quantization.h"
#include "cluster.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

int* generateRandomValues(ImageInfo *info);
Cluster *initializeClusters(unsigned char *data, ImageInfo *info, Pixel **head);
void insertItem(Cluster *cluster, Pixel *pixel);
void removeItem(Cluster *cluster, Pixel *pixel);
void calculateCentroid(Cluster *clusters, int k, int channels);

Cluster* lloydsAlgorithm(unsigned char *data, ImageInfo *info, Pixel **head) {
   Cluster *clusters;
   int i, min, minIndex, diss, limit;
   Pixel *pix;
   bool isChanged;

   clusters = initializeClusters(data, info, head);
   isChanged = true;

   limit = 0;
   while (isChanged && limit < info->maxInterations) {
      pix = *head;
      isChanged = false;
      limit++;

      while (pix) {
         min = INT_MAX;
         for (i = 0; i < info->k; i++) {
            diss = dissimilarity(pix, clusters[i].centroid, info->channels);
            if (diss < min) {
               min = diss;
               minIndex = i;
            }
         }

         if (pix->centroidIndex != minIndex) {
            removeItem(&(clusters[pix->centroidIndex]), pix);
            insertItem(&(clusters[minIndex]), pix);
            pix->centroidIndex = minIndex;
            isChanged = true;
         }
         pix = pix->successor;
      }

      if (isChanged) calculateCentroid(clusters, info->k, info->channels);
   }

   puts("Done!");
   printf("%d iterations were performed\n", limit);

   return clusters;
}

Cluster *initializeClusters(unsigned char *data, ImageInfo *info, Pixel **head) {
   int i, *randomNums;
   Cluster *clusters;
   unsigned char *pixel;
   Pixel *pix, *newPix;

   randomNums = generateRandomValues(info);
   clusters = (Cluster *)malloc(sizeof(Cluster) * info->k);

   for (i = 0; i < info->k; i++) {
      clusters[i].centroid = (unsigned char *)malloc(sizeof(unsigned char) * info->channels);
      clusters[i].head = NULL;
      pixel = data + randomNums[i];

      for (int j = 0; j < info->channels; j++) {
         clusters[i].centroid[j] = pixel[j];
      }
   }
   
   pix = NULL;
   for (i = 0; i < info->width * info->height; i++) {
      newPix = createPixel(&data[i * info->channels]);
      newPix->successor = NULL;
      newPix->centroidIndex = 0;
      insertItem(&(clusters[0]), newPix);
      if (pix) newPix->successor = pix;
      pix = newPix;
   }

   *head = pix;
   return clusters;
}

int* generateRandomValues(ImageInfo *info) {
   int *randomNums, size, i, randomNum;
   bool isDistinct;

   randomNums = (int *)malloc(sizeof(int) * info->k);
   srand((unsigned)time(NULL));
   
   size = 0;

   for (size = 0; size < info->k;) {
      randomNum = rand() % (info->width * info->height);
      randomNum = randomNum - (randomNum % info->channels);
      isDistinct = true;

      for (i = 0; i < size; i++)
         if (randomNums[i] == randomNum) {
            isDistinct = false;
            break;
         }

      if (isDistinct) randomNums[size++] = randomNum;
   }

   return randomNums;
}

void insertItem(Cluster *cluster, Pixel *pixel) {
   if (!cluster || !pixel) return;

   pixel->next = cluster->head;
   if (pixel->next)
      pixel->next->prev = pixel;

   pixel->prev = NULL;
   cluster->head = pixel;

   cluster->size++;
}

void removeItem(Cluster *cluster, Pixel *pixel) {
   if (!cluster || !pixel) return;

   if (pixel->next)
      pixel->next->prev = pixel->prev;
   
   if (pixel->prev)
      pixel->prev->next = pixel->next;

   if (pixel == cluster->head) {
      cluster->head = pixel->next;
   }

   cluster->size = cluster->size - 1;
}

void calculateCentroid(Cluster *clusters, int k, int channnels) {
   int i, j, sum;
   Pixel *pix, *aux;

   for (i = 0; i < k; i++) {
      pix = clusters[i].head;
      for (j = 0; j < channnels; j++) {
         sum = 0;
         aux = pix;
         while (aux) {
            sum += aux->colors[j];
            aux = aux->next;
         }

         if (clusters[i].size > 0)
            clusters[i].centroid[j] = sum / clusters[i].size;
      }
   }
}