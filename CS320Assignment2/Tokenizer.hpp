#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <cstddef>


using namespace std;

class Tokenizer {
private:
    bool check(string);
    int flag(vector<string>);
    vector<string> *getTokens(string);
public:
    vector<string> *GetTokens();

};