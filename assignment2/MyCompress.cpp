
#include <iostream>
#include <fstream>
#include <string>

using namespace  std;


class MyCompress {
	
	string inFile, outFile;
	public:
		MyCompress (string, string);
		void readFile();

};

MyCompress::MyCompress (string in, string out) {
	inFile = in;
	outFile = out;
}

void MyCompress::readFile() {
	// int b = 0;
}


int main(int argc, char* argv[]) {

	MyCompress comp ("hoi", "hai");

	// string in = "original.txt";
	char in[32] = "original.txt";
	string line;
	char nextChar;
	ifstream myfile (in);
	if (myfile.is_open()) {
		while ( myfile.get(nextChar)  ) {
			cout << nextChar << '\n';
		}
		myfile.close();
	}
	else {
		cout << "No file opened";
	}


	return 0;
}