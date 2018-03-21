
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace  std;


class MyCompress {
	
	char* inFile;
	char* outFile;
	char flag;
	void show_help(string);
	int compress();
	void write(char, int, ostream*&);

	public:
		// MyCompress (string, string);
		int parseArgs(int, char**);
		

};

// MyCompress::MyCompress (string in, string out) {
// 	inFile = in;
// 	outFile = out;
// }

int MyCompress::compress() {
	
	ifstream ifs;
	istream* input_stream = &cin;

	ofstream ofs;
	ostream* output_stream = &cout;
	
	if (strlen(inFile) != 0) {
		ifs.open(inFile);
		input_stream = &ifs;
	}
	if (strlen(outFile) != 0) {
		cout << outFile << " used!" << endl;
		ofs.open(outFile);
		output_stream = &ofs;
	}

	string line;
	char next;
	int pvalid = 0;
	char prev;
	int n = 1;

	while ( input_stream->get(next)  ) {
		if (!pvalid) {
			prev = next;
			pvalid = 1;
			continue;
		}
		if (next == prev) {
			n++;
		}
		else {
			write(prev, n, output_stream);
			prev = next;
			n = 1;
		}
	}
	write(prev, n, output_stream);

	return 0;
}

void MyCompress::write(char prev, int n, ostream*& output_stream) {
	
	vector<char> buff;
	if (isdigit(prev) || prev == '\\') {
		buff.push_back('\\');
	}
	buff.push_back(prev);
	if (n > 1) {
		// To cast int to char  (char)n didnt work as it converts to ascii
		string s = to_string(n);
		cout << s << endl;
		char* c = &s[0];
		for (int i = 0; i < strlen(c); i++) {
			buff.push_back(c[i]);
		}
		// char c = s[0];
		// buff.push_back(c);
	}
	// for ()
	for (auto i = buff.begin(); i != buff.end(); i++) {
		// cout << *i;
		*output_stream << *i;
	}
}

int MyCompress::parseArgs(int argc, char* argv[]) {

	if (argc < 2) {
		show_help(argv[0]);
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
	if (argc == 3) {
		if ( (string) argv[1] == "-c" ) {
			inFile = argv[2];
			outFile = (char*) "";
			// cout << outFile << endl;
			return compress();
		}
	}
	if (argc == 4) {
		// TODO: Check voor input output files
		if ( (string) argv[1] == "-c" ) {
			inFile = argv[2];
			outFile = argv[3];
			return compress();
		}
	}
	return 0;

}

void MyCompress::show_help(string name) {
	cerr << "Usage " << name << " [OPTION] [INPUT FILE] [OUTPUT FILE]\n"
		 << "Options:\n"
		 << "  -h\tShow this help message\n"
		 << "  -c\tCompress input to output\n"
		 << "  -d\tDecompress input to output\n";
}

int main(int argc, char* argv[]) {

	MyCompress comp;

	int c = comp.parseArgs(argc, argv);

	if (c == 1) {
		return 0;
	}
	return 0;
}