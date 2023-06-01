#ifndef PROJECT_AK2_LEXER_H
#define PROJECT_AK2_LEXER_H

#include<iostream>
#include <vector>

typedef uint8_t byte;
typedef std::vector<std::string> strings;

enum State:byte {
    BEGINING, //0
    READCH,   //1
    READBL,   //2
    JUMP,     //3
    DUMP,     //4
    COMM,     //5
    END       //6
};

class Lexer{
    char start_char, stop_char;
    bool special(char c);
    bool space(char  c);
    bool group(char c);
    public:
    strings lex(std::string txt);

};


#endif

