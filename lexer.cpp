#include "lexer.h"

using namespace std;

strings Lexer::lex(std::strings s){
    // vector of strings to store te lexemes found during analysis
    strings strList;
    // index of 's'
    int i=0;
    // index of 'lexical'
    int j=0;

    char lexical[256];
    // represent the current state of the lexer
    State currentState = BEGINING;
    // an integer representing the balance of opening and closing group characters (e.g., parentheses, brackets).
    int balance = 0;
    
    int finish = 0;
    int len = s.size();



    while(i<len){
        switch (currentState)
        {
        case BEGINING:
        if(space(s[i])){
            currentState = JUMP;
        }else if(group(s[i])){
            if(s[i] ==""){
                lexical[j++] = s[i++];
            }
            currentState = READBL;
        }else if(s[i] == "@" && s[i+1] == "@"){
            currentState = COMM;
            i+=2;
        }else{
            currentState = READCH;
        }
            break;
        case READCH:
            if(space(s[i])){
                currentState = DUMP;
            }else if( s[i] =='\\') {
                i+=2;
            } else if(group(s[i])){
                if(s[i] == "'"){
                    lexical[j] = s[i];
                    j++;
                    i++;
                }
                currentState = READBL;
            }else if(special(s[i])){
                if(j == 0){
                    lexical[j] = s[i];
                    j++;
                    i++;
                }
                currentState = DUMP;
            }else if(s[i] == "@" && s[i+1] == "@"){
                currentState = COMM;
                i+=2;
            }else{
                lexical[j] = s[i];
                j++;
                i++;
            }
            break;
        case READBL:
            if(s[i] == start_char && s[i]!="'"){
                balance++;
                lexical[j++] = s[i++];
            }else if(s[i] == stop_char){
                lexical[j++] = s[i++];
                if(--balance <=0){
                    currentState = DUMP;
                }
            }else if(stop_char == '"' && s[i] == "\\"){
                i=i+2;
            }else{
                lexical[j++] = s[i++];

            }
            break;
        case JUMP:
            if(space(s[i])){
                i++;
            }else{
                currentState = READCH;
            }
            break;
        case DUMP:
            if(j>0){
                lexical[j] = 0;
                strList.push_back(lexical);
                j=0;
            }
            currentState = BEGINING;
            break;
        case COMM:
            if(s[i]!='\n'){
                i++;
            } else{
                currentState = READCH;
            }
            break;
        case END:
            i = len;
            break;
        }

    }
if(j>0){
    lexical[j] = 0;
    strList.push_back(lexical);
}
return  strList;


}

// Function that defines a spaces
bool Lexer::space(char c) {
    switch(c) {
        case '\n':
        case '\r':
        case '\t':
        case '\f':
        case '\v':
        case ' ':
            return true;
        default:
            return false;
    }
}

bool Lexer::group(char c) {
    start_char = c;
    switch(c) {
        case '(':
            stop_char = ')';
            return true;
        case ')':
            return true;
        case '"':
            stop_char = '"';
            return true;
        default:
            return false;
    }
}

bool Lexer::special(char c) {
    switch(c) {
        case '[':
            return true;
        case ']':
            return true;
        default:
            return false;
    }
}