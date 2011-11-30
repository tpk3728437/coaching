CXX      = g++
CXXFLAGS += -g -Wall -Wextra -std=c++0x
INCPATH  = -I. -I/usr/include/
LINK     = g++
LIBS     = -pthread -lgtest_main -lgtest

####### Files

TARGET = test1

####### Build rules

all : $(TARGET)

clean :
	rm -f $(TARGET) *.o

####### Compile

test.o: test.cpp HeadsOrTailsGame.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o test.o test.cpp

headsortailsgame.o: HeadsOrTailsGame.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o headsortailsgame.o HeadsOrTailsGame.cpp

test1 : test.o headsortailsgame.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) $^ -o $@

