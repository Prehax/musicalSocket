/*
    Defines a class that contains chairs, counters, an array
    of Players, C-streams, buffers, and everything else need
    to communicate between one of the MomLogic functions and
    others.
*/
#pragma once
#include "sockBase.hpp"
#include <sys/poll.h>

struct Player {
    string name = "??";
    bool alive = false;
    FILE* kidIn;        // Stream for kid to send to Mom
    FILE* kidOut;       // Stream for mom to send to Kid
};

class MomLogic: protected SockBase {
private:
    int nKids;      // Number of kids
    struct Player* kids;    // The player array
    int nAlive;     // number of kids still in game
    int nChairs;
    char* chairs;
    int status;     // store return values from sys call
    int nCli;       // number of sockets connected
    pollfd* result;
    pollfd* welcomeFd;
    pollfd* workerFd;

    int doService(pollfd* pfd, int k);
    int doWelcome();
    // int doReject(); // When nCli reaches nKids
    void doPoll();
    int accept();

    void initRound();
    void stopTheMusic();
    void checkSockets();
    void handleChairRequest(int kidNum, int& nAvailable);
    bool areAllKidsReady();
public:
    MomLogic() = default;
    MomLogic(int n);
    ~MomLogic();
    void run();
};

