#include<iostream>
#include "../my_functions.h"
#include <conio.h>   // for getch() (Windows only)

using namespace std ;




void showStartPage() {
    system("cls"); // clear screen (Windows)
    cout << "=========================================\n";
    cout << "          Welcome to Library         \n";
    cout << "=========================================\n\n";
    cout << "Please choose an option:\n";
    cout << "1. Log In\n";
    cout << "2. Sign Up\n";
    cout << "3. Exit\n";
    cout << "-----------------------------------------\n";
    cout << "Enter your choice: ";
}

void StartUp()
{
    int choice;
    while (true) {
        showStartPage();
        cin >> choice;

        switch (choice) {
            case 1:
                LoginPage() ;
                break;
            case 2:
                SignUpPage() ;
                break;
            case 3:
                cout << "\nExiting... Thank you for visiting\n";
                exit(0);
            default:
                cout << "\nInvalid choice. Try again!\n";
                getch();
        }
    }

    return ;
}