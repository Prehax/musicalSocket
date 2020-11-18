# musicalSocket

----------
    2020/11/17:

    after make compile, mom is server, kid is client, start.sh is a shell script to launch several clients.

    Now kids can connects to Mom, but Kids should send their names to Mom, I don't know how to send with high-level IO, the method mentioned in the P6, Fischer said use fflush() but it looks doesn't work, maybe my method is not correct.

    server usage: mom nKids to start server
    example: mom 4

    client usage: ./start.sh hostname
    example: ./start.sh localhost

    Files:
    sockBase.hpp sockBase.cpp: Just like the demo program, they are the basic socket components shared by momLogic and kidLogic.

    mom.cpp: server main
    kid.cpp: client main

    protocol.hpp: the common variables or constant stores here

    momLogic.hpp, momLogic.cpp, kidLogic.hpp, kidLogic.cpp:
    The class of server and client

    kids.txt: stores kids' names for shell script to run



