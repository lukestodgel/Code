/*
Group Member: Sheng Yu Chang, Hong Zou, Luke Stodgel
cssc1068, cssc1069, cssc1080
CS570 Summer 2018
Assignment 2 Multi-processing file editor
a2.h
*/
#include<iostream>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<vector>
#include<sstream>
#include<cstring>
#include<fstream>
#include<sys/stat.h>
#include<sys/wait.h>

void creating(std::string);
void reading(std::string);
void writing (std::string);
void status(std::string);
void dirListing(std::string);
