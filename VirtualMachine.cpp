#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(){
    memory.reserve(1000000); //reserve memory for processor
}

void VirtualMachine::fetch() {
    PC++;
}

void VirtualMachine::decode() {
    type = getType(memory[PC]);
    data = getData(memory[PC]);
}

void VirtualMachine::execute() {
    if(type == 0 || type == 2){
        SP--;   //Stack growing down
        memory[SP] = data;
    } else{
        exInstruction();
    }
}

/*
 * Format:
 * Type: 2 bits
 * Data: 30 bits
 * 0 -> positive integer
 * 1 -> instruction
 * 2 -> negative integer
 * */

sint VirtualMachine::getType(sint token) {
    sint type = 0xc0000000; //1100... in binary
    type = (type & token) >> 30; //AND the type and shift 30 bits
    return type;
}

sint VirtualMachine::getData(sint token) {
    sint data = 0x3fffffff; //last 30 bits
    data = data & token;
    return data;
}

//Instruction set reference
void VirtualMachine::exInstruction() {
    switch (data) {
        case 0: //STOP
            std::cout << "STOP" << std::endl;
            running = 0;
            break;
        case 1: //ADD
            std::cout << "ADD " << memory[SP + 1] << " " << memory[SP] << std::endl;
            memory[SP + 1] = memory[SP + 1] + memory[SP];
            SP++;
            break;
        case 2: //SUB
             std::cout << "SUB " << memory[SP + 1] << " " << memory[SP] << std::endl;
             memory[SP + 1] = memory[SP + 1] - memory[SP];
             SP++;
             break;
        case 3: //DIV
             std::cout << "DIV " << memory[SP + 1] << " " << memory[SP] << std::endl;
             memory[SP + 1] = memory[SP + 1] / memory[SP];
             SP++;
             break;
        case 4: //MUL
            std::cout << "MUL" << memory[SP + 1] << " " << memory[SP] << std::endl;
             memory[SP + 1] = memory[SP + 1] * memory[SP];
             SP++;
             break;
    }
}

void VirtualMachine::load(std::vector<sint> program) {
    for(sint i = 0; i < program.size(); i++){
        memory[PC + i] = program[i];
    }
}

void VirtualMachine::run() {
    PC -= 1;
    while(running){
        fetch();
        decode();
        execute();
        std::cout << "SP:" << memory[SP] << std::endl;
    }
}

