Kyle Zou cssc1069, Allen Chang cssc1068, Luke Stodgel cssc1080
CS570 Summer 2018
Assignment 2 Multi-processing file editor
README.txt

Please look in cssc1069 for the full working program.

File manifest  
	creating.cpp, reading.cpp, writing.cpp, status.cpp, main.cpp, a2.h, Makefile, dirListing.cpp, README.txt

Compile instructions 
	If you type make, the makefile will compile all of the .cpp files, make object files, and will create an executable file named filem. If you then type filem the program will execute. 

Operating instructions
	All you must do is run the make file, and call filem. You will then be able to navigate through the program via its menus.

List/description of any extra features/algorithms/functionality you included which were not required	
	We used many functions from the <stream>, <string>, <iostream>, <stdio>, <sstream>, <sys/stat>, <stdlib.h>, <cstring>, <fstream>, <unistd.h>, <vector> class function libraries. That's about it!	

List/description of all known deficiencies or bugs
	Haven't found one yet. We tested our program for several hours.

Lessons learned
	We learned a lot about file manipulation in this project. Specifically figuring out how to write to a new file, or edit an existing file at a specific location was something everyone in our group learned about. We also learned how to create processes and how to use both the parent and child processes to perform separate tasks.
