#include "Tokenizer.hpp"

bool Tokenizer::check(string token) {
    for(int i=0;i<token.length();i++) {
        if(isdigit(token[i]) == 0) {
            return false;
        }
    }
    return true;
}

int Tokenizer::flag(vector<string> tokens){
    int count = tokens.size();
    int error = 0;
    for(int i =0 ; i< count;i++){
        if(error == -1 && check(tokens[i])) {
            break;
        }
        else if (error == -1 && !check(tokens[i])) {
            error = 2;
        }
        else if (check(tokens[i]) && count == 1) {
            error = 1;
            break;
        } else if (check(tokens[i]) && count == 2) {
            error = 2;
            break;
        } else {
            error = -1;
        }
    }
    return error;
}
vector<string> *Tokenizer::getTokens(string line) {
    string delim = (" \t\n");
    size_t first = line.find_first_not_of(delim, 0); //start at 0 go until delimiter
    size_t last = line.find_first_of(delim, first); //start at first go until next delimiter
    vector<string> *tokens = new vector<string>();
    while(first != string::npos || last != string::npos){
        std::string token = line.substr(first, last-first);
        tokens->push_back(token);
        first = line.find_first_not_of(delim, last);
        last = line.find_first_of(delim, first);
    }
    return tokens;
}

vector<string>*Tokenizer::GetTokens() {
        string buff;
        do {
            printf("> ");
            getline(cin, buff);
            vector<string>* tokens = getTokens(buff);

            int c = tokens->size();
            if (c > 2 || c == 0) {
                printf("ERROR! Incorrect number of tokens found.\n");
                continue;
            } else if (strlen(buff.c_str()) > 66) {
                printf("ERROR! Input string too long.\n");
                continue;
            }
            switch (flag(*tokens)) {
                case 1:
                    printf("ERROR! Expected STR.\n");
                    continue;
                case 2:
                    printf("ERROR! Expected STR INT.\n");
                    continue;
            }
            return tokens;
        } while (true);
}