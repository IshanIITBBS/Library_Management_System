// a.h
#include "my_classes.h"
#include<iostream>
#include<vector>
#include <chrono>
#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

// Function declaration (prototype)



void SignUpPage() ;
void StartUp() ;
void LoginPage() ;
void AdminHome(Users*) ;
void BookManage(Users*) ;
void AddBook(Users*) ;
void ShowBooks(vector<Books>&v,Users* user) ;
void UserHome(Users*) ;
void RequestBook(Users*) ;
void BorrowManage(Users*) ;
void IssueBook(Users*) ;
void RequestStatus(Users*) ;
void FinePolicy(Users*) ;
void ReturnBook(Users*) ;
string getCurrentDateTime() ;



#endif
