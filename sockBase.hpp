/*
    Basic socket sockaddr_in info that is shared by mom and kid
*/
#pragma once
#include "protocol.hpp"


class SockBase {
protected:
    int fd = -1;    // File desctiptor
    int port;
    sockaddr_in info={0};
    char host[256]; // name of local host

public:
    // SockType() = default;
    SockBase(int p=5005);
    int getFd() const { return fd; }
    int getPort() const { return port; }
    ostream& printInfo(ostream& out) const;  // For printing the info of socket
};

inline ostream& operator <<(ostream& out, const SockBase& st) {
    return st.printInfo(out);
}