#ifndef PROJECT_AK2_VIRTUAL_MACHINE_H
#define PROJECT_AK2_VIRTUAL_MACHINE_H

#include <iostream>
#include <vector>

//Type definitions
typedef int32_t sint; //signed integer

class VirtualMachine{
    std::vector<sint> memory;
    sint PC = 100; //Program counter
    sint SP = 99; //Stack pointer
    sint type = 0;
    sint data = 0;
    sint running = 1;

    //Functions
    void fetch();
    void decode();
    void execute();
    sint getType(sint token);
    sint getData(sint token);
    void exInstruction();

    public:
    VirtualMachine();
    void run();
    void load(std::vector<sint> program);
};

#endif //PROJECT_AK2_VIRTUAL_MACHINE_H
