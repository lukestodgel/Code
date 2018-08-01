Kyle Zou cssc1069, Allen Chang cssc1068, Luke Stodgel cssc1080
CS570 Summer 2018
Assignment 3 Timer control program
README.txt

Please look in cssc1069 for the full working program.

File manifest  
	a3.cpp, a3.h, Makefile, README.txt

Compile instructions 
	If you type make, the makefile will create .o files for all of the .cpp files, and will create an executable file named tevent. If you then type tevent the program will execute. 

Operating instructions
	Create the executable file by typing make, then call tevent and the second command line argument should be number of seconds the program will run for. If no second argument is provided the program will run for the default 25 seconds.

List/description of any extra features/algorithms/functionality you included which were not required	
	We used some functions from the <string>, <iostream>, <stdio.h>, <signal.h>, <stdlib.h>, <cstring>, <unistd.h>, <iostream>, <cstddef>, <time.h> class function libraries. That's about it!	

List/description of all known deficiencies or bugs
	None exist. We tested our program for several hours.

Lessons learned
	We learned more about how to create and work with pthreads. We also learned how to use signals to control thread termination.