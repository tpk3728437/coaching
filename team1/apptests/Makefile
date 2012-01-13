# Points to the root of Google Mock, relative to where this file is.
# Remember to tweak this if you move this file.
GMOCK_DIR = ../../gmock-1.6.0

# a copy of Google Test at a different location.
GTEST_DIR = $(GMOCK_DIR)/gtest

# Where to find user code.
USER_DIR = ..
TEST_DIR = .

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include -I$(GMOCK_DIR)/include -I.. -I/usr/local/include -I../engine

# flag to compile in 32-bit mode
#CFLAGS += -m32

# GCOV flags
#GCOV_CFLAGS = -fprofile-arcs -ftest-coverage

# Flags passed to the C++ compiler.
LIBS = -lOIS
CXXFLAGS += -g -Wall -Wextra $(GCOV_CFLAGS)

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = tests

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# All Google Mock headers. Note that all Google Test headers are
# included here too, as they are #included by Google Mock headers.
# Usually you shouldn't change this definition.
GMOCK_HEADERS = $(GMOCK_DIR)/include/gmock/*.h \
                $(GMOCK_DIR)/include/gmock/internal/*.h \
                $(GTEST_HEADERS)

# House-keeping build targets.
all : $(TESTS)

test: $(TESTS)
	./$(TESTS)

valgrind: $(TESTS)
	valgrind ./$(TESTS)

clean :
	rm -f $(TESTS) gmock.a gmock_main.a *.o *.gcda *.gcno *.gcov

distclean: clean

# Builds gmock.a and gmock_main.a.  These libraries contain both
# Google Mock and Google Test.  A test should link with either gmock.a
# or gmock_main.a, depending on whether it defines its own main()
# function.  It's fine if your test only uses features from Google
# Test (and not Google Mock).

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
GMOCK_SRCS_ = $(GMOCK_DIR)/src/*.cc $(GMOCK_HEADERS)

# For simplicity and to avoid depending on implementation details of
# Google Mock and Google Test, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Mock and
# Google Test compile fast and for ordinary users their source rarely
# changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GTEST_DIR)/src/gtest-all.cc

gmock-all.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GMOCK_DIR)/src/gmock-all.cc

gmock_main.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GMOCK_DIR)/src/gmock_main.cc

gmock.a : gmock-all.o gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gmock_main.a : gmock-all.o gtest-all.o gmock_main.o
	$(AR) $(ARFLAGS) $@ $^


# Builds a sample test.
inputhandler_tests.o : $(TEST_DIR)/inputhandler_tests.cpp $(GMOCK_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -c $(TEST_DIR)/inputhandler_tests.cpp

inputhandler.o: $(USER_DIR)/inputhandler.cpp $(GMOCK_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -c $(USER_DIR)/inputhandler.cpp

doubleuplogic_tests.o : $(TEST_DIR)/doubleuplogic_tests.cpp $(GMOCK_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -c $(TEST_DIR)/doubleuplogic_tests.cpp

doubleuplogic.o: $(USER_DIR)/doubleuplogic.cpp $(GMOCK_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -c $(USER_DIR)/doubleuplogic.cpp

$(TESTS) : gmock_main.a inputhandler_tests.o inputhandler.o doubleuplogic_tests.o doubleuplogic.o
	${CXX} $^ $(LIBS) -pthread -o $@
