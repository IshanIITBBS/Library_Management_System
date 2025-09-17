#include <iostream>
#include <string>
#include "../my_functions.h"
#include "../my_classes.h"

using namespace std;

    void BorrowManage(Users* admin) {
        system("cls") ;
        cout<<"\n==============================\n";
        cout<<"   Library Management System\n";
        cout<<"==============================\n";

        int choice;
            cout << "\n===== Borrow & Return Management =====\n\n";
            cout << "1. Issue Book to a User\n";
            cout << "2. Return Book\n";
            cout << "3. View Issued Books \n";
            cout << "4. Create/Change  Fine policy  \n";
            cout << "0. Back to Admin Home\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    IssueBook(admin) ;
                    break;
                case 2:
                    //returnBook();
                    break;
                case 3:
                    //viewIssuedBooksAll();
                    break;
                case 4:
                     FinePolicy(admin) ;
                    break ;
                case 0:
                    AdminHome(admin) ;
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }
    }

//     // Function to issue book
//     void issueBook() {
//         int userId, bookId, copies;
//         cout << "\n--- Issue Book ---\n";
//         cout << "Enter User ID: ";
//         cin >> userId;
//         cout << "Enter Book ID: ";
//         cin >> bookId;
//         cout << "Enter Number of Copies: ";
//         cin >> copies;

//         // TODO: Implement SQL logic
//         cout << "Book with ID " << bookId << " issued to User " << userId 
//              << " (" << copies << " copies).\n";
//     }

//     // Function to return book
//     void returnBook() {
//         int userId, bookId;
//         cout << "\n--- Return Book ---\n";
//         cout << "Enter User ID: ";
//         cin >> userId;
//         cout << "Enter Book ID: ";
//         cin >> bookId;

//         // TODO: Implement SQL logic
//         cout << "Book with ID " << bookId << " returned by User " << userId << ".\n";
//     }

//     // Function to view all issued books
//     void viewIssuedBooksAll() {
//         cout << "\n--- All Issued Books ---\n";
//         // TODO: Implement SQL logic
//         cout << "(Display all currently issued books here)\n";
//     }

//     // Function to view issued books of a specific user
//     void viewIssuedBooksByUser() {
//         int userId;
//         cout << "\n--- Issued Books by User ---\n";
//         cout << "Enter User ID: ";
//         cin >> userId;

//         // TODO: Implement SQL logic
//         cout << "(Display books issued to User " << userId << " here)\n";
//     }

