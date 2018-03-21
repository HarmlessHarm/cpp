
#include <iostream>
#include <fstream>
#include <string>

using namespace  std;


class MyCompress {
	
	string inFile, outFile;
	char flag;
	void show_help(string);

	public:
		// MyCompress (string, string);
		int compress();
		int parseArgs(int, char**);
		

};

// MyCompress::MyCompress (string in, string out) {
// 	inFile = in;
// 	outFile = out;
// }

int MyCompress::compress() {
	// int b = 0;
	return 0;
}

int MyCompress::parseArgs(int argc, char* argv[]) {
	// cout << argc << endl;
	// for (int i = 0; i < argc; i++) {
	// 	cout << argv[i] << endl;
	// }
	if (argc < 2) {
		show_help(argv[0])
		return 1;
	}
	if (argc == 2) {
		if ((string) argv[1] == "-h") {
			show_help(argv[0]);
			return 1;
		}
		else {
			cout << "Ga iets doen met user input en output" << endl;
			return 1;
		}
	}
	if (argc == 4) {
		// Check voor input output files
	}

}

void MyCompress::show_help(string name) {
	cerr << "Usage " << name << " [OPTION] [INPUT FILE] [OUTPUT FILE]\n"
		 << "Options:\n"
		 << "  -h\tShow this help message\n"
		 << "  -c\tCompress input to output\n"
		 << "  -d\tDecompress input to output\n";
}

int main(int argc, char* argv[]) {

	MyCompress comp ();

	int c = comp.parseArgs(argc, argv);

	if (c == 1) {
		return 0;
	}
	string line;
	char nextChar;
	ifstream myfile (argv[1]);
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