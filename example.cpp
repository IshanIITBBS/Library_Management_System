#include <iostream>
#include "sqlite3.h"
using namespace std;

int main() {
    sqlite3* db;
    int rc = sqlite3_open("library.db", &db);
    if (rc) {
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Create Users table if not exists
    // const char* sqlCreate = "CREATE TABLE IF NOT EXISTS Users ("
    //                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                         "email TEXT UNIQUE NOT NULL, "
    //                         "password TEXT NOT NULL,"
    //                         "isAdmin BOOLEAN NOT NULL DEFAULT 0);";
    //   const char* sqlCreate = "CREATE TABLE IF NOT EXISTS Books ("
    //                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                         "Name VARCHAR(255), "
    //                         "Author VARCHAR(255),"
    //                         "Price INT,"
    //                         "Copies INT,"
    //                         "Description TEXT);";
    //const char* sqlCreate = "DROP TABLE Requests" ;
    //  const char* sqlCreate = "CREATE TABLE IF NOT EXISTS Genres ("
    //                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                         "Book_id INT,"
    //                         "Name VARCHAR(255),"
    //                         "FOREIGN KEY(Book_id) REFERENCES Books(id) ON DELETE CASCADE);"; 
    //   const char* sqlCreate = "CREATE TABLE IF NOT EXISTS Requests ("
    //                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                         "Book_id INT ,"
    //                         "User_id INT ,"
    //                         "Copies INT ,"
    //                         "Time DATETIME, "
    //                         "FOREIGN KEY(Book_id) REFERENCES Books(id) ON DELETE CASCADE, "
    //                         "FOREIGN KEY(User_id) REFERENCES Users(id) ON DELETE CASCADE);" ; 

    //   const char* sqlCreate = "CREATE TABLE IF NOT EXISTS BookAssignments ("
    //                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                         "Book_id INT ,"
    //                         "User_id INT ,"
    //                         "Copies INT ,"
    //                         "Time DATETIME, "
    //                         "FOREIGN KEY(Book_id) REFERENCES Books(id) ON DELETE CASCADE, "
    //                         "FOREIGN KEY(User_id) REFERENCES Users(id) ON DELETE CASCADE);" ;

      const char* sqlCreate = "CREATE TABLE IF NOT EXISTS Requests("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "Book_id INT ,"
                            "User_id INT ,"
                            "Copies INT ,"
                            "Time DATETIME, "
                            "STATUS INT DEFAULT 0, "
                            "FOREIGN KEY(Book_id) REFERENCES Books(id) ON DELETE CASCADE, "
                            "FOREIGN KEY(User_id) REFERENCES Users(id) ON DELETE CASCADE);" ;

    //   const char* sqlCreate = "CREATE TABLE IF NOT EXISTS FinePolicy ("
    //                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                         "Day INT,"
    //                         "Fine INT) ;" ;
                
    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sqlCreate, 0, 0, &errMsg);
     if (rc != SQLITE_OK) {
        cout << "\n SQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
    sqlite3_close(db);
    return 0;
}
