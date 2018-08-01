/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment2 Multi-processing file editor
writing.cpp

This function asks the user which file he/she would like to write to, and how he/she would like to write to it.

*/

#include"a2.h"
using namespace std;

void writing(string path){
	bool out = true;
	while(out){
	chdir(path.c_str());
	string newFile;
	string existingFileName;
	int status;
	string choice; //determines which type of file to write to

	cout << "---------------------------------------------------" << endl;
	cout << "Current path: " << path << endl;
	cout << "1. write to an existing file?" <<endl;
	cout << "2. write to a new file? " << endl;
	cout << "0. Back to previous menu" << endl;
	cin >> choice;
        if(choice == "1"){  //write to existing file
		string choice2; //determines overwrite or append to existing file
		cout << "Which existing file would you like to write to?" << endl;
		cin >> existingFileName;
		string existingFileNameBak = existingFileName;
		string sortedFile = existingFileName;
		string revesedFile = existingFileName;
		existingFileNameBak.append(".bak");
		sortedFile.append(".bakS");
		revesedFile.append(".bakR");  //creating the names of the back up files
		ifstream readfile(existingFileName.c_str(),ios::binary);
		if(readfile.is_open()){ 
			cout << "----------------------------------" << endl;
			cout <<"1. overwrite" << endl;
			cout <<"2. append to the existing file?" << endl;
			cout <<"3. edit at specific bytes" << endl;
			cout <<"0. Back to previous menu" << endl;
			cin >> choice2;
			if(choice2 =="1"){ //overwrite mode
				string toBeWritten;
				ofstream overwriteFile(existingFileName.c_str(), ios::binary);
				cout << "Please type whatever content you wish" 
					<<"to write followed by pressing the enter key." <<endl;
				cin.ignore();
				getline(cin,toBeWritten);
				overwriteFile << toBeWritten;
				overwriteFile.close();
				out = false;
			}
			if(choice2 =="2"){ //append mode
				string toBeWritten;
				ofstream appendFile(existingFileName.c_str(), ios::out|ios::app|ios::binary);
				cout << "Please type whatever content you wish"
				<< "to add to the end of the existing file." << endl;
				cin.ignore();
				getline(cin,toBeWritten);
				appendFile << toBeWritten;
				appendFile.close();
				out = false;
			}
			if (choice2 == "3"){ //write starting at specific byte
				int num;
				string content;
				fstream editFile(existingFileName.c_str(),ios::in|ios::out|ios::binary);
				cout << "At which byte would you like to start writing to? " << endl;
				cin >> num;
				cout << "Enter content you want to input" << endl;
				cin.ignore();
				getline(cin,content);
				editFile.seekg(num,ios::beg);
				editFile << content;
				editFile.close();
				out = false;
				
			}
			if(choice2 == "0"){
				continue;	
			}
			
			pid_t pid1 = fork();
			pid_t pid2 = fork();
			if (pid1<0 && pid2 <0){
				cout << "fork() failed" << endl;
				exit(EXIT_FAILURE);
			}
			else if (pid1 > 0 && pid2 > 0) { // parent
       				wait(&status);
				exit(EXIT_SUCCESS);
   			}
  			else if (pid1 == 0 && pid2 > 0){//first child creates .bak
        		ifstream readfile(existingFileName.c_str(), ios::binary);
				if(readfile.is_open()){
					ofstream backupFile(existingFileNameBak.c_str(), ios::binary);
					backupFile << readfile.rdbuf();
					backupFile.close();
					readfile.close();
					exit(EXIT_SUCCESS);
				} // end if

    			} // end else if
    			else if (pid1 > 0 && pid2 == 0){//second child creates .bakS file representing an alphabetically sorted back up file
        		vector<string> tokens;
				string content;
				string tmp;
				ifstream file(existingFileName.c_str());
				if (file.is_open()){
					while(!file.eof()){
						getline(file,tmp);
						content.append(tmp);
					}
					file.close();
				}

				stringstream text(content);
				string str;
				while(getline(text,str,' ')){
					tokens.push_back(str);
				}

    				string tmpStr;
    				bool swapped = true;
    				int z = 0; 
    				while(swapped){
        					swapped = false;
         			 	z++;
        					for(int v = 0; v < tokens.size() - z; ++v){
        						if(tokens[v] > tokens[v + 1]){
                 				    tmpStr = tokens[v];
                 				    tokens[v] = tokens[v+1];
                       				tokens[v+1] = tmpStr;
                        			swapped = true;

        						}//end if
        					}//end For	
     				}//end W

				ofstream sortFile(sortedFile.c_str(),ios::binary);
     				for(int j = 0; j < tokens.size(); ++j){
					
					sortFile << tokens[j]<< " ";
     				}
				sortFile.close();
				file.close();
				exit(EXIT_SUCCESS);

    			}
    			else {//third child creates .bakR file which is a back up sorted in reverse alphabetical order. 
        			vector<string> tokens;
				string content;
				string tmp;
				ifstream file(existingFileName.c_str());
				if (file.is_open()){
					while(!file.eof()){
						getline(file,tmp);
						content.append(tmp);
					}
					file.close();
				}

				stringstream text(content);
				string str;
				while(getline(text,str,' ')){
					tokens.push_back(str);
				}

    				string tmpStr;
    				bool swapped = true;
    				int z = 0; 
    				while(swapped){
        				swapped = false;
         			 	z++;
        				for(int v = 0; v < tokens.size() - z; ++v){
        					if(tokens[v] > tokens[v + 1]){
                	       		tmpStr = tokens[v];
       				       		tokens[v] = tokens[v+1];
                       			tokens[v+1] = tmpStr;
                        		swapped = true;
        						}//end if
        					}//end For	
     				}//end W
				
				ofstream reFile(revesedFile.c_str(),ios::binary);
				for(int i = tokens.size();i!=0;i--){
					
					reFile << tokens[i-1] << " ";
					
				}
				reFile.close();
				file.close();
				readfile.close();
				exit(EXIT_SUCCESS);

    			}

		}
		else
			cout << "No such file" << endl;
		

	} // end choice==1 (existing file editing)
	else if(choice == "2"){  //write to new file
		
		string choice3; //Write to beginning of file, starting from a specific byte,
				//or starting at the end of the new file.
		cout << "----------------------------------------" << endl;
		cout << "What would you like to name your "
			<<"new file to which you will write?" << endl;
		cin >> newFile;
		string sortedFile = newFile;
		string revesedFile = newFile;
		string newFileBackUp = newFile;
		newFileBackUp.append(".bak");
		sortedFile.append(".bakS");
		revesedFile.append(".bakR"); //names for back up files

		cout << "Where would you like to begin writing?" << endl;
		cout << "1. Beginning of file" << endl;
		cout << "2. Specific byte" << endl;
		cout << "0. Back to previous menu" << endl;
		cin >> choice3;	
		if(choice3 =="1"){ //Write to beginning of new file	
			string toBeWritten;
			ofstream tmpFile(newFile.c_str(),ios::binary);
			cout << "Please type whatever content you wish" 
				<<"to write followed by pressing the enter key." << endl;
			

			cin.ignore();
			getline(cin, toBeWritten);
			

			tmpFile << toBeWritten;
			tmpFile.close();		
			out = false;
		}	
		if(choice3 =="2"){ //write to specific byte in new file	
			string toBeWritten;
			int num;
			ofstream tmpFile(newFile.c_str(),ios::binary);
			cout << "Enter the specific bytes to start" << endl;	
			cin >> num;

			for(int i=1;i<=num; i++ ){
				tmpFile << " ";	
			}
			
			cout << "Please type whatever content you wish" 
				<<"to write followed by pressing the enter key." << endl;
			cin.ignore();
			getline(cin, toBeWritten);
			tmpFile << toBeWritten;
			tmpFile.close();
			out = false;			
		}
		if(choice3 == "0"){ //go to previous menu
			continue;
		}
		
			pid_t pid1 = fork();
			pid_t pid2 = fork();
			if (pid1<0 && pid2 <0){
				cout << "fork() failed" << endl;
				exit(EXIT_FAILURE);
			}
			else if (pid1 > 0 && pid2 > 0) { // parent
       				wait(&status);
				exit(EXIT_SUCCESS);
   			}
  			else if (pid1 == 0 && pid2 > 0){//first child makes .bak file
        				ifstream readfile(newFile.c_str(), ios::binary);
				if(readfile.is_open()){
					ofstream backupFile(newFileBackUp.c_str(), ios::binary);
					backupFile << readfile.rdbuf();
					backupFile.close();
					readfile.close();
					exit(EXIT_SUCCESS);
				}

    			}
    			else if (pid1 > 0 && pid2 == 0){//second child creates .bakS representing an alphabetically sorted back up file
        			vector<string> tokens;
				string content;
				string tmp;
				ifstream file(newFile.c_str());
				if (file.is_open()){
					while(!file.eof()){
						getline(file,tmp);
						content.append(tmp);
					}
					file.close();
				}

				stringstream text(content);
				string str;
				while(getline(text,str,' ')){
					tokens.push_back(str);
				}

    				string tmpStr;
    				bool swapped = true;
    				int z = 0; 
    				while(swapped){
        					swapped = false;
         			 	z++;
        					for(int v = 0; v < tokens.size() - z; ++v){
	
        						if(tokens[v] > tokens[v + 1]){
                 				       		tmpStr = tokens[v];
                 				       		tokens[v] = tokens[v+1];
                       					tokens[v+1] = tmpStr;
                        					swapped = true;

        						}//end if
        					}//end For	
     				}//end W

				ofstream sortFile(sortedFile.c_str(),ios::binary);
     				for(int j = 0; j < tokens.size(); ++j){
					
					sortFile << tokens[j]<<" ";
     				}
				sortFile.close();
				file.close();
				exit(EXIT_SUCCESS);

    			}
    			else {//third child creates .bakR which is a reverse alphabetically sorted back up file.
        			vector<string> tokens;
				string content;
				string tmp;
				ifstream file(newFile.c_str());
				if (file.is_open()){
					while(!file.eof()){
						getline(file,tmp);
						content.append(tmp);
					}
					file.close();
				}

				stringstream text(content);
				string str;
				while(getline(text,str,' ')){
					tokens.push_back(str);
				}

    				string tmpStr;
    				bool swapped = true;
    				int z = 0; 
    				while(swapped){
        					swapped = false;
         			 	z++;
        					for(int v = 0; v < tokens.size() - z; ++v){
	
        						if(tokens[v] > tokens[v + 1]){
                 				       		tmpStr = tokens[v];
                 				       		tokens[v] = tokens[v+1];
                       					tokens[v+1] = tmpStr;
                        					swapped = true;

        						}//end if
        					}//end For	
     				}//end W
				
				ofstream reFile(revesedFile.c_str(),ios::binary);
				for(int i = tokens.size();i!=0;i--){
					
					reFile << tokens[i-1] << " ";
					
				}
				reFile.close();
				file.close();
				exit(EXIT_SUCCESS);

    			}
	
			
	}//end editing existing file 
	else if(choice == "0"){ //brings us back to main menu
		out = false;
		break;
	}
	else {
		cout << "Enter valid number " << endl;
		continue;
	}
	}//end outter while 
}// end function 
