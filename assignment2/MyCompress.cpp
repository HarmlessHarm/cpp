
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

	char inFlag = 'c';
	char outFlag = 'c';

	int count_in = 0;
	int count_out = 0;

	void write_compress(char, int);
	void write_decpomress(char, string);

	public:
		char flag;
		MyCompress(int, char*, char*);
		int compress();
		int decompress();
		static int show_help(string);
};

MyCompress::MyCompress (int f, char* inFile, char* outFile) {
	
	flag = f;
	// Checks if a file is given, 
	// if so uses the filestream not the command line stream
	if (strlen(inFile) != 0) {
		ifs.open(inFile);
		input_stream = &ifs;
		inFlag = 'f';
	}
	// Tooltip for using cin
	else cerr << "Use ^D when finished to declare EOF" << endl; 
	if (strlen(outFile) != 0) {
		ofs.open(outFile);
		output_stream = &ofs;
		outFlag = 'f';
	}
}

int MyCompress::compress() {
	
	char next;
	char prev;
	int pvalid = 0;
	int n = 1;

	while ( input_stream->get(next)  ) {
		count_in++;
		// Prev not valid on start because no prev char
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

	cerr << "\nCompression rate: " << (float)count_out / count_in << endl;
	count_out = 0;
	count_in = 0;
	return 0;
}

void MyCompress::write_compress(char prev, int n) {
	
	// Buffer output to build entire print array
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
		count_out++;
	}
}

int MyCompress::decompress() {

	char next;
	char c;
	// A string so a multi digit number can be represented
	string n;
	char end = 0;

	input_stream->get(next);
	count_in++;
	while ( input_stream->good() ) {
		// check if special char
		if (next == '\\') {
			input_stream->get(next);
			count_in++;
		}
		c = next;
		input_stream->get(next);
		count_in++;
		// Read multi digit numbers
		while( isdigit(next) ) {
			n += next;
			input_stream->get(next);
			count_in++;
		}
		// When no number specified n = 1
		if (n.length() == 0) {
			n = "1";
		}
		write_decpomress(c, n);
		n = "";
	}

	cerr << "\nCompression rate: " << (float)count_out / count_in << endl;
	count_out = 0;
	count_in = 0;

	return 0;
}

void MyCompress::write_decpomress(char c, string in) {

	int n = atoi (in.c_str());
	for ( int i = 0; i < n; i++ ) {
		*output_stream << c;
		count_out++;
	}
}

int MyCompress::show_help(string name) {
	// Write man to cerr as not to corrupt outputfiles
	cerr << "Name\n"
		 << "   MyCompress\n"
		 << "Synopsis\n"
		 << "   MyCompress <flag> [<input-filename>] [<output-filename>]\n"
		 << "Description\n"
		 << "   Compresses and decompresses text files.\n"
		 << "   If no output filename is given it writes to standard output (stdout).\n"
		 << "   If no input filename is given it reads from standard input (stdin).\n"
		 << "Options for <flag>\n"
		 << "   -h\tgive this usage information and exit\n"
		 << "   -c\tcompress the input file and write result to output file\n"
		 << "   -d\tdecompress the input file and write result to output file\n"
		 << "Example Usage\n"
		 << "   MyCompress -c input.txt output.txt # compress input.txt to output.txt\n"
		 << "   cat output.txt | MyCompress -d # read from stdin, decompress to stdout\n";
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

	if (argc >= 1) {
		// Loop through args set flags, input and output
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
				else {
					cerr << arg << " doesn't exist!" << endl;
					return 1;
				}
			}
			else if (strlen(outFile) == 0) {
				outFile = argv[i];
			}
		}
	}
	
	cerr << flag << " in: " << inFile << " out: " << outFile << endl;
	MyCompress compressor (flag, inFile, outFile);
	if (compressor.flag == 'd') {
		return compressor.decompress();
	}
	else return compressor.compress();
	return 0;
}