struct kdTree { 
    struct kdNode *root; 
};

struct kdNode {
    double *pos;
    int dir;
    struct airport *data;
    struct kdNode *left;
    struct kdNode *right;
};

struct airport {
    string code<>;
    string name<>;
    double latitude;
    double longitude;
    double distance;
};

struct placesArg {
    double latitude;
    double longitude;
};

struct airportsLLNode {
    struct airport *airport;
    struct airportsLLNode *next;
};

union airportsRet switch (int err) {
    case 0:
        airportsLLNode *airports;
    default:
        void; /* error occured, nothing returned */
};

program AIRPORTS_PROG {
    version AIRPORTS_VERS {
        airportsRet AIRPORTS_NEAR_COORD(placesArg) = 1;
    } = 1;
} = 0x38710268;
