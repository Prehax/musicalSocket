/*
    the main program for the mom module, make all connections
    and then instantiates the MomLogic class, and call its
    run function
*/
#include "kidLogic.hpp"
#include "momLogic.hpp"

int main(int argc, char* argv[]) {
    //banner();
    // Check the command parameters
    if (argc<2) {
        printf("Error: Not enough arguments!\n\nUsage: mom kidNumber\nExample: mom 4\n");
        bye();
        return -1;
    }
    int nKids = atoi(argv[1]);
    printf("There are %d kids joining the game...\n", nKids);

    // When all kids came, close the welcome socket:
    // close(welcomeSock);

    MomLogic momLogic(nKids);
    momLogic.run();

    //bye();
    return 0;
}