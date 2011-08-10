#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


using namespace std;

char *_file;
char *_out;
char *_buffer;

const char *_header = "#include <stdio.h>\nchar mem[30000];\nint main(int argc, char **argv) {\n\tchar *buffer = mem;\0";

//easier to see if i put them in {}
const char *validChars = "><.,[]+-*:{0123456789}\n\r\0";

char *movePointer(int teller) {
	return teller > 0 ? (char *)"++buffer;\0" : (char *)"--buffer;\0";
}

char *printPointer() {
	return (char *)"putchar(*buffer);\0";
}

char *setPointer() {
	return (char *)"*buffer=getchar();\0";
}

char *openWhile() {
	return (char *)"while(*buffer) {\0";
}

char *closeWhile() {
	return (char *)"}\0";
}	


char *changePointer(int teller) {
 	return teller > 0 ? (char *)"++*buffer;\0" : (char *)"--*buffer;\0";       
}

char *pointerRandom() {
	return (char *)"*buffer = arc4random() % 255;";
}

char *moveTo(char *where) {
	string result("buffer = mem;\n");
	result += "buffer += ";
	result += where;
	result += ";";
	return (char *)result.c_str();
}

char *printIntPointer() {
	return (char *)"printf(\"%i\", *buffer);";	
}

char *errorCommand() {
	return (char *)"poop\0";
}

char *createFileBuffer(char *buffer, int *length) {
	
	string result(_header);
	unsigned int place = 0;
	unsigned int brackets = 0;
	while (place < (unsigned)strlen(buffer)) {
		
		result += "\n";
                result += "\t";
                for (int i = 0; i < brackets; i++) {
                        result += "\t";
                }

		char *command;
		
		switch (buffer[place]) {

			case '>':
				command = movePointer(1);
				break;
			case '<':
				command = movePointer(-1);
				break;
			case '.':
				command = printPointer();
				break;
			case ',':
				command = setPointer();
				break;
			case '[':
				brackets++;
				command = openWhile();
				break;
			case ']':
				brackets--;
				command = closeWhile();
				break;
			case '+':
				command = changePointer(1);
				break;
			case '-':
				command = changePointer(-1);
				break;
			case '*':
				command = pointerRandom();
				break;
			case '{': {
				string where("");
				place++;
				while (buffer[place] != '}') {
					where += buffer[place++];
				}
				command = moveTo((char *)where.c_str());
				break;
			}
			case ':':
				command = printIntPointer();
				break;
			default:
				command = "\n";
				break;
		}

		result += command;
		place++;
	}

	result += "}";

	*length = result.length();

	return (char *)result.c_str();

}


void parse(char *buffer) {

	cout << "Parsing..." << endl;
	
	unsigned int strl = (int)strlen(buffer);
	
	unsigned int place = 0;
	
	int brackets = 0;

	int curlyBrackets = 0;
	
	while (place < strl) {
		
		char c = buffer[place];
		bool valid = false;
		for (unsigned int i = 0; i < (unsigned)(strlen(validChars)+1); i++) {
			if (c == validChars[i]) {
				valid = true;
				break;
			}
		}
		switch (c) {
                        case '[':
                                brackets++;
                                break;
                        case ']':
                                brackets--;
                                break;
                        case '{':
                                curlyBrackets++;
                                break;
                        case '}':
                                curlyBrackets--;
                                break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (curlyBrackets <= 0) {
					cout << "Expected { before " << c << endl;
					valid = false;
				}
			default:
				break;
		}

		if (!valid) {
			cout << "Invalid char " << c << " at place " << place << endl;
			exit(1);	
		}
		place++;
	}
	
	if (brackets != 0) {
		cout << "Brackets are mismatched, check your code" << endl;
		exit(1);
	}
}

void printhelp() {
	cout << "help has yet to be written" << endl;
}

int main(int argc, char **argv) {

	if (argc - 1 != 2) {
		printhelp();
		exit(1);
	}
	
	_file = new char[strlen(argv[1])];
	strcpy(_file, argv[1]);
	_out = new char[strlen(argv[2])];
	strcpy(_out, argv[2]);
	
	struct stat st;

	if (stat(_file, &st) != 0) {

		cout << "No file found at path " << _file << endl;
		exit(1);

	}

	_buffer = new char[st.st_size];

	FILE *inFile;
	if (!(inFile = fopen(_file, "r"))) {
		
		cout << "Could not open file " << _file << " for reading" << endl;
		exit(1);
	}
	if ((unsigned)st.st_size != (unsigned)fread(_buffer, 1, st.st_size, inFile)) {
		
		cout << "Could not read file " << _file << endl;
		exit(1);

	}
	fclose(inFile);

	parse(_buffer);

	int length = 0;
	
	char *fileBuffer = createFileBuffer(_buffer, &length);

	cout << "Got file buffer" << endl;

	FILE *outFile;
	
	char *tmpCFile = new char[strlen(_out)+3+1];
	
	tmpCFile[0] = '.';
	int place = 0;
	for (unsigned int i=0; i < (unsigned)strlen(_out); i++) {
		tmpCFile[++place] = _out[i];
	}
	tmpCFile[++place] = '.';
	tmpCFile[++place] = 'c';
	tmpCFile[++place] = '\0';

	if (!(outFile = fopen(tmpCFile, "w+"))) {
		cout << "Could not open " << _out << " for writing" << endl;
		exit(1);
	}

	if ((unsigned)length != (unsigned)fwrite(fileBuffer, 1, length, outFile)) {
		cout << "Could not write to file " << tmpCFile << endl;
		exit(1);
	}

	pid_t cid = fork();

	if (cid == 0) {

		cout << "Compiling.... " << endl;
	
		string command(GCC_PATH);
	
		command += " ";
		command += tmpCFile;
		command += " ";
		command += "-o ";
		command += _out;

		system(command.c_str());

	}
	
	delete _file;
	delete _out;
	delete tmpCFile;
	delete _buffer;

	return 0;
}

