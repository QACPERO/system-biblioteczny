#ifndef UZYTKOWNICY_HPP
#define UZYTKOWNICY_HPP

#include <iostream>

using namespace std;



class Account
{
private:
    string login;
    string password;
    string role;

public:
    Account();
    Account(string, string);
    Account(string n, string p, string r);

    void SetLogin(string log);
    string GetLogin();

    void SetPassword(string pass);
    string GetPassword();

    void SetRole(string rol);
    string GetRole();

    void insert_into_csv();

    void display();

    ~Account();

};




/*
//klasa z typem uzytkowniaka najwyzszego dostepu
class Admin : public Account
{
public:
    Admin(string, string);
    void przedstaw();

    ~Admin();
};


//dostep dla pracownika
class Employee : public Account
{
public:
    Employee(string, string);
    ~Employee();
};


//dostep zwyklego uzytkownika
class User : public Account
{
public:
    User(string, string);
    ~User();
};
*/

#endif // UZYTKOWNICY_HPP
