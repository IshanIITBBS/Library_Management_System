#include <iostream>
#include <conio.h>
#include <string>
#include "../my_classes.h"
#include "../my_functions.h"

using namespace std;

void UserHome(Users* user) {
        int choice;
        system("cls"); // clear screen
        cout << "\n=====================================\n";
        cout << "        Library Management System\n";
        cout << "=====================================\n";
        cout << "Logged in as: " << user->getMail() << " (User)\n";
        cout << "=====================================\n\n";

        cout << "1. View Books\n";
        cout << "2. Request a Book\n";
        cout << "3. See the Request's Status\n";
        cout << "4. Return a Book\n";
        cout << "5. My Profile/View My Issued Books\n";
        cout << "6. Change Password\n";
        cout << "7. Logout\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        vector<Books> v; 
        switch (choice) {
            case 1:
                v = Books::getAllBooks() ;
                ShowBooks(v,user) ;
                break;
            case 2:
                RequestBook(user) ;
                break;
            case 3:
                RequestStatus(user) ;
                getch();
                break;
            case 4:
                ReturnBook(user) ;
                break;
            case 5:
                cout << "Return Book selected.\n";
                // Implement ReturnBook(user)
                getch();
                break;
            case 6:
                cout << "View Issued Books selected.\n";
                // Implement ViewIssuedBooks(user)
                getch();
                break;
            case 7:
                cout << "Logging out...\n";
                getch();
                StartUp() ;
                return; // Exit UserHome
            default:
                cout << "Invalid choice. Try again.\n";
                getch();
                UserHome(user) ;
        }
    
};

