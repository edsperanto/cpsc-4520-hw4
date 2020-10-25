#include <stdlib.h>
#include <float.h>

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
    addKdNode(&(kd->root), NULL, airports, 0, size-1, LATITUDE);
    return kd;
}

void
addKdNode(kdNode **node, kdNode *parent, airport *airports, int start, int end, int dir)
{
    if (start <= end) {
        int size = end - start + 1;
        int median = start + floor(size/2);
        qsort(airports+start, size, sizeof(airport), dir ? cmpLongitude : cmpLatitude);
        *node = genKdNode(airports, parent, median, dir);
        addKdNode(&((*node)->left), *node, airports, start, median-1, 1-dir);
        addKdNode(&((*node)->right), *node, airports, median+1, end, 1-dir);
    }
}

kdNode *
genKdNode(airport *airports, kdNode *parent, int median, int dir) 
{
    kdNode *newNode = NEW_STRUCT(kdNode);
    airport *airport = airports + median;
    newNode->x = airport->longitude;
    newNode->y = airport->latitude;
    newNode->dir = dir;
    newNode->airport = airport;
    newNode->parent = parent;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct kdNode *
nearestNeighbor(struct kdNode *node, double x, double y) 
{
    struct kdNode *approx = searchApprox(node, x, y),
                  *nearest;
    searchAround(approx, &nearest, x, y, DBL_MAX);
    return nearest;
}

struct kdNode *
searchApprox(struct kdNode *node, double x, double y) 
{
    if (node->dir == LATITUDE) {
        if (node->left != NULL && y < node->y) {
            return searchApprox(node->left, x, y);
        } else if (node->right != NULL && y >= node->y) {
            return searchApprox(node->right, x, y);
        }
    }
    if (node->dir == LONGITUDE) {
        if (node->left != NULL && x < node->x) {
            return searchApprox(node->left, x, y);
        } else if (node->right != NULL && x >= node->x) {
            return searchApprox(node->right, x, y);
        }
    }
    return node;
}

void 
searchAround(struct kdNode *node, struct kdNode **best, double x, double y, double dist) 
{
    double curr_min = node->dir == LATITUDE ? fabs(node->y - y) : fabs(node->x - x);
    double parent_min = DBL_MAX;
    double left_min = DBL_MAX;
    double right_min = DBL_MAX;
    if (node->parent != NULL) {
        parent_min = node->parent->dir == LATITUDE ? fabs(node->parent->y - y) : fabs(node->parent->x - x);
    }
    if (node->left != NULL) {
        left_min = node->left->dir == LATITUDE ? fabs(node->left->y - y) : fabs(node->left->x - x);
    }
    if (node->right != NULL) {
        right_min = node->right->dir == LATITUDE ? fabs(node->right->y - y) : fabs(node->right->x - x);
    }
    
    double curr_dist = sqrt(pow(node->x - x, 2) + pow(node->y - y, 2));
    if (curr_dist < dist) {
        dist = curr_dist;
        *best = node;
    }
    
    if (node->left != NULL && left_min < curr_min) {
        searchAround(node->left, best, x, y, dist);
    }
    if (node->right != NULL && right_min < curr_min) {
        searchAround(node->right, best, x, y, dist);
    }
    if (node->parent != NULL && parent_min < curr_min) {
        searchAround(node->parent, best, x, y, dist);
    }
}
