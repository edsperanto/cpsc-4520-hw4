struct location {
    string city<>;
    string state<>;
    double latitude;
    double longitude;
};

struct clientArg {
    string city<>;
    string state<>;
};

struct airportInfo {
    string code<>;
    string name<>;
    double latitude;
    double longitude;
    double distance;
};

struct placesLLNode {
    struct airportInfo *airport;
    struct placesLLNode *next;
};

struct placesResults {
    struct location location;
    struct placesLLNode *airports;
};

union placesRet switch (int err) {
    case 0:
        placesResults results;
    default:
        void; /* error occured, nothing returned */
};

program PLACES_PROG {
    version PLACES_VERS {
        placesRet AIRPORTS_NEAR_CITY(clientArg) = 1;
    } = 1;
} = 0x34865249;
