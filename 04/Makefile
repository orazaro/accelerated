
PROGRAMS = cppunittest main1 main2
TESTS = main1_test

OBJECTS = median.o grade.o Student_info.o
HFILES = $(OBJECTS:%.o=%.h)
OBJ1 = main1.o $(OBJECTS)
OBJ3 = main2.o $(OBJECTS)
OBJ2 = run_test.o test.o $(OBJECTS)
LIBRARIES = cppunit

CXX = g++
CPPFLAGS += -Wall -O2
LDFLAGS = $(LIBRARIES:%=-l%)

.PHONY: all clean test

all: $(PROGRAMS)

test: $(TESTS)
	./main1_test

cppunittest: 04-00-CppUnit.o
	$(CXX) $< $(LDFLAGS) -o $@

main1: $(OBJ1) $(HFILES)
	$(CXX) $(OBJ1) $(LDFLAGS) -o $@

main2: $(OBJ3) $(HFILES)
	$(CXX) $(OBJ3) $(LDFLAGS) -o $@

main1_test: $(OBJ2) $(HFILES)
	$(CXX) $(OBJ2) $(LDFLAGS) -o $@

main2.o: Student_info.h

%.o: %.cpp %.h Student_info.h
	$(CXX) -c $(CPPFLAGS) $<

clean:
	rm -f *.o $(PROGRAMS) $(TESTS)
