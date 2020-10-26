/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "places.h"
#include <string.h>
#include <errno.h>

#define NEW_STRUCT(s) (s *)malloc(sizeof(s))
#define NEW_STRING(s) (char *)malloc(strlen(s)+1)
#define CPY_STRING(dst, src) dst = NEW_STRING(src); strcpy(dst, src)

struct cmdInput {
    char *host;
    clientArg *location;
};

typedef struct cmdInput cmdInput;

// function declarations for processing user input
cmdInput * parseCmdLineInput(int argc, char *argv[]);
void checkIfInputValid(int argc, char *argv[]);
cmdInput * populateRequest(char *argv[]);

// function declarations for processing RPC call
placesRet * findAirportsNearCity(CLIENT *clnt, clientArg *userInput);
CLIENT * connectToClient(char *host);
void checkIfResultIsNull(placesRet *result, CLIENT *clnt);
void disconnectFromClient(CLIENT *clnt, placesRet *result);

// client main function
int
main (int argc, char *argv[])
{
    // perform query
    cmdInput *request = parseCmdLineInput(argc, argv);
	CLIENT *clnt = connectToClient(request->host);
	placesRet *result = findAirportsNearCity(clnt, request->location);

    // print results
    if ((errno = result->err) == 0) {
        airportInfo *airports = (result->placesRet_u).results.airports;
        location location = (result->placesRet_u).results.location;
        printf("%s, %s: ", location.city, location.state);
        printf("%.6f, %.6f\n", location.latitude, location.longitude);
        for (int i = 0; i < 5; i++) {
            airportInfo ap = airports[i];
            char *comma = strchr(ap.name, ',');
            char *state = comma + 1;
            char *city = ap.name;
            *comma = '\0';
            printf("code=%s, ", ap.code);
            printf("name=%s, state=%s ", city, state);
            printf("distance:%.2f miles\n", ap.distance);

        }
    } else {
        perror("ERROR");
    }

    // end query
    disconnectFromClient(clnt, result);
    exit(0);
}

cmdInput *
parseCmdLineInput(int argc, char *argv[]) 
{
    checkIfInputValid(argc, argv);
    cmdInput *request = populateRequest(argv);
    return request;
}

void
checkIfInputValid(int argc, char *argv[]) 
{
	if (argc < 4) {
		printf ("usage: %s places_server_host city state\n", argv[0]);
		exit(1);
	}
}

cmdInput *
populateRequest(char *argv[]) 
{
    cmdInput *request = NEW_STRUCT(cmdInput);
    CPY_STRING(request->host, argv[1]);
    request->location = NEW_STRUCT(clientArg);
    CPY_STRING(request->location->city, argv[2]);
    CPY_STRING(request->location->state, argv[3]);
    return request;
}

placesRet *
findAirportsNearCity(CLIENT *clnt, clientArg *userInput)
{
	placesRet *result = airports_near_city_1(userInput, clnt);
    checkIfResultIsNull(result, clnt);
    return result;
}

CLIENT *
connectToClient(char *host) 
{
    #ifndef	DEBUG
	CLIENT *clnt = clnt_create(host, PLACES_PROG, PLACES_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		exit (1);
	}
    #endif	/* DEBUG */
}

void
checkIfResultIsNull(placesRet *result, CLIENT *clnt) 
{
	if (result == (placesRet *) NULL) {
		clnt_perror(clnt, "call failed");
	}
}

void
disconnectFromClient(CLIENT *clnt, placesRet *result) 
{
    #ifndef	DEBUG
    clnt_freeres(clnt, (xdrproc_t)xdr_placesRet, result);
	clnt_destroy(clnt);
    #endif	 /* DEBUG */
}
