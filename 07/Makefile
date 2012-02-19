PROGRAMS = main
TESTS = 

OBJECTS = median.o grade.o Student_info.o
OBJ = $(OBJECTS) main.o
HFILES = $(OBJECTS:%.o=%.h)
LIBRARIES = cppunit

CXX = g++
CPPFLAGS += -Wall -O2
LDFLAGS = $(LIBRARIES:%=-l%)

.PHONY: all clean test

all: $(PROGRAMS)

test: $(TESTS) all
	./main <../data/grades

main: main.o $(OBJECTS) $(HFILES)
	$(CXX) $(OBJECTS) $< $(LDFLAGS) -o $@

%.o: %.cpp %.h Student_info.h
	$(CXX) -c $(CPPFLAGS) $<

clean:
	rm -f *.o $(PROGRAMS) $(TESTS)
