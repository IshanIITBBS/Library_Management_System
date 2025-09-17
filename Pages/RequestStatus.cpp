#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "../sqlite3.h"
#include "../my_classes.h"
#include "../my_functions.h"

using namespace std;



void RequestStatus(Users* user) {
    system("cls");
    int bookId, copies;

    cout << "\n==============================\n";
    cout << "        Request Status \n";
    cout << "==============================\n\n";

    user->getAllRequests(user) ;
    cout<<"\n Press Enter to Go to Home"<<endl ;
    getch() ;
    UserHome(user) ;
}
