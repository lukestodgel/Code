/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment 2 Multi-processing file editor
status.cpp

This function gets a filename from the user and returns its status.

We used the sys/stat package to make a stat variable which gave us functions
that allowed us to list characteristics about a file.
*/


#include"a2.h"

using namespace std;
void status (string path){
	chdir(path.c_str());
	string filename;
	cout<< "Please enter filename that you want the status of."<< endl;
	cin >>  filename;
	struct stat fileStat;
	if(stat(filename.c_str(),&fileStat) < 0){ 
		cout << "stat failed"<< endl;
	}
	else{
		cout << "*********************************"<<endl;
		cout << "Filename: " << filename << endl;
		cout << "File Size: " << fileStat.st_size << " bytes" << endl;
		cout << "Number of Links: " << fileStat.st_nlink << endl;
		cout << "File inode " << fileStat.st_ino << endl;
		cout <<"File Permissions: ";
    		cout << ((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    		cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    		cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    		cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    		cout << ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    		cout << ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    		cout << ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    		cout << ((fileStat.st_mode & S_IROTH) ? "r" : "-");
    		cout << ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    		cout << ((fileStat.st_mode & S_IXOTH) ? "x" : "-")<< endl;
    		cout <<"The file "<< ((S_ISLNK(fileStat.st_mode)) ? "is" : "is not")<<" a symbolic link" <<endl <<endl;
 	}
}
