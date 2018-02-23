CC		= g++
CPPV	= -std=c++11

all: run test

run: run.cpp assignment1.cpp 
	$(CC) $(CPPV) run.cpp -o run.o

test: testCode.cpp assignment1.cpp
	$(CC) $(CPPV) testCode.cpp -o testCode.o

clean:
	rm *.o
