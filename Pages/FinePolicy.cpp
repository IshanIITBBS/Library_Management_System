#include <iostream>
#include <string>
#include "../my_functions.h"
#include "../my_classes.h"
#include <conio.h>

using namespace std;

void FinePolicy(Users* admin)
{
        system("cls") ;
        cout<<"\n==============================\n";
        cout<<"   Library Management System\n";
        cout<<"==============================\n";

        cout << "\n===== Define Fine Policy =====\n";

        int n ;

        cout << "Enter number of fine rules / Enter -1 to go to previous Page : ";
        cin >> n;
        
        if(n<=0)
        {
            BorrowManage(admin) ;
            return ;
        }
          
        admin->DeleteFinePolicy()  ;
        for(int i=0;i<n;i++)
        {
            int day , fine ;

            cout<<"Enter the number of days after which the rule "<<i<<" is applied : " ;
            cin>>day ;
            cout<<"Enter fine per day for rule "<<i<<" : " ;
            cin>>fine ;
            admin->addFineRule(day,fine) ;
        }

        cout<<"Fine Policy Updated ! " ;
        getch() ;
        BorrowManage(admin) ;
}