/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment 3
a3.cpp

This class uses threads to implement the functionality of a timer.
The user may enter the number of seconds he/she wants the timer to count down from, or not, and the default 25 second timer will run.
The threads communicate by a signal and will terminate when the signal is invoked.
*/
#include"a3.h"

using namespace std;
pthread_t tmp_thread;


void signalhandler(int sig){ // if signal() gets error, print error message.  
	cout << "signal error" << endl;
	exit(sig);
}


void *signal(void* num){
	int tmp = *(int*)num; 
	signal(SIGINT,signalhandler);	// register a SIGINT signal, if get error call handler
	sleep(tmp);
	pthread_cancel(tmp_thread);
	cout << "BEEP BEEP! " << tmp << " seconds are up!" << endl;
	pthread_exit(NULL);

}

void *countdown(void* num){
    int tmp = *(int*) num;
    tmp_thread = pthread_self();
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    for(long i = 0; i < tmp; i++){// countdown the time 
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 80,"%H:%M:%S", timeinfo);
        cout << buffer << endl;
        sleep(1);	
    }
    raise(SIGINT);//get signal from signal function and exit 

}



int main(int argc, char *argv[]) {
    pthread_t thread1,thread2;
    if(argc > 2){// when command line is more than two, print error message. 
        cout << "Invalid input, please try again." << endl;
    }

    if (argc == 2 && *argv[1] == '0'){	// if enter 0 as input, print time is up
   	int sec =0; 
	cout << "BEEP BEEP! " << sec << " seconds are up!" << endl;

    }	

    if(argc == 2 && *argv[1] !='0'  ){// if enter is not 0 and only two command line.
        int sec = (int) strtol(argv[1], NULL, 10);  //number of seconds(base 10) 
        if (sec == 0){
            printf("ERROR! Expected integer argument.");
            return 1;
        }
        else{ 	
	    pthread_create(&thread1,NULL,countdown,&sec);
            pthread_create(&thread2,NULL,signal,&sec);
    	    pthread_join(thread1,NULL);
    	    pthread_join(thread2,NULL);
	}
    }

    if(argc == 1){	// if command line is one, default sec is 25 sec.
        int sec =25;
	pthread_create(&thread1,NULL,countdown,&sec);
	pthread_create(&thread2,NULL,signal,&sec);
        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);
    }
    return 0; 
}
