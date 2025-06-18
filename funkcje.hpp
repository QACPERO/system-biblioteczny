#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include "uzytkownicy.hpp"

void login(Account* &current_user);             // sekwencja logowania
void user_login(Account* &current_user);
void wrong_choise(Account* &current_user);
void new_user(Account* &current_user);          //sekwencja tworzenia nowego uzytkownika
void art();
void clear_consol();                            //czyzszczenie  kosnoli i wywietlanie npisu
bool check_user(Account* &current_user);        //sprawdzanie czy uzytkownik istenije w bazie
bool check_login_in_file(string login);         //sprawdzanie czy login istenije w bazie
bool is_valid_login(const string& login);       //walidacja loginu
string get_current_date();                        //pobieranie aktualnej daty
int remember_id(const string& filename);        //pobieranie najwiekszego id aby uniknac duplikowania
void change_status(string item_id);             //zmiana statusu przedmiotu w pliku na przeciwny (dsotpeny/niedostepny)
void remove_unwanted_lines(const string& filename);
bool is_in_file(const string& filename, const string& login);   // sprawdzadnie czy podana wartosc znandueje sie w podanym pliku
bool is_borrowed(string item_id);
void add_return_date(const string& filename, const string& login, const string& item_id);
string hash_password(const string& input);     // hashowanie hasla
string get_password();
bool is_not_empty(const string& login);
void borrowed_items(const string& current_login, const string& filter_type);
void delete_item(const string &id);
void change_password(Account *&current_user);
void change_access(const string login);
