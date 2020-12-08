/*
    Implements a function for each part of the protocol,
    and a functino that writes messages, one that reads
    and parses messages, and a function that looks at 
    the command in a message and calls one of the proto-
    col functions
*/
#include "kidLogic.hpp"

const std::string stateName[]={
    "Kid is newbie",
    "Kid is marching",
    "Kid is seeking",
    "Kid is sitting",
    "Kid is quiting",
};

const char* commands[] = {
    "HELLO",
    "GETUP",
    "SIT",
    "WANT",
    "ACK",
    "NACK",
    "QUIT",
    "PRIZE"
};

KidLogic::KidLogic(const char* h, int port, string name) : 
SockBase(port), kidName(name) {
    strcpy(host, h);

}

// -----

void KidLogic::connect(const char* host, int port) {
    // Use domain name server to get IP address associated with server.
    struct hostent* remoteHost = gethostbyname(host);
    if (remoteHost == NULL) fatalp("Socket: unknown host: %s\n", host);

    memmove(&info.sin_addr, remoteHost->h_addr_list[0], remoteHost->h_length);

    info.sin_port = htons(port);

    // Info in client sockaddr struct is now ready to connect to server.
    cout << "Ready to connect socket " << fd << " to " << host << endl;
    int status = ::connect( fd, (sockaddr*)&info, sizeof info );
    if (status < 0) fatalp("Client: Connection to %s refused.", host);
    //refresh();
    cout << "Socket: connection established to " << host << ".\n";
}

// ------
void KidLogic::doCommand(){
    int status = fscanf( momIn, "%6s", command );
    if (status!=1) fatalp("Error reading command");
    cout << "State = "<< stateName[pcol]<< ", Command is: " <<command << endl ;
    try{
        if (strcmp( "GETUP", command) == 0) doGetup();
        else if (strcmp( "SIT", command) == 0) doSit();
        else if (strcmp( "NACK", command) == 0) doNack();
        else if (strcmp( "ACK", command) == 0) doAck();
        else if (strcmp( "QUIT", command) == 0) doQuit();
        else if (strcmp( "PRIZE", command) == 0) doPrize();
        else throw( "Protocol is mixed up." );
    }
    catch (string& s) {
        cout << s <<" ["<< command <<"]\n";
        exit(1); 
    }
}

// ----- run
void KidLogic::run() {
    // Use High-level I/O communication. 
    momIn = fdopen(fd, "r");
    momOut = fdopen(fd, "w");

    // Send name to server
    fprintf(momOut, "%s\n", kidName.c_str());
    fflush(momOut);
    // send(fd, momOut, sizeof(momOut), 0);

    cout << "[Sent<<] " << kidName << endl;
    // doCommand();
}

// ----- doGetup
void KidLogic::doGetup(){
    cout << "Kid do getup" << endl;
}

// ----- doSit
void KidLogic::doSit(){
    cout << "Kid do sit" << endl;
}

// ----- doAck
void KidLogic::doAck(){
    cout << "Kid do ack" << endl;
}

// ----- doQuit
void KidLogic::doQuit(){
    cout << "Kid do quit" << endl;
}

// ----- doPrize
void KidLogic::doPrize(){
    cout << "Kid do prize" << endl;
}

// ----- doNack
void KidLogic::doNack(){
    cout << "Kid do nack" << endl;
}