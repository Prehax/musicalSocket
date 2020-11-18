/*
    Defines the name and state of the kid and 2 C-streams
*/
#pragma once
#include "sockBase.hpp"

class KidLogic: protected SockBase{
private:
    // For musical game
    FILE* momIn, * momOut;
    int nChairs;
    string kidName;
    StateT pcol = NEWBIE;
    char* command;

    // For socket
    // int momFd; is fd, inherited from Base
    char host[BUFSIZ];

    // Functions
    void doGetup();
    void doSit();
    void doAck();
    void doQuit();
    void doPrize();
    void doNack();

public:
    KidLogic(const char* host, int port, string name);
    ~KidLogic() = default;
    // For musical game
    void run();
    void doCommand();

    // For socket
    void connect(const char* host, int port);
    ostream& printInfo( ostream& out ){
        return SockBase::printInfo( out );
    }
    unsigned getFd() const { return SockBase::getFd(); }
};