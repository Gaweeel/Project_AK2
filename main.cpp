#include <iostream>
#include <fstream>
#include "VirtualMachine.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "Usage message: " << argv[0] << " <filename>" << endl;
        return 0;
    }

    ifstream r(argv[1], ios::binary);
    i32 i;
    vector<i32> program;

    while (r.read((char*)&i, sizeof(i))) {
        program.push_back(i);
    }

    VirtualMachine VM;
    // std::vector<sint> program{21, 37, 0x40000001, 8,0x40000002,12,0x40000003,5,0x40000004,0x40000000};
    VM.load(program);
    VM.run();
    return 0;
}