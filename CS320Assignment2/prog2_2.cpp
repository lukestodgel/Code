#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <cstddef>
#include "Tokenizer.hpp"


using namespace std;
bool check(string token) {
    for(int i=0;i<token.length();i++) {
        if(isdigit(token[i]) == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    printf("Assignment #2-2, Luke Stodgel, lukersmaster@aol.com\n");
    if (argc != 2) {
        printf("ERROR! Program accepts 1 command line argument.");
        return 1;
    }
    int n = (int) strtol(argv[1], NULL, 10);  //number of times to prompt user. (base 10)
    if (n == 0) {
        printf("ERROR! Expected integer argument.");
        return 1;
    }
    string buff;
    Tokenizer token;
    do {
        if(n==0) {
            return 0;
        }
        vector<string>* tokens = token.GetTokens();
        if (strncasecmp((*tokens)[0].c_str(), "quit", (*tokens)[0].length()) == 0) {
            return 0;
        }
        for (int i = 0;i< tokens->size(); i++) {
            if (check((*tokens)[i])) {
                printf("INT ");
            } else {
                printf("STR ");
            }
        }
        printf("\n");
        n--;
    } while (true);
}