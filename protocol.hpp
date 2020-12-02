/*
    The port number and list of messages used in the protocol
*/
#pragma once
#include "tools.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

const int PORT = 5005;

enum cmdMsg {HELLO, GETUP, SIT, WANT, ACK, NACK, QUIT, PRIZE};
enum StateT {NEWBIE, MARCHING, SEEKING, SITTING, QUITING };

const std::string stateName[]={
    "Kid is newbie",
    "Kid is marching",
    "Kid is seeking",
    "Kid is sitting",
    "Kid is quiting",
};

const char* commands[] = {
    "HELLO ",
    "GETUP ",
    "SIT",
    "WANT ",
    "ACK",
    "NACK ",
    "QUIT",
    "PRIZE"
};