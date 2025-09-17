#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../my_classes.h"
#include "../my_functions.h"
#include <conio.h>
#include <iostream>

using namespace std ;



void AdminHome(Users* admin) {
    system("cls");
    string email = admin->getMail() ;
    string role = "Admin" ;
    int choice;
    while (1) {
        cout<<"\n==============================\n";
        cout<<"   Library Management System\n";
        cout<<"==============================\n";
        cout<<"Admin Profile:\n";
        cout<<"Email:"<< email<<"\n";
        cout<<"Role : "<<role<<"\n";
        printf("------------------------------\n");
        printf("1. Book Management\n");
        printf("2. User Management\n");
        printf("3. Borrow & Return Management\n");
        printf("4. Reports & Analytics\n");
        printf("5. Logout\n");
        printf("==============================\n");
        printf("Enter choice: ");
        cin>>choice ;
        switch (choice) {
            case 1:
                BookManage(admin) ;
                break;
            case 2:
               // userManagement();
                break;
            case 3:
                 BorrowManage(admin);
                 break ;
            case 4:
                //reportsAndAnalytics();
                break;
            case 5:
                printf("\nLogging out...\n");
                getch() ;
                StartUp() ;
                return ;
            default:
                printf("\nInvalid choice! Try again.\n");
                getch() ;
                AdminHome(admin) ;
        }
    }
}


