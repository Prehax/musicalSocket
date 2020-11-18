//                  -*- mode:c++; tab-width:4 -*-
// File: tools.cpp - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  the tools library.
//  Assorted utility routines for use in C++ programs.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "tools.hpp"

// --------------------------------------------------------------
// I/O Utilities-------------------------------------------------
// --------------------------------------------------------------
// Used to discard the remainder of the current input line
istream&
cleanline(istream& is) {
	return is.ignore(numeric_limits<streamsize>::max(), '\n');
}

// --------------------------------------------------------------
// Used to flush the cin buffer as in cin >> x >> flush;  or cin >> flush;
istream&
flush(istream& is) {
	return is.seekg(0, ios::end);
}

// --------------------------------------------------------------
// Print a neat header on the output.
void fbanner(ostream& fout) {
	char date[16], time[10];
	when(date, time);
	fout
			<< "\n---------------------------------------------------------------\n"
			<< "\t" << NAME << "\n\t" << CLASS << "\n\t" << date << "\t" << time
			<< endl
			<< "---------------------------------------------------------------\n";
}

// --------------------------------------------------------------
//  Print termination message.
void bye(void) {
	cout << "\n---------------------------------------------------------------"
			"\nNormal termination.\n";
}

// --------------------------------------------------------------
//  This is a handy function for messages of all sorts.
//  It formats and prints a message.
//  params: a format followed by a variable number of data items to print.
void say(const char* format, ...) {
	va_list vargs;                     // optional arguments

	va_start(vargs, format);
	vfprintf(stdout, format, vargs);
	fprintf(stdout, "\n");
}

// --------------------------------------------------------------
// Intended for use after a non-fatal error in a system call.
// In addition to the work done by say(), it prints the system error comment.
void sayp(const_cstring format, ...) {
	int err = errno;                           // capture the global error code.
	va_list vargs;                          // optional arguments

	va_start( vargs, format);
	vfprintf(stderr, format, vargs);
	fprintf(stderr, "\n         %s\n", strerror(err));
}

// --------------------------------------------------------------
// Delay progress of program for some number of seconds using a "busy wait".  Used to simulate useful work being done.
void delay(int seconds) {
	do {
		seconds = sleep(seconds);
	} while (seconds > 0);
}

// --------------------------------------------------------------
//  Error handling and error recovery.
//---------------------------------------------------------------
//---------------------------------------------------------------
// This function is for error messages.
// Takes a format argument followed by any number of data args.
// Formats and prints an error message, then exits.

void fatal(const char* format, ...) {
	va_list vargs;          // optional arguments
	cout << flush;
	va_start(vargs, format);
	vfprintf(stdout, format, vargs);
	fprintf(stderr, "\n");
	exit(1);
}

// --------------------------------------------------------------
// This function is for error messages following system calls.
// In addition to the work done by fatal(), it prints the system error comment.
void fatalp(const_cstring format, ...) {
	int err = errno;       // capture the global error code.
	va_list vargs;         // optional arguments
	va_start(vargs, format);
	vfprintf(stderr, format, vargs);
	fprintf(stderr, "\n        Error code %i: %s", err, strerror(err));
	exit(1);
}

// --------------------------------------------------------------
// Routines for handling the time and date.
// --------------------------------------------------------------
// --------------------------------------------------------------
// Store the current date and time in the arguments.
//      System's date format is: "Fri Jun  9 10:15:55 1995\n"
//      After extraction, date is: "Fri Jun  9 1995"    hour is: "10:15:55"

void when(cstring date, cstring hour) {
	time_t now;         // Stores integer encoding of date, time
	char* nowstring;    // Stores the date and time in a readable form.
	now = time(NULL);   // Get the date and time from the system.
	nowstring = ctime(&now);        // Convert to string form.
	strncpy(date, nowstring, 10);   // Extract day, month, date.
	strncpy(&date[10], &nowstring[19], 5); // Extract space, year.
	date[15] = '\0';                 // Add the string terminator.
	strncpy(hour, &nowstring[11], 8);// Copy hour:minutes:seconds.
	hour[8] = '\0';                  // Add the string terminator.
}

// --------------------------------------------------------------
// Store current date in the argument and return a pointer to it.
// date format is: "Fri Jun  9 1995"
cstring today(cstring date) {
	time_t now;          // Stores integer encoding of date, time
	cstring nowstring;   // Stores the date, time in readable form

	now = time(NULL);    // Get the date and time from the system.
	nowstring = ctime(&now);      // Convert to string form.
	strncpy(date, nowstring, 10); // Extract day, month, date.
	strncpy(&date[10], &nowstring[19], 5);  // Extract space, year
	date[15] = '\0';              // Add the string terminator.
	return (date);
}

// --------------------------------------------------------------
// Store the current time in hour and return a pointer to it.
//      hour format is: "10:15:55"
cstring oclock(cstring hour) {
	time_t now;          // Stores integer encoding of date, time
	cstring nowstring;   // Stores the date, time in readable form
	now = time(NULL);    // Get the date and time from the system
	nowstring = ctime(&now);            // Convert to string form
	strncpy(hour, &nowstring[11], 8);   // Hhour, minutes, seconds
	hour[8] = '\0';      // Add the string terminator.
	return (hour);
}
