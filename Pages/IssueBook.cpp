#include <iostream>
#include <string>
#include "../my_functions.h"
#include "../my_classes.h"
#include <conio.h>

using namespace std;

    void IssueBook(Users* admin) {
        system("cls") ;

        cout<<"\n==============================\n";
        cout<<"   Library Management System\n";
        cout<<"==============================\n\n";

        admin->getAllRequests(admin) ;
        
        int rid ;
        cout<<"Enter Request Id : " ;
        cin>>rid ;
          
        int choice ;
        cout<<"Choose :-\n";
        cout<<"   TO APPROVE REQUEST : 1\n" ;
        cout<<"   TO REJECT REQUES : 0\n" ;
        cout<<"   TO GO BACK TO PREVIOUS PAGE : -1\n";
        cout<<"Enter choice : ";
        cin>>choice ;

        if(choice==-1)
        {
            BorrowManage(admin) ;
        }
        else if(choice==1)
        {
              admin->issueBook(rid) ;
              getch() ;
              BorrowManage(admin) ;
        }
        else if(choice==0)
        {
             admin->UpdateRequestlog(rid,0) ;
             cout<<"REQUEST REJECTED" ;
             getch() ;
             BorrowManage(admin) ;
        }
        else
        {
            cout<<"INVALID CHOICE" ;
            getch() ;
            BorrowManage(admin) ;
        }

    }



