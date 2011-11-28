CXX      = g++
CXXFLAGS += -g -Wall -Wextra -std=c++0x
INCPATH  = -I.
LINK     = g++
LIBS     = -pthread 

####### Files

SOURCES = main.cpp \
	  calculator.cpp 

TARGET = test1

####### Build rules

all : $(TARGET)

clean :
	rm -f $(TARGET) *.o

####### Compile

main.o: main.cpp calculator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

calculator.o: calculator.cpp calculator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calculator.o calculator.cpp

test1 : main.o calculator.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LIBS)-pthread $^ -o $@

