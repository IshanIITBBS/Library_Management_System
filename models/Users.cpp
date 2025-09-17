#include <iostream>
#include "../my_classes.h"

using namespace std ;

string Users :: getMail(){
    return this->email;
}

bool Users :: isadmin()
{
    return this->isAdmin ;
}

int Users :: getId(){
    return this->id ;
}

Users :: Users(int id,string email , string password, bool isAdmin)
{
    this->email = email ;
    this->password = password ;
    this->id = id ;
    this->isAdmin = isAdmin ;
}




