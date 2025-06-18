#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "loan.hpp"
#include "funkcje.hpp"

using namespace std;

int Loan::counter = remember_id("loans.csv");

Loan::Loan(){}

Loan::Loan(string l, string i): id(++counter), user_login(l), item_id(i), loan_date(get_current_date()) {}

Loan::Loan(string l, string i,string d): user_login(l), item_id(i), loan_date(d), return_date(get_current_date()) {}

Loan::Loan(string loan_i, string l, string item_i, string t, string d): id(stoi(loan_i)), user_login(l), item_id(item_i), item_title(t), loan_date(d) {}

void Loan::save_loan()
{
    fstream file;
    file.open("loans.csv", ios::app);
    file << id << "," << user_login << "," << item_id << "," << item_title << "," << loan_date << endl;
    file.close();
}

void Loan::save_return()
{
    fstream file;
    file.open("loans.csv", ios::app);
    file << id << "," << user_login << "," << item_id << "," << item_title << "," << loan_date << "," << return_date << endl;
    file.close();
}

void Loan::display_loan()
{
    cout << "Wypozyczono przedmiot o id  " << item_id << " uzytkownikowi " << user_login << endl;
    cout << "Nacisnij dowolny przycisk aby kontynuowac." << endl;
    getch();
    clear_consol();
}

void Loan::set_title() // Dodawanie tytu³u na podstawie ID przedmiotu
{
    fstream file;
    file.open("items.csv", ios::in);

    if (!file) {
        cout << "Nie mozna otworzyc pliku items.csv" << endl;
        return;
    }

    string line; // Zmienna na liniê z pliku
    while (getline(file, line))
        { // Odczyt linii
        stringstream ss(line); // Tworzenie strumienia z linii
        string file_id, file_title, temp;

        // Odczyt ID i tytu³u z odpowiednich kolumn
        getline(ss, file_id, ',');   // Separator ',' jako pojedynczy znak
        getline(ss, file_title, ','); // Odczyt pierwszego tytu³u (w tym przypadku "ksiazka")
        getline(ss, temp, ',');       // Odczyt drugiego tytu³u (w tym przypadku "wiedz")

        if (file_id == item_id)
        {
            item_title = temp; // Przypisanie tytu³u z drugiej kolumny
            break;
        }
    }

    file.close();
}

bool Loan::is_available() // Sprawdzenie dostêpnoœci przedmiotu
{
    fstream file;
    file.open("items.csv", ios::in);

    if (!file) {
        cout << "Nie mozna otworzyc pliku items.csv" << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string file_id, column;

        // Pobierz ID z pierwszej kolumny
        getline(ss, file_id, ',');


        if (file_id == item_id)
        {
            string status;


            while (getline(ss, column, ','))
            {
                status = column;
            }

            file.close();
            return (status == "dostepny");
        }
    }

    file.close();
    return false; // Jeœli ID nie znaleziono, zwracamy false
}

