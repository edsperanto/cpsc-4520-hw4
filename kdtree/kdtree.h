#ifndef __KDTREE_H_
#define __KDTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../airports.h"

struct kdTree {
    struct kdNode *root;
};
typedef struct kdTree kdTree;

struct kdNode {
    double pos;
    int dir;
    struct airport *airport;
    struct kdNode *left;
    struct kdNode *right;
};
typedef struct kdNode kdNode;

struct kdParams {
    int start;
    int end;
};
typedef struct kdParams kdParams;

int cmpLatitude (const void *a_ptr, const void *b_ptr);
int cmpLongitude (const void *a_ptr, const void *b_ptr);

kdTree * generateKdTree(airport *airports, int size);
void addKdNode(kdNode **node, airport *airports, int start, int end, int dir);
kdNode * genKdNode(airport *airports, int median, int dir);

#endif
