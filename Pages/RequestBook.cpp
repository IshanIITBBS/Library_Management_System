#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "../sqlite3.h"
#include "../my_classes.h"
#include "../my_functions.h"

using namespace std;



void RequestBook(Users* user) {
    system("cls");
    int bookId, copies;

    cout << "\n==============================\n";
    cout << "        Request a Book\n";
    cout << "==============================\n\n";

    cout << "Enter Book ID: ";
    cin >> bookId;
    if (bookId <= 0) {
        cout << "Invalid Book ID!\n";
        getch();
        UserHome(user) ;
        return;
    }
    cout << "Enter Number of Copies: ";
    cin >> copies;
    if (copies <= 0) {
        cout << "Invalid number of copies!\n";
        getch();
        UserHome(user) ;
        return;
    }
    
    user->MakeRequest(bookId,copies) ;
    getch() ;
    UserHome(user) ;
}
