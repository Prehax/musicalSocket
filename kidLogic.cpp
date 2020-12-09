/*
    Implements a function for each part of the protocol,
    and a functino that writes messages, one that reads
    and parses messages, and a function that looks at 
    the command in a message and calls one of the proto-
    col functions
*/
#include "kidLogic.hpp"

const string stateName[]={
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
    char* messageCStr = nullptr;
    int status = fscanf( momIn, "%s", messageCStr);
    if (status!=1) return;
    string message = messageCStr;
    string::size_type spacePos = message.find(" ");
    command = message.substr(0, spacePos);
    cout << "State = "<< stateName[pcol]<< ", Command is: " <<command << endl ;
    try{
        if (command == commands[cmdMsg::GETUP]){
            string numChairs = message.substr(spacePos + 1, string::npos);
            nChairs = stoi(numChairs);
            doGetup();
        } 
        else if (command == commands[cmdMsg::SIT]) doSit();
        else if (command == commands[cmdMsg::NACK]){
            string availableChairs = message.substr(spacePos + 1, string::npos);
            doNack(availableChairs);
        } 
        else if (command == commands[cmdMsg::ACK]) doAck();
        else if (command == commands[cmdMsg::QUIT]) doQuit();
        else if (command == commands[cmdMsg::PRIZE]) doPrize();
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

    while (pcol != StateT::QUITING){
        doCommand();
    }
}

// ----- doGetup
void KidLogic::doGetup(){
    pcol = StateT::MARCHING;
    cout << "Time to get another round started" << endl;
}

// ----- doSit
void KidLogic::doSit(){
    pcol = StateT::SEEKING;
    cout << "Let's get a seat!" << endl;
    // Sleep for a random time
    usleep(rand()%30000);
    // Change this child's state to SEEKING
    pcol = SEEKING;
    // Get a random chair to try
    int wantSeat = rand()%nChairs;
    // Send request
    cout << "Trying seat: " << wantSeat << endl;
    fprintf(momOut, "WANT %d\n", wantSeat);
    fflush(momOut);
}

// ----- doAck
void KidLogic::doAck(){
    pcol = StateT::SITTING;
    cout << "Woo I got the seat." << endl;
}

// ----- doQuit
void KidLogic::doQuit(){
    close(fd);
    pcol = StateT::QUITING;
    cout << "I lost. I am now quitting :(" << endl;
}

// ----- doPrize
void KidLogic::doPrize(){
    close(fd);
    pcol = StateT::QUITING;
    cout << "I won :)" << endl;
}

// ----- doNack
void KidLogic::doNack(string availableChairs){
    cout << "Kid do nack" << endl;
}