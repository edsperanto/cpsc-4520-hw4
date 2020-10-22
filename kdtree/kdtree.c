#include "kdtree.h"

#define LATITUDE 0
#define LONGITUDE 1
#define NEW_STRUCT(s) (s *)malloc(sizeof(s))
#define NEW_STRING(s) (char *)malloc(strlen(s)+1)
#define CPY_STRING(dst, src) dst = NEW_STRING(src); strcpy(dst, src)

int 
cmpLatitude(const void *a_ptr, const void *b_ptr) 
{
    airport a = *(airport *)a_ptr;
    airport b = *(airport *)b_ptr;
    return a.latitude < b.latitude ? -1 : a.latitude > b.latitude;
}

int 
cmpLongitude(const void *a_ptr, const void *b_ptr) 
{
    airport a = *(airport *)a_ptr;
    airport b = *(airport *)b_ptr;
    return a.longitude < b.longitude ? -1 : a.longitude > b.longitude;
}

kdTree * 
generateKdTree(airport *airports, int size) 
{
    kdTree *kd = NEW_STRUCT(kdTree);
    addKdNode(&(kd->root), airports, 0, size-1, LATITUDE);
    return kd;
}

void
addKdNode(kdNode **node, airport *airports, int start, int end, int dir)
{
    if (start <= end) {
        int size = end - start + 1;
        int median = start + floor(size/2);
        int nodeIsLeaf = start == end;
        qsort(airports+start, size, sizeof(airport), dir ? cmpLongitude : cmpLatitude);
        *node = genKdNode(airports, nodeIsLeaf ? median : -1, dir);
        addKdNode(&((*node)->left), airports, start, median-1, 1-dir);
        addKdNode(&((*node)->right), airports, median, nodeIsLeaf ? -1 : end, 1-dir);
    }
}

kdNode *
genKdNode(airport *airports, int median, int dir) 
{
    kdNode *newNode = NEW_STRUCT(kdNode);
    airport *airport = airports + median;
    newNode->pos = dir ? airport->longitude : airport->latitude;
    newNode->dir = dir;
    newNode->airport = median > -1 ? airport : NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
