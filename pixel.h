typedef struct pixel Pixel;

struct pixel {
    int centroidIndex;
    unsigned char *colors;
    Pixel *next;
    Pixel *successor;
    Pixel *prev;
};

int dissimilarity(Pixel *pixel, unsigned char *centroid, int channels);
Pixel *createPixel(unsigned char *colors);