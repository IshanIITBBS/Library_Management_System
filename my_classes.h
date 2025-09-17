#ifndef MYCLASS_H
#define MYCLASS_H
#include <iostream>
#include<vector>

using namespace std ;

class Users{
    protected: 
       int id ;
       string email ;
       string password ;
       bool isAdmin ;
    public :
    Users(int,string,string,bool) ;
    Users() ; 
    string getMail() ;
    bool isadmin()  ;
    int getId();
    virtual void MakeRequest(int book_id, int user_id){} ;
    virtual void getAllRequests(Users*user){} ;
    virtual void issueBook(int){} ;
    virtual void DeleteRequest(int){} ;
    virtual void UpdateRequestlog(int,bool){} ;
    virtual void DeleteFinePolicy(){} ;
    virtual void addFineRule(int,int){} ;
    virtual void returnBook(int){} ;
    virtual void ShowIssuedBooks(){} ;
};


class Admin : public Users{
        public:
        Admin(int,string,string,bool) ;
        void getAllRequests(Users*user) ;
        void issueBook(int) ;
        void DeleteRequest(int) ;
        void UpdateRequestlog(int,bool) ;
        void DeleteFinePolicy() ;
        void addFineRule(int,int) ;
} ;

class Books;

class Books{
     public :
      int id = -1 ;
      string name ;
      string author ;
      int price ;
      int copies ;
      string description ;
      string genres ;
      Books(){} ;
      Books(string name,string author,int price, int copies, string description) ;
      Books(int id,string name,string author,int price, int copies, string description) ;
      void addbook() ;
      void addgenres(vector<string>&genres) ;
      static vector<Books> getAllBooks();
      static vector<Books> FilterByGenre(string name);
      static vector<Books> FilterByName(string name);
      static vector<Books> FilterByAuthor(string name) ;
};


class Customer : public Users{
    public:
    Customer(int,string,string,bool)  ;
    void MakeRequest(int book_id,int numcopies) ;
    void getAllRequests(Users*user) ;
    void returnBook(int) ;
    void ShowIssuedBooks() ;
};

#endif