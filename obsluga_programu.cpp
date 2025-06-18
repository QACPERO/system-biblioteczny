#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "funkcje.hpp"
#include "obsluga_programu.hpp"
#include "obsluga_pliku.hpp"
#include "zasoby.hpp"
#include "loan.hpp"

using namespace std;

void program(Account* &current_user)
{
    if(current_user->GetRole() == "user") user(current_user);
    if(current_user->GetRole() == "admin") admin(current_user);
    if(current_user->GetRole() == "employee") employee(current_user);
}

//==========================================================================================================
//Obsluga dostepu user
//=========================================================================================================


void user(Account* &current_user)
{
    clear_consol();
    bool variable = true;
    while(variable)
    {
        cout << "Wybierz z ponizszych." <<endl;
        cout << "1. Aktualnie wypozyczone przedmioty" << endl;
        cout << "2. Historia wypozyczen" << endl;
        cout << "3. Zmiana hasla" << endl;
        //cout << "4. Usuniecie konta" << endl;
        cout << "0. Wylogowanie" << endl;
        char ch = getch();

        switch(ch)
        {
        case '0':
            clear_consol();
            variable = false;
            //login(current_user);
            break;
        case '1':
            borrowed_items(current_user->GetLogin(), "one_date");
            break;
        case '2':
            borrowed_items(current_user->GetLogin(), "two_dates");
            break;
        case '3':
            change_password(current_user);
            break;
        case '4':
            break;
        default:
            cout << "Wybor spoza listy." << endl;
            break;
        }
    }
 // sprawdzenie akualnej listy wyporzyczonych przedmiotow
 //zmiana hasla
 //usuniecie konta
 //wylogowanie

}




//==========================================================================================================
//Obsluga dostepu bibloekarza
//=========================================================================================================


void employee(Account* &current_user)
{
    clear_consol();
    bool variable = true;
    while(variable)
    {

        cout << "Wybierz z ponizszych."                 << endl;
        cout << "1. Wypozycz"                          << endl;
        cout << "2. Przyjminj zwrot"                    << endl;
        cout << "3. Dodaj do listy zasobow"             << endl;
        cout << "4. Usun z listy zasobow"               << endl;
        //cout << "5. Wyszukaj przedmiot"                 << endl;
        cout << "5. Sprawdz aktualne wpozyczenia uzytkownika"   << endl;
        cout << "6. Sprawdz historie wypozyczen uzytkownika" << endl;
        cout << "7. Zmien haslo"                        << endl;
        cout << "0. Wyloguj"                            << endl;
        char ch = getch();

    switch(ch)
        {
        case '0':
            clear_consol();
            variable = false;
            //login(current_user);
            break;
        case '1':
            user_loan();
            break;
        case '2':
            user_return();
            break;
        case '3':
            app_lib_items(current_user);
            break;
        case '4':
            {
                string id;
                cout << "Podaj id przedmiotu do usuniecia: ";
                cin >> id;
                cout << endl;
                delete_item(id);
                break;
            }
        case '5':
            {
                string user_login;
                cout << "Podaj login uzytkownika: ";
                cin >> user_login;
                if (is_in_file("users.csv", user_login))
                {
                    borrowed_items(user_login, "one_date");

                }
                else
                {
                    cout << "Nie znalezniono uzytkownika" << endl;
                    cout << "Kliknij dowolny przycisk aby kontynuowac" << endl;
                    getch();
                    clear_consol();
                }
                break;
            }

        case '6':
            {
                string user_login;
                cout << "Podaj login uzytkownika: ";
                cin >> user_login;
                if (is_in_file("users.csv", user_login))
                {
                    borrowed_items(user_login, "two_dates");
                }
                else
                {

                    cout << "Nie znalezniono uzytkownika" << endl;
                    cout << "Kliknij dowolny przycisk aby kontynuowac" << endl;
                    getch();
                    clear_consol();
                }
                break;
            }
        case '7':
            change_password(current_user);
            break;
        default:
            clear_consol();
            cout << "Nieprawidlowy wybor." << endl;
            break;
        }
    }

 //usuniecie zasobow
 //wyszukanie gdzie znajduje sie zaso (wsensie u kogo lub czy jest w bibliotece)
 //sprawdzenie wyporzyczen urzytkownika
 //pelna lista zasobow
}

//==========================================================================================================
//Obsluga dostepu admin
//=========================================================================================================


void admin(Account* &current_user)
{
    clear_consol();
    bool variable = true;
    while(variable)
    {
        cout << "1. Zmiana dostepu konta podanego uzytkownika" << endl;
        //cout << "2. Usuniecie urzytkownika" << endl;
        cout << "2. Zmiana hasla" << endl;
        cout << "0. Wyloguj" << endl;
        char ch = getch();

        switch (ch)
        {
        case '1':
            {
                clear_consol();
                string temp_login;
                cout << "Podaj login uzytkownika do zmiany dostepu: ";
                cin >> temp_login;
                cout << endl;
                change_access(temp_login);
            }
            break;
        //case '2':
            //break;
        case '2':
            change_password(current_user);
            break;
        case '0':
            clear_consol();
            variable = false;
            break;
        default:
            break;
        }
    }
    //zmiana dostepu konta
    //usuniecie urzytkownika
    //wyloguj
}




void user_loan()
{
    clear_consol();
    //cin.ignore();
    string current_login, current_id;
    while(true)
    {
        cout << "Wypozyczanie." << endl;
        cout << "Login uzytkownika: ";
        getline(cin, current_login);
        if(is_in_file("users.csv", current_login))
        {
            cout << "Id przedmiotu: ";
            //cin.ignore();
            getline(cin, current_id);
            if(is_in_file("items.csv", current_id))
            {
                Loan* current_loan;
                current_loan = new Loan(current_login, current_id);
                if(current_loan->is_available())
                {
                    current_loan->set_title();
                    current_loan->save_loan();
                    current_loan->display_loan();
                    change_status(current_id);
                    remove_unwanted_lines("items.csv");
                    break;
                }
                else
                {
                    cout << "Przedmiot jest obecnie niedostepny." << endl;
                    cout << "Wcisnij '0' aby wyjsc lub inny klawisz aby kontynuowac." << endl;
                    char ch = getch();
                    clear_consol();
                    if (ch == '0') break;

                }

                delete current_loan;
            }
            else
            {
                clear_consol();
                cout << "Nie znaleziono przemiotu o podanym numerze." << endl;
                cout << "Wcisnij '0' aby wyjsc lub inny klawisz aby kontynuowac." << endl;
                char ch = getch();
                clear_consol();
                if (ch == '0') break;

            }
        }
        else
        {
            clear_consol();
            cout << "Nie znaleziono uzytkownika" << endl;
            cout << "Wcisnij '0' aby wyjsc lub inny klawisz aby kontynuowac." << endl;
            char ch = getch();
            clear_consol();
            if (ch == '0') break;

        }
    }
}

void user_return()
{
    clear_consol();
    string current_login, current_id;
    while(true)
    {
        cout << "Zwrot." << endl;
        cout << "Podaj login uzytkownika: ";
        getline(cin, current_login);
        if(is_in_file("users.csv", current_login))
        {
            cout << "Podaj id przemdiotu: ";
            getline(cin, current_id);
            if(is_in_file("items.csv", current_id))
            {
                if(!is_borrowed(current_id))
                {
                    change_status(current_id);
                    remove_unwanted_lines("items.csv");
                    add_return_date("loans.csv", current_login, current_id);
                    break;
                }
                else
                {
                    cout << "Przedmiot nie jest obecnie wypozycznony." << endl;
                    cout << "Wcisnij '0' aby wyjsc lub inny klawisz aby kontynuowac." << endl;
                    char ch = getch();
                    clear_consol();
                    if (ch == '0') break;

                }
            }
            else
            {
                cout << "Przedmiot jest obecnie niedostepny." << endl;
                cout << "Wcisnij '0' aby wyjsc lub inny klawisz aby kontynuowac." << endl;
                char ch = getch();
                clear_consol();
                if (ch == '0') break;

            }
        }
        else
        {
            cout << "Nie znaleziono podanego uzytkownika." << endl;
            cout << "Wcisnij '0' aby wyjsc lub inny klawisz aby kontynuowac." << endl;
            char ch = getch();
            clear_consol();
            if (ch == '0') break;

        }
    }
}

void app_lib_items(Account* &current_user) //3. Dodaj do listy zasobow" employee
{
    Item *app_item;
    char ch;
    bool valid_choice = false;

    do
    {
        clear_consol();
        cout << "Wybierz typ, ktory chcesz dodac: " << endl;
        cout << "1. Ksiazka"        << endl;
        cout << "2. Muzyka"         << endl;
        cout << "3. Audiobook"      << endl;
        cout << "4. Czasopismo"     << endl;
        cout << "0. Cofnij"         << endl;

        ch = getch();
        //cin.ignore(); // Czyszczenie bufora

        switch(ch)
        {
        case '0':
        {
            program(current_user);
            return;
        }
        case '1':
        { // Ksiazka
            //cin.ignore(); // Czyszczenie bufora
            string book_title, book_author, book_isbn, book_genre;
            cout << "Zapisywanie nowego obiektu." << endl;
            cout << "Podaj dane ksiazki do zapisu." << endl;
            cout << "Tytul: ";
            getline(cin, book_title);
            cout << "Autor: ";
            getline(cin, book_author);
            cout << "Nr ISBN: ";
            getline(cin, book_isbn);
            cout << "Gatunek: ";
            getline(cin, book_genre);
            app_item = new Book(book_isbn, book_author, book_title, book_genre);
            app_item->save();
            valid_choice = true;
            break;
        }
        case '2':
        { // Muzyka
            //cin.ignore(); // Czyszczenie bufora przed u¿yciem getline
            string music_title, music_genre, music_format, music_artist, music_album;
            cout << "Zapisywanie nowego obiektu." << endl;
            cout << "Podaj dane muzyki do zapisu." << endl;
            cout << "Tytul: ";
            getline(cin, music_title);
            cout << "Gatunek: ";
            getline(cin, music_genre);
            cout << "Nosnik: ";
            getline(cin, music_format);
            cout << "Artysta: ";
            getline(cin, music_artist);
            cout << "Album: ";
            getline(cin, music_album);
            app_item = new Music(music_title, music_genre, music_format, music_artist, music_album);
            app_item->save();
            valid_choice = true;
            break;
        }
        case '3':
        { // Audiobook
            //cin.ignore(); // Czyszczenie bufora przed u¿yciem getline
            string ab_title, ab_author, ab_duration;
            cout << "Zapisywanie nowego obiektu." << endl;
            cout << "Podaj dane audiobooka do zapisu." << endl;
            cout << "Tytul: ";
            getline(cin, ab_title);
            cout << "Autor: ";
            getline(cin, ab_author);
            cout << "Czas trwania: ";
            getline(cin, ab_duration);
            app_item = new Audiobook(ab_title, ab_author, ab_duration);
            app_item->save();
            valid_choice = true;
            break;
        }
        case '4':
        { // Czasopismo
            //cin.ignore(); // Czyszczenie bufora przed u¿yciem getline
            string journal_title, journal_issue_number, publication_date;
            cout << "Zapisywanie nowego obiektu." << endl;
            cout << "Podaj dane czasopisma do zapisu." << endl;
            cout << "Tytul: ";
            getline(cin, journal_title);
            cout << "Numer wydania: ";
            getline(cin, journal_issue_number);
            cout << "Data publikacji: ";
            getline(cin, publication_date);
            app_item = new Journal(journal_title, journal_issue_number, publication_date);
            app_item->save();
            valid_choice = true;
            break;
        }
        default:
            clear_consol();
            cout << "Niepoprawny wybor! Sprobuj ponownie." << endl;
            break;
        }

        delete app_item;

    } while (!valid_choice);
}



/*void check_item(const string &id)
{
    if (is_in_file("items.csv", id))
    {
        fstream file("items.csv", ios::in);
        string line;
        bool found = false;
        string last_user;
        while (getline(file, line))
        {
            stringstream ss(line);
            string entry_id, user, item_id, item_name, borrow_date, return_date;
            getline(ss, entry_id, ',');
            getline(ss, user, ',');
            getline(ss, item_id, ',');
            getline(ss, item_name, ',');
            getline(ss, borrow_date, ',');
            getline(ss, return_date, ',');

            if (item_id == id)
            {
                found = true;
                last_user = user;
            }
        }

        if (found)
        {
            cout << "Przedmiot o ID " << id << " jest obecnie wypożyczony przez użytkownika: " << last_user << endl;
        }
        else
        {
            cout << "Przedmiot o ID " << id << " nie jest obecnie wypożyczony." << endl;
        }
    }
    else
    {
        cout << "Nie znaleziono podanego przedmiotu." << endl;
    }

    cout << "Wciśnij '0' aby wyjść lub inny klawisz aby kontynuować." << endl;
    char ch = getch();
    if (ch == '0') return;
}*/














