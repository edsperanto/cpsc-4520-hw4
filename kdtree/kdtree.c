#include "kdtree.h"
#include "../airports.h"

int cmpLatitude (const void *a_ptr, const void *b_ptr) {
    airport a = *(airport *)a_ptr;
    airport b = *(airport *)b_ptr;
    if (a.latitude > b.latitude) {
        return 1;
    } else if (a.latitude < b.latitude) {
        return -1;
    } else {
        return 0;
    }
}

int cmpLongitude (const void *a_ptr, const void *b_ptr) {
    airport a = *(airport *)a_ptr;
    airport b = *(airport *)b_ptr;
    if (a.longitude > b.longitude) {
        return 1;
    } else if (a.longitude < b.longitude) {
        return -1;
    } else {
        return 0;
    }
}


