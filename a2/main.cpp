/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment 2 Multi-processing file editor
main.cpp

This is the main function. The user will choose what he/she wants to do with the file editor, andthat function will execute.

*/
#include"a2.h"
using namespace std;

int main(int argc, char* argv[]){
	string path = "/home/cs/gleonard/cssc1069/a2/";
	bool trigger = true; 
	while(trigger){
		cout<< "*************MENU*************" << endl;
		cout<< "* 1. Creating files          *" << endl;
		cout <<"* 2. Reading files           *" << endl;
		cout <<"* 3. Writing files           *" << endl;
		cout <<"* 4. Print file status       *"<< endl;
		cout <<"* 5. Print dir listing       *" << endl;
		cout <<"* 0. Exit                    *" << endl;
		cout <<"******************************" << endl;
	
		int index;
		cin >> index;
		switch (index) {
			case 1:
				creating(path); 
				break;
			case 2: 
				reading(path);
				break;
			case 3:
				writing(path); 
				break;
			case 4: 
				status(path);
				break;
			case 5:
				dirListing(path);
				break;
			case 0:
				trigger = false;
				break;
			default: 	
				cout << "please enter the vaild number." << endl;
				trigger =false;
			
		}
	}	
		
	return 0;
}
