/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment2 Multi-processing file editor
reading.cpp

This function reads and prints to the termimal the contents of a file.

*/

#include"a2.h"
using namespace std;
void reading (string path){	
	chdir(path.c_str());
	string name;
	string content;
	int status;
	cout << "Current path: " << path << endl;
	cout << "Enter the filename that you want to read " << endl;
	cin >> name;
	string nameBak;
	nameBak = name;
	nameBak.append(".bak"); 

	pid_t pid = fork(); //create child process
	if (pid < 0){
		cout << "fork() failed" << endl;
		exit(EXIT_FAILURE);
	}
	if (pid == 0){ // child pid
		ifstream readfile(name.c_str(),ios::binary);
		if(readfile.is_open()){ //if the file exists, make a back up
			ofstream backupFile(nameBak.c_str(),ios::binary);
			backupFile << readfile.rdbuf();
			backupFile.close();
			readfile.close();
			exit(EXIT_SUCCESS);
		}
		else{
			exit(EXIT_SUCCESS);
		}
	}
	else {
		wait(&status);
		ifstream readfile(name.c_str());
		if(readfile.is_open()){
			getline(readfile,content);
			while(!readfile.eof()){
				cout << content << endl;  //print content to screen
				getline(readfile,content);
			}
			readfile.close();
		}
		else
			cout << "Error opening file" << endl;	
		}
}//end function
