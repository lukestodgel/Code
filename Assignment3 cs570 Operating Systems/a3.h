/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment 3
a3.h

Header file for a3.cpp.
*/
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <cstring>
#include <cstddef>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string>

void signalhandler(int);
void *signal(void* );
void *countdown(void* );
