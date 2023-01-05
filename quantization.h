typedef struct imageInfo ImageInfo;

struct imageInfo {
    int k;
    int width;
    int height;
    int channels;
    int maxInterations;
};

void quantize(char *filename, int k, int maxIterations);