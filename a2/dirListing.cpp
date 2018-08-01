/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment2 Multi-processing file editor
dirListing.cpp

This function prints to the terminal the contents of the current directory.
*/

#include"a2.h"
using namespace std;

void dirListing(string path){
	DIR *tmp;
	struct dirent *dir;
	tmp = opendir(".");
	cout << "Current path: " << path << endl;
	if(tmp){
		while((dir = readdir(tmp))!= NULL){
			cout << dir->d_name << endl;
		}
		closedir(tmp);
	}

} // end function
