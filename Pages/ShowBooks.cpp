#include <iostream>
#include "../sqlite3.h"
#include <string>
#include<vector>
#include "../my_functions.h"
#include "../my_classes.h"
#include <conio.h>
#include <algorithm>


using namespace std;

 static bool comp(Books& a, Books&b)
 {
     return a.name<b.name ;
 }

    // Page for showing books
    void ShowBooks(vector<Books>&v,Users*user) {
        system("cls") ;
        int choice;
        while (true) {
            system("cls"); // clear screen
            cout << "\n==============================\n";
            cout << "       Show  Books\n";
            cout << "==============================\n";
           
              
            for(int i=0;i<v.size();i++)
            {
                 cout<<i+1<<". "<<v[i].name<<endl;
                 cout<<"      Author : "<<v[i].author<<endl ;
                 cout<<"      Book_id : "<<v[i].id<<endl;
                 cout<<"      Price : "<<v[i].price<<endl ;
                 cout<<"      Copies Available : "<<v[i].copies<<endl ;
                 cout<<"      Description : "<<v[i].description<<endl ;
                 cout<<"      Genres :  "<<v[i].genres<<endl ;
                 cout<<endl<<endl ;
            }

            

            cout << "\n==============================\n";
            cout << "1. Filter by Name\n";
            cout << "2. Filter by Genre\n";
            cout << "3. Sort by Name\n";
            cout << "4. Filter by Author\n";
            cout << "5. Back to Previous Menu\n";
            cout << "==============================\n";
            cout << "Enter your choice: ";
            cin >> choice;
             cin.ignore() ;
            string book_name , genre_name,author_name ;

            switch (choice) {
                case 1:
                    cout<<"Enter Book Name : " ;
                    getline(cin,book_name) ;
                    v = Books::FilterByName(book_name) ;
                    ShowBooks(v,user) ;
                    break;
                case 2:
                    cout<<"Enter Genre Name : " ;
                    getline(cin,genre_name) ;
                    v = Books::FilterByGenre(genre_name) ;
                    ShowBooks(v,user) ;
                    break;
                case 3:
                    sort(v.begin(),v.end(),comp) ;
                    ShowBooks(v,user) ;
                    break;
                 case 4:
                    cout<<"Enter Author Name : " ;
                    getline(cin,author_name) ;
                    v = Books::FilterByAuthor(author_name) ;
                    ShowBooks(v,user) ;
                case 5:
                     if(user->isadmin()) { BookManage(user) ; }
                     else { UserHome(user) ; } 
                    return; // exit this page
                default:
                    cout << "\nInvalid choice. Try again.\n";
                    getch() ;
                    ShowBooks(v,user) ;
            }
        }
    }

