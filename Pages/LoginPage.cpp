#include <iostream>
#include <string>
#include "../sqlite3.h"
#include <conio.h>
#include <vector>
#include "../my_functions.h"
#include "../my_classes.h"


using namespace std;

// Helper to check login
static int callback(void* data, int argc, char** argv, char** colName) {
    vector<string>* v = static_cast<vector<string>*>(data);
    for(int i=0;i<argc;i++)
    {
        v->push_back(argv[i]) ;
    }
    return 0;
}

void LoginPage() {
    system("cls");
    cout << "=========================================\n";
    cout << "              Login Page              \n";
    cout << "=========================================\n\n";

    string email, password;
    cout << "Enter Email ID: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

     sqlite3* db  ;
     int exit_code = sqlite3_open("library.db", &db) ; 
     if (exit_code) {
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return ;
    }

    // Prepare SQL SELECT query
    string sql = "SELECT * FROM Users WHERE email='" + email + "' AND password='" + password + "';";

    vector<string> v;
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), callback,&v, &errMsg);
    
    if (rc != SQLITE_OK) {
        cout << "\n SQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
        getch() ;
    } else {
        if (!v.empty()) {
            if(v[3]=="1")
            {
               string s1(v[1]) ;
               string s2(v[2]) ;
               Admin *user = new Admin(stoi(v[0]),s1,s2,stoi(v[3])) ;
               cout << "\n Admin Login Successful! Welcome, " << email << " \n";
               getch();
               AdminHome(user) ;
               return ;
            }
            else
            {
               string s1(v[1]) ;
               string s2(v[2]) ;
               Customer* user = new Customer(stoi(v[0]),s1,s2,stoi(v[3])) ;
               cout << "\n Login Successful! Welcome, " << email << " \n";
               getch() ;
               UserHome(user) ;
            }
        } else {
            cout << "\n Invalid Email or Password!\n";
            getch() ;
            StartUp() ;
        }
    }

}
