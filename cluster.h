#include "pixel.h"

typedef struct cluster Cluster;

struct cluster {
    unsigned char *centroid;
    Pixel *head;
    int size;
};

Cluster* lloydsAlgorithm(unsigned char *data, ImageInfo *info, Pixel **head);