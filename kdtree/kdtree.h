#ifndef __KDTREE_H_
#define __KDTREE_H_

struct kdTree {
    struct kdNode *root;
}
typedef struct kdTree kdTree;

struct kdNode {
    double *pos;
    int dir;
    struct airport *data;
    struct kdNode *left;
    struct kdNode *right;
}
typedef struct kdNode kdNode;

int cmpLatitude (const void *a_ptr, const void *b_ptr);
int cmpLongitude (const void *a_ptr, const void *b_ptr);

#endif
