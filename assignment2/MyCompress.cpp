
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace  std;


class MyCompress {
	
	istream* input_stream = &cin;
	ostream* output_stream = &cout;

	ifstream ifs;
	ofstream ofs;
	

	void write_compress(char, int);

	public:
		char flag;
		MyCompress(int, char*, char*);
		int compress();
		static int show_help(string);
};

MyCompress::MyCompress (int f, char* inFile, char* outFile) {
	
	flag = f;
		
	if (strlen(inFile) != 0) {
		ifs.open(inFile);
		input_stream = &ifs;
	}
	else cerr << "Use ^D when finished to declare EOF" << endl; 
	if (strlen(outFile) != 0) {
		ofs.open(outFile);
		output_stream = &ofs;
	}
}

int MyCompress::compress() {
	
	string line;
	char next;
	char prev;
	int pvalid = 0;
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
			write_compress(prev, n);
			prev = next;
			n = 1;
		}
	}
	// Write last read char.
	write_compress(prev, n);

	return 0;
}

void MyCompress::write_compress(char prev, int n) {
	
	vector<char> buff;
	if (isdigit(prev) || prev == '\\') {
		buff.push_back('\\');
	}
	buff.push_back(prev);
	if (n > 1) {
		// To cast int to char. (char)n didnt work as it converts to ascii
		string s = to_string(n);
		char* c = &s[0];
		for (int i = 0; i < strlen(c); i++) {
			buff.push_back(c[i]);
		}
	}
	for (auto i = buff.begin(); i != buff.end(); i++) {
		*output_stream << *i;
	}
}

int MyCompress::show_help(string name) {
	cerr << "Usage: " << name << " <OPTION> [INPUT FILE] [OUTPUT FILE]\n"
		 << "Options:\n"
		 << "  -h\tShow this help message\n"
		 << "  -c\tCompress input to output\n"
		 << "  -d\tDecompress input to output\n"
		 << '\n'
		 << "  -o\tSpecify output file\n"
		 << "  -i\tSpecify input file\n"
		 << "If no output file is provided output is sent to terminal\n"
		 << "If no input file is provided input is provided by terminal\n";
}

bool exists (string name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char* argv[]) {

	char* inFile = (char*) "";
	char* outFile = (char*) "";
	char flag = 'c';
	char flagSet = 0;

	if (argc < 2) {
		return MyCompress::show_help(argv[0]);
	}
	if (argc >= 2) {
		for (int i = 1; i < argc; i++) {
			string arg = argv[i];
			if (arg == "-h") {
				return MyCompress::show_help(argv[0]);
			}
			else if (arg == "-c" && !flagSet) {
				flag = 'c';
				flagSet = 1;
			}
			else if (arg == "-d" && !flagSet) {
				flag = 'd';
				flagSet = 1;
			}
			else if (arg == "-o") {
				if (i + 1 < argc) {
					outFile = argv[i + 1];
					i++;
				}
				else {
					cerr << "-o requires an argument" << endl;
					return 1;
				}
			}
			else if (arg == "-i") {
				if (i + 1 < argc) {
					inFile = argv[i + 1];
					i++;
				}
				else {
					cerr << "-i requires an argument" << endl;
					return 1;
				}
			}
			else if (strlen(inFile) == 0) {
				if (exists(arg)) {
					inFile = argv[i];
				}
				else {MyCompress
					cerr << arg << " doesn't exist!" << endl;
					return 1;
				}
			}
			else if (strlen(outFile) == 0) {
				outFile = argv[i];
			}
		}
	}
	
	cout << flag << " i: " << inFile << " o: " << outFile << endl;
	MyCompress compressor (flag, inFile, outFile);
	if (compressor.flag == 'c') {
		return compressor.compress();
	}
	// else return compressor.compress();
	return 0;
}