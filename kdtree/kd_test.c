#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"

void printKdTree(kdNode *node, int depth);

int main() {
    double latitude[] = { -3.73, 24.67, -78.9, -10.33, 1.02, 6.28, 45.81, -30.32, 83.28, 17.84 };
    double longitude[] = { 110.3, -84.92, 0, 69.2, -23.64, -162.03, 6.72, -57.13, 92.56, 158.51 };
    airport airports[10];

    // test airports
    printf("Before KD:\n");
    for (int i = 0; i < 10; i++) {
        airports[i].code = "SEA";
        airports[i].name = "Seattle Int'l";
        airports[i].latitude = latitude[i];
        airports[i].longitude = longitude[i];
        airports[i].distance = 0;
        printf("Airport %d:\n", i);
        printf("    Latitude: %f\n", airports[i].latitude);
        printf("    Longitude: %f\n", airports[i].longitude);
    }
    printf("\n");

    printf("Generating KD tree...\n");
    kdTree *kd = generateKdTree(airports, 10);
    printf("\n");

    printf("Printing KD tree...\n");
    printKdTree(kd->root, 1);
    printf("\n");

    printf("Finding nearest...\n");
    kdNode *nearest = NULL;
    double *nearest_dist = (double *)malloc(sizeof(double));
    nearestNeighbor(kd->root, 16, 158, &nearest, nearest_dist);
    printf("    Latitude: %f\n", nearest->airport->latitude);
    printf("    Longitude: %f\n", nearest->airport->longitude);
    
    return 0;
}
