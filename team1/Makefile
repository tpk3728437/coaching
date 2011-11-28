CXX      = g++
CXXFLAGS += -g -Wall -Wextra -std=c++0x
INCPATH  = -I. -I/usr/include/
LINK     = g++
LIBS     = -pthread -lgtest_main -lgtest

####### Files

SOURCES = test.cpp \
	  calculator.cpp 

TARGET = test1

####### Build rules

all : $(TARGET)

clean :
	rm -f $(TARGET) *.o

####### Compile

test.o: test.cpp calculator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o test.o test.cpp

calculator.o: calculator.cpp calculator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calculator.o calculator.cpp

test1 : test.o calculator.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) $^ -o $@

