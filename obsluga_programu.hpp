#include <iostream>
#include "uzytkownicy.hpp"

using namespace std;

void program(Account* &current_user);           //inicjalizacja programu
void user(Account* &current_user);              //oblsuga dostepu user
void admin(Account* &current_user);             // obsulga dostepu admin
void employee(Account* &current_user);          //obsluga dostepu employee
void app_lib_items(Account* &current_user);     // dodaje nowa pozycje do zasobow bibliotecznych
void user_loan();                               //wyporzyczanie przedmotu przez uztykownika
void user_return();                             // zwrot wyporzyczenia przez uzytkownika
void borrowed_items(Account* &current_user);
//void check_item(const string &id);

