#include <iostream>
#include <string>
#include <conio.h>   
#include "../my_functions.h"
#include"../sqlite3.h"
using namespace std;

// Function to take password input (with masking using '*')
string getPassword(const string &prompt) {
    string password;
    char ch;
    cout << prompt;
    while (true) {
        ch = getch(); // read key without showing
        if (ch == 13) { // Enter key
            cout << endl;
            break;
        } else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // erase last *
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    return password;
}

void SignUpPage() {
    system("cls");
    cout << "=========================================\n";
    cout << "              Signup Page               \n";
    cout << "=========================================\n\n";
    
    cout<<"You have to enter your Email_id and password\n" ;
    cout<<"Enter -1 to go to StartUp page\n\n" ;

    string email, password, confirmPassword;

    cout << "Enter Email ID: ";
    cin >> email;
    
    if(email=="-1") 
    {
          StartUp() ;
          return  ;
    }
    
    password = getPassword("Enter Password: ");
    confirmPassword = getPassword("Confirm Password: ");
     
    if(password=="-1" || confirmPassword=="-1")
    {
        StartUp() ;
        return ;
    }

    if (password != confirmPassword) {
        cout << "\nPasswords do not match. Please try again!\n";
        getch() ;
        SignUpPage() ;
        return ;
    }
    
    sqlite3* db ;
    int exit_code = sqlite3_open("library.db", &db);
    if(exit_code)
    {
        cout<<"Error Occured"<<endl ;
        StartUp();
        return ;
    }
    
    string sql = "INSERT INTO Users (email, password) VALUES('" + email + "', '" + password + "');";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\n SQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "\n Signup Successful! User added to DB.\n";
    }

    cout << "\nPress any key to return to Home...";
    getch() ;
    StartUp() ;
} ;










