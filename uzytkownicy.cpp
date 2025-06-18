#include <iostream>
#include <fstream>
#include "uzytkownicy.hpp"

using namespace std;
//Klasa Account i jej konstruktoyr
Account::Account() : login(""), password(""), role("user") {}

Account::Account(string n, string p) : login(n), password(p), role("user")  {}

Account::Account(string n, string p, string r) : login(n), password(p), role(r) {}

Account::~Account() {}

void Account::SetLogin(string log)
{
    login = log;
}


string Account::GetLogin()
{
    return login;
}

void Account::SetPassword(string pass)
{
    password = pass;
}

string Account::GetPassword()
{
    return password;
}

void Account::SetRole(string rol)
{
    role = rol;
}

string Account::GetRole()
{
    return role;
}

void Account::insert_into_csv()
{
    fstream file;
    file.open("users.csv", ios::app);
    if(!file) // kontorla bledu na wypadek blednego otwarcia pliku
    {
        cout << "Plik nie zostal poprawnie otwarty" << endl;
    }

    file << login << "," << password << "," << role << endl;
    file.close();
}

void Account::display()
{
    cout << "Login: " << login << endl;
    cout << "Haslo: " << password << endl;
    cout << "Rola: " << role << endl;
}



//=======================================================================

//KLasa admin

/*Admin::Admin(string n, string p)
{
    user_name = n;
    password = p;
}

Admin::~Admin() {}

void Admin::przedstaw()
{
    cout << user_name << endl << password << endl;
}
*/
