CC		= g++
CPPV	= -std=c++11

run: assignment.cpp
	$(CC) $(CPPV) assignment.cpp -o assignment.o

clean:
	rm *.o

submit: assignment2.cpp original.txt README.md makefile
	tar -zcvf assignment2.tar.gz assignment2.cpp original.txt README.md makefile