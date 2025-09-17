#include <iostream>
#include "../my_classes.h"
#include  "../my_functions.h"
#include "../sqlite3.h"
#include <string>

using namespace std ;

Admin::Admin(int a,string s1,string s2,bool b):Users(a,s1,s2,b)
{
  
}


static int callback(void* data, int argc, char** argv, char** colName) {

    cout<<"Request_id : "<<argv[0]<<",  Book_Id : "<<argv[1]<<
    ",  User_id : "<<argv[2]<<",   Copies : "<<argv[3]<<
    ",  Request_Time : "<<argv[4]<<endl<<endl; 
    return 0 ;
}


void Admin::getAllRequests(Users* user)
{
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = "SELECT * FROM Requests WHERE STATUS = 0 ORDER BY TIME" ;
      
    vector<string> reqs;
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
}






static int bringrequest(void* data, int argc, char** argv, char** colName) {
    vector<string>* v = static_cast<vector<string>*>(data);
    for(int i=0;i<argc;i++)
    {
        v->push_back(argv[i]) ;
    }
    return 0 ;
}

static int checkcopies(void* data, int argc, char** argv, char** colName) {
    int* x = static_cast<int*>(data);
    *x = stoi(argv[0]) ;
    return 0 ;
}


void Admin :: issueBook(int request_id)
{
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
     
    vector<string> req ;
    string sql = "SELECT * FROM Requests WHERE id = '"+to_string(request_id)+"' " ;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), bringrequest, &req, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
    
    if(req.empty() || stoi(req[5])!=0)
    {
        cout<<"INVALID ID";
        return  ;
    }

    int available_copies=-1;
    sql = "SELECT Copies FROM Books WHERE id = '"+req[1]+"' " ;
    errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(), checkcopies , &available_copies, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
    

    if(available_copies<stoi(req[3]))
    {
        UpdateRequestlog(request_id,0) ;
        cout<<"INVALID REQUEST \n" ;
        return  ;
    }
    
    int rem_copies = available_copies-stoi(req[3]) ;
    
    //cout<<rem_copies<<" "<<available_copies<<" "<<stoi(req[3])<<endl ;
    sql = "UPDATE Books SET Copies = '"+to_string(rem_copies)+"' WHERE id = '"+req[1]+"' " ;
    errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
    

    string time = getCurrentDateTime() ;
    sql = "INSERT INTO BookAssignments(Book_id,User_id,Copies,Time)"
          " VALUES('" + req[1] + "', '" +req[2]+ "' , '"+req[3]+"' , '"+time+"');" ;
    errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
   
    UpdateRequestlog(request_id,1) ;
    cout<<"REQUEST APPROVED\n" ;

}




void Admin :: DeleteRequest(int req_id)
{
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    string sql = "DELETE FROM Requests WHERE id = '"+to_string(req_id)+"'  ; " ;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0 , 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
}


void Admin:: UpdateRequestlog(int req_id, bool approved)
{

    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
     
    int status = approved?1:2 ;

    string sql = "UPDATE Requests SET STATUS='"+to_string(status)+"' " 
                  " WHERE id = '"+to_string(req_id)+"' " ;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
}



void Admin::DeleteFinePolicy()
{
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
     
    string sql = "DELETE FROM FinePolicy" ;
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0,0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
}


void Admin::addFineRule(int day,int fine)
{
    sqlite3* db;
    int exit_code = sqlite3_open("library.db", &db);
    if (exit_code) {
        cout << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return;
    }
     
    string sql = "INSERT INTO FinePolicy(Day,Fine)"
                 "VALUES('"+to_string(day)+"','"+to_string(fine)+"')" ;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0,0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "\nSQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } 
}