#include "VirtualMachine.h"
#include "VirtualMachine.cpp"

int main(){
    VirtualMachine VM;
    std::vector<sint> program{21, 37, 0x40000001, 0x40000000};
    VM.load(program);
    VM.run();
    return 0;
}