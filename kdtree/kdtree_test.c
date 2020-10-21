#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
#include "../airports.h"

int main() {
    double latitude[] = { -3.73, 24.67, -78.9, -10.33, 1.02, 6.28, 45.81, -30.32, 83.28, 17.84 };
    double longitude[] = { 110.3, -84.92, 0, 69.2, -23.64, -162.03, 6.72, -57.13, 92.56, 158.51 };
    airport airports[10];

    printf("Before qsort:\n");
    for (int i = 0; i < 10; i++) {
        airports[i].code = "SEA";
        airports[i].name = "Seattle Int'l";
        airports[i].latitude = latitude[i];
        airports[i].longitude = longitude[i];
        airports[i].distance = 0;
        printf("    %f\n", airports[i].latitude);
    }

    qsort(airports, 10, sizeof(airport), cmpLatitude);

    printf("After qsort:\n");
    for (int i = 0; i < 10; i++) {
        struct airport airport = airports[i];
        printf("    %f\n", airport.latitude);
    }
    
    return 0;
}
