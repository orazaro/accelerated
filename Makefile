#$Id: Makefile,v 1.2 2012/02/08 16:56:33 oraz Exp $

CPP			= $(wildcard *.cpp)
PROGRAMS	= $(CPP:%.cpp=%) 
CFILES		= $(wildcard *.c)
PROGRAMC	= $(CFILES:%.c=%) 
LIBRARIES	= cppunit
DEPS		= cppunit_run.inc

CC          = gcc
CXX         = g++
CFLAGS      += -Wall -O3
CPPFLAGS    += -Wall -O2
LDFLAGS     = $(LIBRARIES:%=-l%)

.PHONY: all clean

all: $(PROGRAMS) $(PROGRAMC) 

%: %.cpp $(DEPS) 
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $< -o $@

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.a $(PROGRAMS) $(PROGRAMC)

