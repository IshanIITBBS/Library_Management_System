#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../my_classes.h"
#include "../my_functions.h"
#include <conio.h>
#include <iostream>

using namespace std ;



void BookManage(Users* admin) {
    system("cls");
    string email = admin->getMail() ;
    string role = "Admin" ;
    int choice;
        cout<<"\n==============================\n";
        cout<<"   Library Management System\n";
        cout<<"==============================\n";

        printf("------------------------------\n");
        printf("1. Add Book\n");
        printf("2. Edit Book\n");
        printf("3. Delete Book\n");
        printf("4. View All Books\n");
        printf("5. Back to Home\n");
        printf("==============================\n");
        printf("Enter choice: ");
        cin>>choice ;
        vector<Books> v ;
        switch (choice) {
            case 1:
                AddBook(admin) ;
                break;
            case 2:
               // userManagement();
                break;
            case 3:
                 //BorrowReturnManagement() ;
                 break ;
            case 4:
                 v = Books::getAllBooks() ;
                 ShowBooks(v,admin);
                break;
            case 5:
                AdminHome(admin) ;
                return ;
            default:
                printf("\nInvalid choice! Try again.\n");
                getch() ;
                BookManage(admin) ;
                return ;
    }
    
}


