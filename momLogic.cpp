/*
    Implements the functions, instantiates KidLogic
    and calls its run function
*/
#include "momLogic.hpp"

MomLogic::MomLogic(int n): SockBase(PORT), nKids(n) {
    kids = new Player[n];
    chairs = new char[n-1];
    nCli = 0;
    result = new pollfd[nKids+1];
    welcomeFd = &result[0];
    workerFd = &result[1];

    // Setup the server, bind info to this fd
    if (::bind(fd, (struct sockaddr*)&info, sizeof(info)) != 0 ) {
        fatal("Can not bind!\n");
        close(fd);
        bye();
        exit(0);
    }

    // Reuse the port number
    // int trueVal = 1;
    // status = setsockopt(welcomeFd->fd, SOL_SOCKET, SO_REUSEADDR, &trueVal, sizeof(int));
    // if (status < 0) { fatal("Can't set reuse socket option"); }

    // Set it to listen mode
    if (::listen(fd, 10) != 0) {
        fatal("Can not listen!\n");
        close(fd);
        bye();
        exit(0);
    }
}

// ----- Run
void MomLogic::run() {
    printf("%d kids are coming~~\n", nKids);
    doPoll();
    while (nChairs > 1) {
        initRound();
    }
    for (int k = 0; k < nKids; ++k) {
        if(kids[k].alive) {
            fprintf(kids[k].kidOut, "%s\n", commands[cmdMsg::PRIZE]);
            fflush(kids[k].kidOut);
            close(workerFd[k].fd);
        }
    }
}

// ----- doPoll
void MomLogic::doPoll() {
    *welcomeFd = {fd, POLLIN, 0};
    bool allKidsReady = false;
    for (;;) {
        status = ::poll(result, 1+nCli, -1);
        if (status < 0) {
            fatal("Error in poll().\n");
        } else if (status == 0) {
            fatal("Poll timed out.\n");
        }
        // ::poll will change the value of revents
        if (welcomeFd->revents != 0) {
            // If number of Client < nKids, Still accept.
            // doWelcome is a combination of accept and send message
            // nCli will increase (by +1) in accept function
            if (nCli < nKids) { doWelcome(); }
            // else { doReject(); }
        }

        for (int k=0; k<nCli; k++) {
            //cout <<"Ready to scan workers.\n";
            if (workerFd[k].revents != 0) {
                //cout <<k <<"  " <<workerFd[k].revents <<endl;
                status = doService( &workerFd[k], k);
                if (status == -1){
                    fatalp("A child disconnected too early at port %i the game will now end.\n", getPort());
                }
            }
            // else go on to the next socket.
        }

        // If Client number < nKids, keep events still POLLIN
        // else if nCli = nKids, change events to 0
        welcomeFd->events = (nCli < nKids) ? POLLIN : 0;
        allKidsReady = areAllKidsReady();
        if (allKidsReady) break;
    }
}

// ---------doWelcome()
int MomLogic::doWelcome() {

    int newfd = accept();

    if (newfd == 0) {  // This signals an error in ::accept().
        cout <<"False alarm: connection attempt was rejected.\n";
        return 0;  // False alarm, nobody there, 0 new clients.
    }
    // We have a new caller -- send an ack.
    const char* greeting ="Hello, Kid! What's your name?\n";
    int bytes = write(newfd, greeting, strlen(greeting));
    if (bytes < 1) cout <<"Error while writing to socket\n";
    //printPeer(cout);
    return 1;
}

// --------accept wrap
int MomLogic::accept(){
    //cout << "Entering accept.\n";
    sockaddr_in newSock;
    unsigned sockLen = sizeof newSock;
    int newFd = ::accept(fd, (sockaddr*)&newSock, &sockLen);
    if (newFd < 0) {
        cout <<"False alarm: connection was rejected.\n";
        return 0;  // False alarm, nobody there, 0 new clients.
    }
    cout << "::accept successful. New fd is " <<newFd <<"\n";
    pollfd newCaller = {newFd, POLLIN, 0};
    // Put new socket into our polling list.
    Player kid = {"", true, fdopen(newFd, "r"), fdopen(newFd, "w")};
    kids[nCli] = kid;
    workerFd[nCli++] = newCaller;
    return newFd;
}

// -------doService
int MomLogic::doService(pollfd* pfd, int k) {
    cout << "Now start servicing " << pfd->fd << endl;
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);

    if (pfd->revents != 0) {
        // This means there is an event
        if (pfd->revents & POLLIN) {
            // This means the event is reading
            int byte = read(pfd->revents, buf, BUFSIZ);
            if (byte > 0) {
                buf[byte] = '\0';
                cout << "Hello " << buf << endl;
                kids[k].name = buf;
            }
        }
        else if (pfd->revents & POLLHUP) {
            return -1;
        }   
    }
    sleep(1);
    return 0;
}

// -------initRound
void MomLogic::initRound() {
    nChairs = nAlive - 1;
    for (int k = 0; k < nChairs; ++k){
        chairs[k] = (char)"1";
    }
    for (int k = 0; k < nAlive; ++k){
        fprintf(kids[k].kidOut, "%s %i\n", commands[cmdMsg::GETUP], nChairs);
        fflush(kids[k].kidOut);
    }
    stopTheMusic();
}

void MomLogic::stopTheMusic() {

}

void MomLogic::checkSockets() {

}

bool MomLogic::areAllKidsReady() {
    bool allKidsReady = true;
    for (int k = 0; k < nKids; ++k){
        if (kids[k].name == ""){
            allKidsReady = false;
        }
    }
    return allKidsReady;
}

MomLogic::~MomLogic(){
    delete [] chairs;
    delete [] kids;
    delete [] result;
}