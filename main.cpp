#include "VirtualMachine.h"

int main(){
    VirtualMachine VM;
    std::vector<sint> program{21, 37, 0x40000001, 8,0x40000002,12,0x40000003,5,0x40000004,0x40000000};
    VM.load(program);
    VM.run();
    return 0;
}