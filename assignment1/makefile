CC		= g++
CPPV	= -std=c++11

all: run test testCode

run: run.cpp assignment1.cpp 
	$(CC) $(CPPV) run.cpp -o run.o

testCode: testCode.cpp assignment1.cpp
	$(CC) $(CPPV) testCode.cpp -o testCode.o

test: test.cpp assignment1.cpp
	$(CC) $(CPPV) test.cpp -o test.o

clean:
	rm *.o

submit: assignment1.cpp run.cpp testCode.cpp README.md makefile
	tar -zcvf assignment1.tar.gz assignment1.cpp run.cpp testCode.cpp README.md makefile