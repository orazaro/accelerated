
PROGRAMS = fail_pass gen_students
TESTS = 

OBJECTS = median.o grade.o Student_info.o
OBJ = $(OBJECTS) list_main.o
HFILES = $(OBJECTS:%.o=%.h)
LIBRARIES = cppunit

CXX = g++
CPPFLAGS += -Wall -O2
LDFLAGS = $(LIBRARIES:%=-l%)

.PHONY: all clean test

all: $(PROGRAMS)

test: $(TESTS) all
	./fail_pass <../data/grades


fail_pass: $(OBJ) $(HFILES)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

%.o: %.cpp %.h Student_info.h
	$(CXX) -c $(CPPFLAGS) $<

clean:
	rm -f *.o $(PROGRAMS) $(TESTS)
