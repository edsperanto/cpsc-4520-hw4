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
    double x;
    double y;
    int dir;
    struct airport *airport;
    struct kdNode *parent;
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
void addKdNode(kdNode **node, kdNode *parent, airport *airports, int start, int end, int dir);
kdNode * genKdNode(airport *airports, kdNode *parent, int median, int dir);
void searchAround(struct kdNode *node, struct kdNode **best, double x, double y, double dist);
struct kdNode *searchApprox(struct kdNode *node, double x, double y);
struct kdNode *nearestNeighbor(struct kdNode *node, double x, double y);

#endif
