#include "sockBase.hpp"

SockBase::SockBase(int p): port(p) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        fatal("Socket: Can't create socket");
    }
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port = htons(port);
    gethostname(host, 256);

}

// --------- printInfo
ostream& SockBase::printInfo(ostream& out) const {
    out << "{\n\tsin_addr.saddr = " << inet_ntoa(info.sin_addr)
    << "\n\tsin_port = " <<  ntohs(info.sin_port) << "\n}\n";

    return out;
}