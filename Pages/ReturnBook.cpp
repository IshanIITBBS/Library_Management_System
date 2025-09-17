#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "../sqlite3.h"
#include "../my_classes.h"
#include "../my_functions.h"

using namespace std;



void ReturnBook(Users* user) {
    system("cls");
    int bookId, copies;

    cout << "\n==============================\n";
    cout << "        Return Book \n";
    cout << "==============================\n";
    
    user->ShowIssuedBooks() ;

    cout<<"Note :- Enter -1 to return to previous Page"<<endl ;
    int aid ;
    cout<<"Enter Your Assignment Id : " ;
    cin>>aid ;

    user->returnBook(aid) ;
    getch() ;
    UserHome(user) ;
}
