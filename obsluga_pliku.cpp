#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "obsluga_pliku.hpp"

using namespace std;


vector<Account> load_users_from_csv(const string& filename)
{
    fstream file;
    file.open(filename, ios::in); // Otwieranie pliku w trybie do odczytu

    vector<Account> users;
    if (!file) {
        cout << "Plik nie zostal poprawnie otwarty" << endl;
        return users; // Zwrócenie pustego wektora w przypadku bledu
    }

    string line;
    while (getline(file, line))
    {
        vector<string> fields = split(line, ','); // Podzia³ linii po przecinku
        if (fields.size() == 3) {
            Account acc;
            acc.SetLogin(fields[0]);    // Login
            acc.SetPassword(fields[1]); // Haslo
            acc.SetRole(fields[2]);     // Rola
            users.push_back(acc);       // Dodanie obiektu do wektora
        } else {
            cout << "Nieprawidlowy format danych w linii: " << line << endl;
        }
    }

    file.close(); // Zamkniecie pliku
    return users;
}

vector<string> split(const string& line, char delimiter)
{
    vector<string> tokens;
    string token;
    stringstream ss(line); // Tworzenie strumienia z linii


    while (getline(ss, token, delimiter)) // Podzial po podanym znaku
    {
        tokens.push_back(token);
    }

    return tokens;
}

vector<Account> lines_into_class(vector<string> vec)
{
    vector<Account> users;

    // Iterowanie co 3 elementy
    for (size_t i = 0; i < vec.size(); i += 3)
    {
        // Tworzenie nowego obiektu Account
        Account acc;
        acc.SetLogin(vec[i]);
        acc.SetPassword(vec[i + 1]);
        acc.SetRole(vec[i + 2]);

        // Dodanie obiektu do wektora
        users.push_back(acc);
    }

    return users;
}


