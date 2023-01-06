#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "quantization.h"

int main(int argc, char **argv) {
   char *filename;
   int k, maxIterations;

   if (argc < 3) {
      puts("Error: not enough informations\n");
      puts("usage: ./quantize filename clusters [MAX_ITERATIONS]\n");
      puts("positional arguments:");
      puts("  filename\t\tthe name of the png file");
      puts("  clusters\t\tnumber of clusters\n");
      puts("optional arguments:");
      puts("  MAX_ITERATIONS\t\tmaximum number of maxIterations");
      return 0;
   }

   filename = argv[1];
   k = atoi(argv[2]);

   if (argc < 4) maxIterations = INT_MAX;
   else maxIterations = atoi(argv[3]);

   quantize(filename, k, maxIterations);
   return 0;
}
