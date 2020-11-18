//     -*- mode:c++; tab-width:4 -*-
// file: tools.hpp ----------------------------------------------------
// header file for the C++ tools library.
// modified September 2009

#pragma once

// ---------------------------------------------------------------
// Local definitions.
// Please enter your own name.
// ---------------------------------------------------------------
#define NAME    "Dylan Chariott & Longlong Xu"
#define CLASS   "CSCI 4547/6647"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

#include <cstdio>      // for NULL
#include <cstdlib>     // for malloc() and calloc()
#include <cstring>     // for time_t, time() and ctime()
#include <cmath>
#include <ctime>
#include <cctype>      // for isspace() and isdigit()
#include <cstdarg>     // for functions with variable # of args
#include <cerrno>
#include <unistd.h>

using namespace std;

typedef char* cstring;
typedef const char* const_cstring;
typedef FILE* cstream;

// ---------------------------------------------------------------
// Macros to make more convenient use of standard library functions.
// ---------------------------------------------------------------
#define DUMPp(p) "\n"<<hex<<"   " #p " @ "<<(unsigned)&p<<"   value = "<<(unsigned)p<<"   " #p " --> "<<dec<<*p
#define DUMPv(k) "\n"<<hex<<"   " #k " @ "<<(unsigned)&k<<"   value = "<<dec<<k

// ---------------------------------------------------------------
// Routine screen and process management.-------------------------
// ---------------------------------------------------------------
void     fbanner( ostream& fout );
#define  banner()  fbanner( cout )
void     bye( void );
void     say( const_cstring format, ... );
void     delay( int );

// ---------------------------------------------------------------
// I/O Extension. ------------------------------------------------
// ---------------------------------------------------------------
istream&  cleanline( istream& is ); // discards remainder of line
istream&  flush( istream& is );     // Used in cin >>x >>flush;

// ---------------------------------------------------------------
// Error handling. -----------------------------------------------
// ---------------------------------------------------------------
void    fatal( const_cstring format, ... );
void    fatalp( const_cstring format, ... );
void    sayp (const_cstring format, ...);

// ---------------------------------------------------------------
// Time and date. ------------------------------------------------
// ---------------------------------------------------------------
void     when( cstring date, cstring hour );
cstring  today( cstring date );
cstring  oclock( cstring hour );
