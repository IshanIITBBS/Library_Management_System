#include <iostream>
#include "../my_functions.h"
#include "../my_classes.h"
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "../sqlite3.h"
#include <sstream>
#include <iomanip>

using namespace std ;

Customer :: Customer(int id, string email , string password, bool isAdmin)
            :Users(id,email,password,isAdmin)
{
     
}


string getCurrentDateTime() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now_time));
    return string(buf);
}


void Customer :: MakeRequest(int book_id, int numcopies)
{
    string requestTime = getCurrentDateTime();

    // Save to DB
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = "INSERT INTO Requests(User_id, Book_id, Copies, Time) VALUES(" +
                 to_string(id) + ", " +
                 to_string(book_id) + ", " +
                 to_string(numcopies) + ", '" +
                 requestTime + "');";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "\nBook request submitted successfully!\n";
        cout << "Request Time: " << requestTime << endl;
    }

    sqlite3_close(db);
} 


static int callback(void* data, int argc, char** argv, char** colName) {
    string apv  ;
    int status = stoi(argv[5]) ;
    if(status==0) {apv="PENDING"; }
    else if(status == 1) {apv="APPROVED" ;}
    else {apv = "REJECTED" ; }

    cout<<"Request_id : "<<argv[0]<<",  Book_Id : "<<argv[1]<<
    ",  User_id : "<<argv[2]<<",   Copies : "<<argv[3]<<
    ",  Request_Time : "<<argv[4]<<
    "  STATUS : "<<apv<<endl<<endl; 
    return 0 ;
}


void Customer:: getAllRequests(Users* user)
{
     // Save to DB
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    string sql = "SELECT * FROM Requests WHERE User_id = '"+to_string(id)+"' ORDER BY TIME DESC" ;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
    
}




int daysBetween(const string& date1, const string& date2) {
    tm tm1 = {}, tm2 = {};
    istringstream ss1(date1), ss2(date2);

    ss1 >> get_time(&tm1, "%Y-%m-%d %H:%M:%S");
    ss2 >> get_time(&tm2, "%Y-%m-%d %H:%M:%S");

    auto tp1 = chrono::system_clock::from_time_t(mktime(&tm1));
    auto tp2 = chrono::system_clock::from_time_t(mktime(&tm2));

    auto diff = chrono::duration_cast<chrono::hours>(tp2 - tp1).count();

    return diff / 24; // difference in days
}


static int bringbooks(void* data, int argc, char** argv, char** colName) {
    vector<string>* v = static_cast<vector<string>*>(data); 
    for(int i=0;i<argc;i++)
    {
        v->push_back(argv[i]) ;
    }
    return 0 ;
}

static int bringpolicy(void* data, int argc, char** argv, char** colName) {
    vector<pair<int,int>>* v = static_cast<vector<pair<int,int>>*>(data); 
     v->push_back({stoi(argv[1]),stoi(argv[2])}) ;
    return 0 ;
}


int calcFine(vector<string>&v,vector<pair<int,int>>&fp)
{
    string time = getCurrentDateTime() ;
    int days = daysBetween(v[4],time) ;
    int fine = 0 ;
     for(int i=0;i<fp.size();i++)
    {
        if(fp[i].first>days) { break ;}
        int slab = (i+1 == fp.size())?(days+1-fp[i].first): (min(fp[i+1].first,days+1)-fp[i].first) ;
        fine += slab*fp[i].second*stoi(v[3]) ;
    }

    return fine ;
}

void Customer::returnBook(int aid)
{
      // Save to DB
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    vector<string> v ;
    string sql = "SELECT * FROM BookAssignments WHERE id = '"+to_string(aid)+"' " 
                 "AND User_id = '"+to_string(id)+"'"  ;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(),bringbooks,&v, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
     
    if(v.empty())
    {
        cout<<"INVALID ID\n" ;
        return ;
    }
    
    vector<pair<int,int>> fp ;
    sql = "SELECT * FROM FinePolicy ORDER BY DAY" ;
    errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(),bringpolicy,&fp, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 

     
    int fine = calcFine(v,fp) ;
   
    cout<<"FINE DUE : "<<fine<<endl ;

    cout<<"PAY FINE BY PRESSING ENTER\n" ;
    getch() ;
    

    sql = "UPDATE Books SET Copies = Copies + '"+v[3]+"' WHERE id = '"+v[1]+"'"  ; 

    errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(),bringbooks,&v, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
     
    sql = "DELETE FROM BookAssignments WHERE id='"+to_string(aid)+"' "  ; 
    errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(),bringbooks,&v, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
    
    cout<<"BOOKS RETURNED !" ;
}


static int callback3(void* data, int argc, char** argv, char** colName) {
    cout<<"Assignment_id: "<<argv[0]<<",  Book_Id : "<<argv[1]<<
    ",  User_id : "<<argv[2]<<",   Copies : "<<argv[3]<< 
    ",  Borrowed at : "<<argv[4]<<endl<<endl ;
    return 0 ;
}

void Customer :: ShowIssuedBooks()
{
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
    string sql = "SELECT * FROM BookAssignments WHERE User_id = '"+to_string(id)+"'" ;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(),callback3,0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
}