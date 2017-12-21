#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <cstddef>
#include "Tokenizer.hpp"
#include "Stack.hpp"


using namespace std;

int check(string token) {
    for (int i = 0; i < token.length(); i++) {
        if (isdigit(token[i]) == 0) {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    printf("Assignment #2-3, Luke Stodgel, lukersmaster@aol.com\n");

    if (argc != 2) {
        printf("ERROR! Program accepts 1 command line argument.");
        return 1;
    }
    int n = (int) strtol(argv[1], NULL, 10);  //number of times to prompt user. (base 10)
    if (n == 0) {
        printf("ERROR! Expected integer argument.");
        return 1;
    }
    Tokenizer toke;
    Stack<string> stack;
    do {
        if (n == 0) {
           stack.Print();
            return 0;
        }
        vector<string> *tokens = toke.GetTokens();
        if (strncasecmp((*tokens)[0].c_str(), "quit", (*tokens)[0].length()) == 0) {
            stack.Print();
            return 0;
        }
        if (tokens->size() == 2) {
            if ((*tokens)[0].compare("push")==0) {
                stack.Push(tokens[0][1]);
            }
        } else if ((*tokens).size() == 1) {
            if ((*tokens)[0].compare("pop")==0) {
                stack.Pop();
            }

        }
        n--;
    } while (true);
}