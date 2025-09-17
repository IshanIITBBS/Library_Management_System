#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../my_classes.h"
#include "../my_functions.h"
#include <conio.h>
#include <iostream>
#include<string>
#include<vector>

using namespace std ;



void AddBook(Users* admin) {
    system("cls");
    string email = admin->getMail();
    string role = "Admin";

    cout << "\n==============================\n";
    cout << "   Library Management System\n";
    cout << "==============================\n";

    cout << "---------- ADD A BOOK ----------\n\n";
    cout << "To go back to Previous Page, enter -1 at any prompt\n\n";

    string name, author, desc;
    int price, copies, gennum;

    cin.ignore(); // Clear buffer at start

    cout << "Enter Book Name: ";
    getline(cin, name);
    if (name == "-1") { BookManage(admin); return; }

    cout << "Enter Author Name: ";
    getline(cin, author);
    if (author == "-1") { BookManage(admin); return; }

    cout << "Enter Price: ";
    cin >> price;
    if (price == -1) { BookManage(admin); return; }

    cout << "Enter Copies: ";
    cin >> copies;
    if (copies == -1) { BookManage(admin); return; }

    cin.ignore(); // Clear buffer after int inputs

    cout << "Enter Description: ";
    getline(cin, desc);
    if (desc == "-1") { BookManage(admin); return; }

    cout << "How many genres do you want to assign this book: ";
    cin >> gennum;
    if (gennum < 0 || gennum > 1000000) { BookManage(admin); return; }

    cin.ignore(); // Clear buffer before getline

    vector<string> genres(gennum);
    for (int i = 0; i < gennum; i++) {
        cout << "Enter genre number " << i + 1 << ": ";
        getline(cin, genres[i]);
    }

    Books* book = new Books(name, author, price, copies, desc);
    book->addbook();
    book->addgenres(genres);

    cout << "\nBook Added successfully!\n";
    cin.get(); // Wait for Enter
    BookManage(admin);
    return;
}

