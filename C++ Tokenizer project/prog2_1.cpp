#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <cstddef>


using namespace std;

int check(string token) {
   for(int i=0;i<token.length();i++) {
        if(isdigit(token[i]) == 0) {
            return -1;
        }
    }
    return 0;
}

int flag(vector<string> tokens){
    int count = tokens.size();
    int error = 0;
    for(int i =0 ; i< count;i++){
        if(error == -1 && check(tokens[i]) == 0) {
            break;
        }
        else if (error == -1 && check(tokens[i]) != 0) {
            error = 2;
        }
        else if (check(tokens[i]) == 0 && count == 1) {
            error = 1;
            break;
        } else if (check(tokens[i]) == 0 && count == 2) {
            error = 2;
            break;
        } else {
            error = -1;
        }
    }
    return error;
}
vector<string> getTokens(string line) {
    string delim = (" \t\n");
    size_t first = line.find_first_not_of(delim, 0); //start at 0 go until delimiter
    size_t last = line.find_first_of(delim, first); //start at first go until next delimiter
    vector<string> tokens;
    while(first != string::npos || last != string::npos){
        std::string token = line.substr(first, last-first);
        tokens.push_back(token);
        first = line.find_first_not_of(delim, last);
        last = line.find_first_of(delim, first);
    }
    return tokens;
}

int main(int argc, char *argv[]) {

    printf("Assignment #2-1, Luke Stodgel, lukersmaster@aol.com\n");

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
    do {
        if(n==0) {
            return 0;
        }
        printf("> ");
       getline(cin, buff);
        vector<string> tokens = getTokens(buff);
        int c = tokens.size();
        if (c > 2 || c == 0) {
            printf("ERROR! Incorrect number of tokens found.\n");
            n--;
            continue;
        } else if (strlen(buff.c_str()) > 66) {
            printf("ERROR! Input string too long.\n");
            n--;
            continue;
        }
        switch (flag(tokens)) {
            case 1:
                printf("ERROR! Expected STR.\n");
                n--;
                continue;
            case 2:
                printf("ERROR! Expected STR INT.\n");
                n--;
                continue;
        }
        if (strncasecmp(buff.c_str(), "quit", tokens[0].length()) == 0) {
            return 0;
        }
            for (int i = 0;i< tokens.size(); i++) {
                if (check(tokens[i]) == 0) {
                    printf("INT ");
                } else {
                    printf("STR ");
                }
            }
            printf("\n");
        n--;
    } while (true);
}