#include <iostream>
#include "../my_classes.h"
#include  "../my_functions.h"
#include "../sqlite3.h"
#include <string>
#include <unordered_map>

Books:: Books( string name,string author,int price, int copies, string description)
{
   this->name = name ;
   this->author = author ;
   this->price = price ;
   this->copies = copies ;
   this->description = description ;
}

Books:: Books(int id, string name,string author,int price, int copies, string description)
{
   this->name = name ;
   this->author = author ;
   this->price = price ;
   this->copies = copies ;
   this->description = description ;
   this->id = id ;
}


void Books::addbook()
{
         string p = to_string(price) ;
         string c = to_string(copies) ;
        sqlite3* db  ;
        int exit_code = sqlite3_open("library.db", &db);
        string sqlCreate = "INSERT INTO Books(Name,Author,Price,Copies,Description)"
                         "VALUES('" + name + "', '" + author + "','"  + p +  "', '"  + c +  "'," 
                         "'" + description +"'); " ;
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlCreate.c_str(), 0, 0, &errMsg);
         if (rc != SQLITE_OK) {
            cout << "\n SQL Error: " << errMsg << endl;
            sqlite3_free(errMsg);
        } 
        sqlite3_close(db);
}


static int callback(void* data, int argc, char** argv, char** colName) {
    int* id = static_cast<int*>(data);
    string s(argv[0]) ;
    *(id) = stoi(s) ;
    return 0;
}

void Books :: addgenres(vector<string>&genres)
{
       sqlite3* db  ;
       int exit_code = sqlite3_open("library.db", &db);
        
       int id ;
       string sqlCreate = "SELECT id FROM Books WHERE "
                          "'"+ name +"' == Name AND "
                          "'"+ author +"' == Author " ;
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlCreate.c_str(), callback, &id, &errMsg);
         if (rc != SQLITE_OK) {
            cout << "\n SQL Error: " << errMsg << endl;
            sqlite3_free(errMsg);
        } 

       for(int i=0;i<genres.size();i++)
       {
          string sqlCreate = "INSERT INTO Genres(Book_id,Name)"
                         "VALUES('" + to_string(id) + "', '" + genres[i] + "' ) ";
           char* errMsg = nullptr;
           int rc = sqlite3_exec(db, sqlCreate.c_str(), 0, 0, &errMsg);
            if (rc != SQLITE_OK) {
               cout << "\n SQL Error: " << errMsg << endl;
               sqlite3_free(errMsg);
           } 
       }
       sqlite3_close(db);
}




static int callback2(void* data, int argc, char** argv, char** colName) {
    vector<Books>* v = static_cast<vector<Books>*>(data);

    // Extract values from row
    int id = argv[0] ? stoi(argv[0]) : 0;
    string name = argv[1] ? argv[1] : "";
    string author = argv[2] ? argv[2] : "";
    double price = argv[3] ? stod(argv[3]) : 0.0;
    int copies = argv[4] ? stoi(argv[4]) : 0;
    string description = argv[5] ? argv[5] : "";
    string genres = argv[6] ? argv[6] : "" ;
    // Create Book object
    Books book(id,name, author, price, copies, description);
    book.genres = genres ;
    // Add to vector
    v->push_back(book);
    return 0;
}


vector<Books> Books::getAllBooks()
{
       sqlite3* db  ;
       int exit_code = sqlite3_open("library.db", &db);
        
       vector<Books> v ;
       string sqlCreate = "SELECT b.id, b.Name, b.Author, b.Price, b.Copies, b.Description, "
                       "GROUP_CONCAT(g.Name, ', ') AS genres " 
                       "FROM Books as b INNER JOIN Genres as g ON b.id = g.Book_id "
                       "GROUP BY b.id;";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlCreate.c_str(), callback2, &v, &errMsg);
         if (rc != SQLITE_OK) {
            cout << "\n SQL Error: " << errMsg << endl;
            sqlite3_free(errMsg);
        } 

     
        sqlite3_close(db);
           
        return v;
}

vector<Books> Books::FilterByName(string name)
{
    sqlite3* db  ;
       int exit_code = sqlite3_open("library.db", &db);
        
       vector<Books> v ;
       string sqlCreate = "SELECT b.id, b.Name, b.Author, b.Price, b.Copies, b.Description, "
                       "GROUP_CONCAT(g.Name, ', ') AS genres " 
                       "FROM Books as b INNER JOIN Genres as g ON b.id = g.Book_id "
                       "WHERE b.name LIKE '"+name+"%'"
                       "GROUP BY b.id " ;
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlCreate.c_str(), callback2, &v, &errMsg);
         if (rc != SQLITE_OK) {
            cout << "\n SQL Error: " << errMsg << endl;
            sqlite3_free(errMsg);
        } 

     
        sqlite3_close(db);
           
        return v;
}

vector<Books> Books::FilterByGenre(string name)
{
    sqlite3* db  ;
       int exit_code = sqlite3_open("library.db", &db);
        
       vector<Books> v ;
       string sqlCreate = "SELECT b.id, b.Name, b.Author, b.Price, b.Copies, b.Description, "
                       "GROUP_CONCAT(g.Name, ', ') AS genres " 
                       "FROM Books as b INNER JOIN Genres as g ON b.id = g.Book_id "
                        "WHERE g.Name LIKE '"+name+"%'"
                       "GROUP BY b.id " ;
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlCreate.c_str(), callback2, &v, &errMsg);
         if (rc != SQLITE_OK) {
            cout << "\n SQL Error: " << errMsg << endl;
            sqlite3_free(errMsg);
        } 

        sqlite3_close(db);
           
        return v;
}

vector<Books> Books::FilterByAuthor(string name)
{
    sqlite3* db  ;
       int exit_code = sqlite3_open("library.db", &db);
        
       vector<Books> v ;
       string sqlCreate = "SELECT b.id, b.Name, b.Author, b.Price, b.Copies, b.Description, "
                       "GROUP_CONCAT(g.Name, ', ') AS genres " 
                       "FROM Books as b INNER JOIN Genres as g ON b.id = g.Book_id "
                       "WHERE b.author LIKE '"+name+"%'"
                       "GROUP BY b.id " ;
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlCreate.c_str(), callback2, &v, &errMsg);
         if (rc != SQLITE_OK) {
            cout << "\n SQL Error: " << errMsg << endl;
            sqlite3_free(errMsg);
        } 

     
        sqlite3_close(db);
           
        return v;
}