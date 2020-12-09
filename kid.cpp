#include "kidLogic.hpp"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    banner();
    // check correct number of arguments
    if (argc != 3) {
        fatalp( "Usage: kid hostname Name\nExample: kid localhost Amy\n");
        exit(0);
    }
    const char* host = argv[1];
    // const char* kidName = argv[2];

    char buf[BUFSIZ];
    int nBytes;
    KidLogic kid( host, PORT, argv[2]);
    kid.connect(host, PORT);
    cout <<"Joining musical game on " ;
    kid.printInfo( cout );

    // wait for server to acknowledge the connection. 
    nBytes = read( kid.getFd(), buf, BUFSIZ );
    // connection message
    if (nBytes >= 0) { cout << "[Get>>>] "<< buf; } 
    else {
        cout << argv[2] << ": I'm late, I'll leave" << endl;
        kid.~KidLogic();
        bye(); return 0;
    }
    kid.run();
    // all the socket connections are closed automatically 
    bye();
    return 0;
}

// Amy Bob Carol Dimen Eyad Frank Green Helen Iestyn Jack Kazuo 
// Lucan Mike Nikka Oskar Perth Quint Rebacca Saint Taylor Umber Vanessa Wendy Xu Yvonne Zachary  