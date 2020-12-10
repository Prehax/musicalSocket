# macros----------------------------------------------------------
CXX = g++
CXXFLAGS = -O1 -Wall -std=c++17
OBJ-CLI = kidLogic.o tools.o kid.o sockBase.o
OBJ-SER = momLogic.o tools.o mom.o sockBase.o

# targets --------------------------------------------------------
all: mom kid
# client ---------------------------------------------------------
kid: $(OBJ-CLI)
	$(CXX) $(CXXFLAGS) -o kid $(OBJ-CLI)

# server ---------------------------------------------------------
mom: $(OBJ-SER)
	$(CXX) $(CXXFLAGS) -o mom $(OBJ-SER)

# cleanup --------------------------------------------------------
clean:
	rm -f mom kid $(OBJ-SER) $(OBJ-CLI) *.log

# dependencies ---------------------------------------------------

tools.o: tools.cpp tools.hpp
sockBase.o: tools.hpp sockBase.hpp
mom.o: mom.cpp momLogic.cpp momLogic.hpp sockBase.hpp sockBase.cpp protocol.hpp tools.hpp
kidLogic.o: kidLogic.cpp kidLogic.hpp sockBase.hpp sockBase.cpp protocol.hpp tools.hpp
momLogic.o: momLogic.cpp momLogic.hpp sockBase.hpp sockBase.cpp protocol.hpp tools.hpp
kid.o: kid.cpp kidLogic.cpp kidLogic.hpp sockBase.hpp sockBase.cpp protocol.hpp tools.hpp