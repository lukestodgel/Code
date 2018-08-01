/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment2 Multi-processing file editor
creating.cpp

This function allows the user to create regular or directory files.

*/
#include"a2.h"
using namespace std;

void creating (string path){
	while(1){
		string tmp; 
		string option;//2 for directory file, 1 for regular file.
		string name;
		cout << "***************Sub-Menu****************" << endl;
		cout << "*1.create a file in current directory *" << endl;
		cout << "*2.create a new directory             *" <<endl;
		cout << "*0.Back to main menu                  *" <<endl;
		cout << "***************************************" << endl;
		cin >> option; 
		if(option == "2"){
			cout << "Enter name of new directory" << endl;
			cin >> tmp;
			path.append(tmp);
			mkdir(path.c_str(),S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
			break; 
		}
		else if (option == "1"){
			cout<< "Enter the filename that you want to create" << endl;
			cin>> name;
			ofstream filename;
			filename.open(name.c_str(),ofstream::in|ofstream::out|ofstream::app);
			filename.close();
			break;
		}
		else if(option == "0"){
			break;
		}
		else
			cout << "Please enter vaild number." << endl;	
	}// end while
}// end function
