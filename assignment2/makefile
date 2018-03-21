CC		= g++
CPPV	= -std=c++11

run: MyCompress.cpp
	$(CC) $(CPPV) MyCompress.cpp -o MyCompress.o

clean:
	rm *.o

submit: MyCompress.cpp original.txt README.md makefile
	tar -zcvf MyCompress.tar.gz MyCompress.cpp original.txt README.md makefile