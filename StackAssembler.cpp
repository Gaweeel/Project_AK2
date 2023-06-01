#include <iostream>
#include <fstream>
#include "lexer.h"

typedef uint32_t i32;

using namespace std;

vector<i32> compileDataToInstructions(string s);
bool integer(string s);
bool primitive(string s);
i32 instructionToNumber(string s);

int main(int argc, char *argv[]) {
    
    // check for some input errors
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <StackAssembler-filename>" << endl;
        exit(1);
    }

    // reading input file
    ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open() == false)
    {
        cout << "Error: unable to open the file [" << argv[1] << "]" << endl;
        exit(1);
    }

    string fileLine;
    string content;

    while(getline(inputFile, fileLine)) {
        content += fileLine + "\n";
    }
    inputFile.close();

    // parsing file
    Lexer lexer;
    strings lexical = lexer.lex(content);

    // compiling lexemes to binary
    vector<i32> instructions = compileDataToInstructions(lexical);
    
    // writing data to binary file
    ofstream ofile;
    ofile.open("out.bin", ios::binary);

    for(i32 i = 0; i < instructions.size(); i++) {
        ofile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(i32));
    }

    ofile.close();
    return 0;
}

vector<i32> compileDataToInstructions(string s) {
    vector<i32> instructions;

    for(i32 i = 0; i < s.size(); i++) {
        if (integer(s[i])) {
            instructions.push_back(stoi(s[i]));
        }
        else {
            i32 instruction = instructionToNumber(s[i]);
            if (instruction != -1) {
                instructions.push_back(instruction);
            }
            else {
                cout << "Error: Invalid instruction [" << s[i] << "]";
            }
        }
    }
    instructions.push_back(0x40000000); // program won't stuck on an infinite loop
    return instructions;
}

bool integer(string s) {

    for (i32 i = 0; i < s.size(); i++) {
        if (digit(s[i]) == false) {
            return false;
        }
    }

    return true;
}

i32 instructionToNumber(string s) {
    if (s == "+") {
        return 0x40000001;
    }
    else if (s == "-") {
        return 0x40000002;
    }
    else if (s == "*") {
        return 0x40000003;
    }
    else if (s == "/") {
        return 0x40000004;
    }

    return -1; // invalid instruction
}