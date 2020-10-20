struct trie { 
    struct trieNode *root; 
};

struct trieNode {
    char letter;
    struct trieNode *next;
    struct trieNode *down;
    struct location *data;
};

struct location {
    string fullName<>;
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

union placesRet switch (int err) {
    case 0:
        placesLLNode *airports;
    default:
        void; /* error occured, nothing returned */
};

program PLACES_PROG {
    version PLACES_VERS {
        placesRet AIRPORTS_NEAR_CITY(clientArg) = 1;
    } = 1;
} = 0x34865249;
