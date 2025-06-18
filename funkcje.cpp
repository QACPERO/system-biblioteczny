#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <ctime>
#include <limits>
#include <iomanip>

#include "funkcje.hpp"
#include "obsluga_pliku.hpp"
#include "loan.hpp"

#include <openssl/sha.h>


using namespace std;

void login(Account* &current_user) // Logowanie do systemu
{
    cout << "Zaloguj sie lub zarejestruj do systemu. " << endl;
    cout << "1. Zaloguj" << endl;
    cout << "2. Zarejestruj" << endl;
    cout << "0. Wyjscie z programu" << endl;
    char ch = getch();

    switch(ch)
    {
    case '0':
        cout << "Wyjscie z programu." << endl;
        exit(0);
        break;
    case '1':
        user_login(current_user);
        break;
    case '2':
        new_user(current_user);
        break;
    default:
        wrong_choise(current_user);
        break;
    }
}

void user_login(Account* &current_user) // Sekwencja logowania uzytkownika
{
    bool login_access;
    clear_consol();
    cout << "Ekran logowania" << endl;
    login_access = check_user(current_user);
    if(login_access)
    {
        cout << "Zalogowano pomyslnie." << endl;
    }
    else
    {
        cout << "Logowanie nieudane." << endl;
    }
}

bool check_user(Account* &current_user)
{
    current_user = new Account();
    string temp_login, temp_password;
    vector<Account> users = load_users_from_csv("users.csv");
    int attempts = 0;

    while (true)
    {
        cout << "Podaj swoj login: ";
        getline(cin, temp_login);

        bool user_found = false;
        for (size_t i = 0; i < users.size(); ++i)
        {
            if (users[i].GetLogin() == temp_login)
            {
                user_found = true;
                cout << "Podaj haslo: ";
                temp_password = get_password();

                // Hashowanie wprowadzonego hasła
                string hashed_password = hash_password(temp_password);

                if (users[i].GetPassword() == hashed_password)
                {
                    current_user = &users[i];
                    return true;
                }
                else
                {
                    cout << "Nieprawidlowe haslo!" << endl;
                    break;
                }
            }
        }

        if (!user_found)
        {
            clear_consol();
            cout << "Nie znaleziono uzytkownika." << endl;
        }

        attempts++;
        if (attempts >= 3)
        {
            clear_consol();
            cout << "Za duzo nieudanych prob logowania." << endl;
            exit(0);
        }

        cout << "1. Zaloguj sie jeszcze raz" << endl;
        cout << "2. Zarejestruj sie" << endl;
        cout << "0. Zamknij program" << endl;
        char ch = getch();

        switch (ch)
        {
        case '1':
            clear_consol();
            break;
        case '2':
            new_user(current_user);
            break;
        case '0':
            exit(0);
        }
    }
}


void new_user(Account* &current_user)
{
    Account acc;
    clear_consol();
    int counter = 0;
    string temp_login, temp_password;
    while(counter < 4)
    {

        cout << "Rejestracja. Login nie moze zawierac spacji oraz znakow specjalnych" << endl;
        cout << "Podaj swoj login: ";
        getline(cin, temp_login);
        acc.SetLogin(temp_login);
        cout << endl;

        if (!is_valid_login(temp_login))
        {
            cout << "Login zawiera niedozwolone znaki. Sprobuj ponownie." << endl;
            counter++;
            continue;
        }

        if (is_not_empty(temp_login))
        {
            cout << "Podany Login jest pusty" << endl;
            counter++;
            if (counter >= 3)
            {
                cout << "Za duzo nieudanych prob rejestracji" << endl;
                exit(0);
            }
            continue;
        }

        if(check_login_in_file(temp_login))
        {
            cout << "Podany login jest poprawny." << endl;
            cout << "Podaj haslo: ";
            temp_password = get_password();

            // Hashowanie hasła
            string hashed_password = hash_password(temp_password);

            acc.SetPassword(hashed_password);
            current_user = new Account(temp_login, hashed_password);
            acc.insert_into_csv();

            break;
        }
        else
        {
            clear_consol();
            cout << "Podany login \"" << temp_login << "\" jest zajety, sprobuj jeszcze raz." <<endl;
        }


    }
}


bool is_not_empty(const string& login)
{
    if(login.empty())
    {
        return true;
    }
    return false;
}

bool is_valid_login(const string& login) // walidacja loginu
{
    for (char c : login)
    {
        if (!isalnum(c)) // sprawdzenie czy znak jest alfanumeryczny
        {
            return false;
        }
    }
    return true;
}

bool check_login_in_file(string login) // sprawdzanie czy login juz sitneije i czy mozna uzyc podany login
{
    fstream file;
    file.open("users.csv", ios::in);
    if (!file)
    {
        cout << "Nie mozna otworzyc pliku: " << endl;
        return false;
    }
    vector<string> data;
    string line;
    string text;
    while(getline(file, line))     // dodawanie samyc loginow do vectora
    {
        int position = line.find(",");
        line = line.substr(0, position);
        data.push_back(line);
    }
    file.close();

    for (size_t i = 0; i < data.size(); ++i)
    {
        if (login==data[i]) return false;
    }

    return true;
}




void wrong_choise(Account* &current_user)     //wybor spoza mozliwych
{
    clear_consol();
    cout << "Wybor spoza listy. Sproboj ponownie: " << endl;
    login(current_user);

}










//=======================================

void clear_consol()
{
    system("cls");
    art();
}

void art()
{
    cout << " ____  _ _     _ _       _       _         " << endl;
    cout << "| __ )(_) |__ | (_) ___ | |_ ___| | ____ _ " << endl;
    cout << "|  _ \\| | '_ \\| | |/ _ \\| __/ _ \\ |/ / _` |" << endl;
    cout << "| |_) | | |_) | | | (_) | ||  __/   < (_| |" << endl;
    cout << "|____/|_|_.__/|_|_|\\___/ \\__\\___|_|\\_\\__,_|" << endl;
    cout << "=================================================" << endl;
    cout << endl;
}

string get_current_date() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(ltm->tm_mday);
    return date;
}

string hash_password(const string& input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);

    string output;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]); // Konwertuje na format heksadecymalny
        output += buffer;
    }
    return output;
}

string get_password() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();  // Wczytaj znak bez wyświetlania go na ekranie

        if (ch == 13) { // Enter (kod ASCII 13) - zakończenie wpisywania
            break;
        } else if (ch == 8) { // Backspace (kod ASCII 8)
            if (!password.empty()) {  // Jeśli hasło nie jest puste
                cout << "\b \b";  // Cofnij kursor, nadpisz spacją i ponownie cofnij
                password.pop_back(); // Usuń ostatni znak z hasła
            }
        } else if (ch >= 32 && ch <= 126) { // Obsługuje znaki drukowalne
            password.push_back(ch);  // Dodaj znak do hasła
            cout << '*';             // Wyświetl gwiazdkę jako maskowanie
        }
    }

    cout << endl; // Nowa linia po zakończeniu wpisywania
    return password;
}




//=================================================================================
int remember_id(const string& filename)
{
    fstream file;
    file.open(filename, ios::in); // Otwieranie podanego pliku
    if (!file) // Sprawdzenie, czy plik został otwarty
    {
        cout << "Nie mozna otworzyc pliku: " << filename << endl;
        return -1; // Zwracamy -1 jako sygnał błędu
    }

    string line;
    int maxValue = numeric_limits<int>::min();

    while (getline(file, line)) {
        stringstream ss(line);
        string firstPart;

        getline(ss, firstPart, ',');

        try {
            int value = stoi(firstPart);

            if (value > maxValue) {
                maxValue = value;
            }
        } catch (const invalid_argument& e) {
            continue;
        } catch (const out_of_range& e) {
            continue;
        }
    }

    file.close();
    return maxValue;
}

void change_status(string item_id)
{
    fstream file;
    string line;
    file.open("items.csv", ios::in | ios::out);

    if (!file)
    {
        cout << "Nie mozna otworzyc pliku items.csv" << endl;
        return;
    }


    stringstream file_content;
    bool status_changed = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string file_id;
        vector<string> columns;


        while (getline(ss, file_id, ','))
        {
            columns.push_back(file_id);
        }


        if (columns.size() < 2) continue;

        file_id = columns[0]; // Pierwsza kolumna to ID
        string status = columns[columns.size() - 1]; // Ostatnia kolumna to status

        // Sprawdzenie, czy ID się zgadza
        if (file_id == item_id)
        {
            // Zmiana statusu na przeciwny
            if (status == "dostepny")
            {
                status = "niedostepny";
            } else if (status == "niedostepny")
            {
                status = "dostepny";
            }


            columns[columns.size() - 1] = status;


            for (size_t i = 0; i < columns.size(); ++i)
            {
                file_content << columns[i];
                if (i < columns.size() - 1)
                {
                    file_content << ",";
                }
            }
            file_content << "\n";
            status_changed = true;
        } else
    {
            file_content << line << "\n";
        }
    }

    if (!status_changed)
    {
        cout << "Nie znaleziono przedmiotu o ID " << item_id << endl;
    } else {
        // Ustawienie kursora na początek pliku
        file.clear();
        file.seekp(0, ios::beg);

        // Zapisz zmodyfikowany plik
        file << file_content.str();

        // Zatrzymanie strumienia i zamknięcie pliku
        file.close();
    }
}


void remove_unwanted_lines(const string& filename) {
    fstream file;
    string line;
    vector<string> lines;

    // Otwieramy plik do odczytu
    file.open(filename, ios::in);

    if (!file)
    {
        cout << "Nie mozna otworzyc pliku " << filename << endl;
        return;
    }

    // Odczytujemy wszystkie linie i filtrujemy
    while (getline(file, line))
    {
        // Sprawdzamy, czy linia nie zawiera tylko 'y' lub jest pusta
        if (line == "y" || line.empty())
        {
            continue; // Pomijamy te linie
        }
        lines.push_back(line); // Dodajemy poprawne linie do wektora
    }

    file.close(); // Zamykamy plik do odczytu

    // Otwieramy plik ponownie do zapisu (nadpisanie pliku)
    file.open(filename, ios::out | ios::trunc);

    if (!file)
    {
        cout << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }

    // Zapisujemy wszystkie poprawne linie do pliku
    for (const string& valid_line : lines)
    {
        file << valid_line << "\n";
    }

    file.close(); // Zamykamy plik po zapisaniu
}

bool is_in_file(const string& filename, const string& login) {
    fstream file;
    string line;

    // Otwieramy plik do odczytu
    file.open(filename, ios::in);

    if (!file)
    {
        cout << "Nie mozna otworzyc pliku " << filename << endl;
        return false;
    }

    // Sprawdzamy każdą linię
    while (getline(file, line))
    {
        stringstream ss(line);
        string file_login;

        // Wczytujemy pierwszą kolumnę  przed przecinkiem
        getline(ss, file_login, ',');

        // Porównujemy z podanym loginem
        if (file_login == login) {
            file.close(); // Zamykamy plik
            return true;  // Login istnieje
        }
    }

    file.close(); // Zamykamy plik
    return false; // Login nie istnieje
}

bool is_borrowed(string item_id)
{
    fstream file;
    file.open("items.csv", ios::in);
    if(!file)
    {
        cout << "Nie mozna otowrzyc pliku" << endl;
        return false;
    }

    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string file_id, column;

        getline(ss, file_id, ',');

        if (file_id == item_id)
        {
            string status;


            while (getline(ss, column, ','))
            {
                status = column;
            }

            file.close();
            return (status == "niedostpny");
        }
    }

    file.close();
    return false;
}

void add_return_date(const string& filename, const string& login, const string& item_id) {
    fstream file;
    file.open(filename, ios::in);

    if (!file) {
        cout << "Nie mozna otworzyc pliku " << filename << endl;
        return;
    }

    string line;
    vector<string> updated_lines;
    string current_date = get_current_date();
    bool updated = false;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> columns;
        string column;

        // Podział linii na kolumny
        while (getline(ss, column, ',')) {
            columns.push_back(column);
        }

        // Jeśli liczba kolumn jest mniejsza niż 5, pomijamy
        if (columns.size() < 5) {
            updated_lines.push_back(line);
            continue;
        }

        // Sprawdzenie warunków: login, id_przedmiotu oraz brak daty zwrotu
        if (!updated && columns[1] == login && columns[2] == item_id && columns.size() == 5) {
            columns.push_back(current_date); // Dodajemy datę zwrotu
            updated = true; // Aktualizacja zakończona
        }

        // Tworzenie zaktualizowanej linii
        stringstream updated_line;
        for (size_t i = 0; i < columns.size(); ++i)
        {
            updated_line << columns[i];
            if (i < columns.size() - 1)
            {
                updated_line << ",";
            }
        }
        updated_lines.push_back(updated_line.str());
    }

    file.close();

    // Nadpisanie pliku
    file.open(filename, ios::out | ios::trunc);
    if (!file)
    {
        cout << "Nie mozna zapisac pliku " << filename << endl;
        return;
    }

    for (const string& updated_line : updated_lines)
    {
        file << updated_line << "\n";
    }

    file.close();

    clear_consol();
    if (updated)
    {
        cout << "Zwrot przebiegl pomyslnie." << endl;
    }
    else
    {
        cout << "Nie znaleziono pasujacego wypozyczenia." << endl;
    }
}


void borrowed_items(const string& current_login, const string& filter_type)
{
    fstream file;
    file.open("loans.csv", ios::in);
    string line;

    //string current_login = current_user->GetLogin();

    // Dostosowanie nagłówka w zależności od liczby dat
    cout << left << setw(15) << "ID" << setw(40) << "Przedmiot";
    if (filter_type == "one_date")
    {
        cout << setw(25) << "Data wypozyczenia" << endl;
    }
    else if (filter_type == "two_dates")
    {
        cout << setw(25) << "Data wypozyczenia" << setw(25) << "Data zwrotu" << endl;
    }
    cout << string(85, '-') << endl;

    while (getline(file, line))
    {
        stringstream ss(line);
        string loan_id, login, item_id, item_name, start_date, end_date;

        getline(ss, loan_id, ',');
        getline(ss, login, ',');
        getline(ss, item_id, ',');
        getline(ss, item_name, ',');
        getline(ss, start_date, ',');
        getline(ss, end_date, ',');

        if (login == current_login)
        {
            bool show_record = false;

            if (filter_type == "one_date" && end_date.empty())
            {
                show_record = true;
            }
            else if (filter_type == "two_dates" && !end_date.empty())
            {
                show_record = true;
            }

            if (show_record)
            {
                // Wyświetlanie danych z większymi odstępami
                cout << left << setw(15) << item_id << setw(40) << item_name << setw(25) << start_date;
                if (filter_type == "two_dates") {
                    cout << setw(25) << end_date;
                }
                cout << endl;
            }
        }
    }

    cout << endl << "Nacisnij dowolny przycisk aby kontynuowac" << endl;
    getch();
    clear_consol();
    file.close();
}


void delete_item(const string &id)
{
    ifstream file("items.csv");
    vector<string> lines;
    string line;
    bool found = false;
    bool is_available = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string item_id, type, title, author, additional_info, date, status;
        getline(ss, item_id, ',');
        getline(ss, type, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, additional_info, ',');
        getline(ss, date, ',');
        getline(ss, status, ',');

        if (item_id == id) {
            found = true;
            if (status == "dostepny") {
                is_available = true;
                continue;
            }
        }
        lines.push_back(line);
    }
    file.close();

    if (!found) {
        cout << "Nie znaleziono podanego przedmiotu." << endl;
    } else if (!is_available) {
        cout << "Nie można usunac przedmiotu, poniewaz jest wypozyczony." << endl;
    } else {
        ofstream outFile("items.csv");
        for (const string &entry : lines) {
            outFile << entry << endl;
        }
        outFile.close();
        cout << "Przedmiot o ID " << id << " zostal usuniety." << endl;
    }

    cout << "Wcisnij dowolny klawisz aby kontynuowac." << endl;
    getch();
    clear_consol();
}

void change_password(Account *&current_user)
{
    clear_consol();
    string check_password;
    cout << "Zmiana hasla." << endl;
    cout << "Potwierdz aktualne haslo: ";
    check_password = get_password();

    if (hash_password(check_password) == current_user->GetPassword())
    {
        string new_password;
        cout << "Podaj nowe haslo: ";
        new_password = get_password();

        current_user->SetPassword(hash_password(new_password));

        ifstream file("users.csv");
        vector<string> lines;
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string login, password, role;
            getline(ss, login, ',');
            getline(ss, password, ',');
            getline(ss, role, ',');

            if (login == current_user->GetLogin())
            {
                lines.push_back(login + "," + current_user->GetPassword() + "," + role);
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile("users.csv");
        for (const string &entry : lines)
        {
            outFile << entry << endl;
        }
        outFile.close();

        cout << "Haslo zostalo zmienione." << endl;
    }
    else
    {
        cout << "Podano nieprawidlowe haslo." << endl;
    }
    cout << "Nacisnij dowolny przycisk zeby kontynuowac." << endl;
    getch();
    cin.ignore();
    clear_consol();
}


void change_access(const string login)
{
    if (!is_in_file("users.csv", login))
    {
        cout << "Uzytkownik nie znaleziony." << endl;
        return;
    }

    fstream file("users.csv", ios::in | ios::out);
    vector<string> lines;
    string line, current_role;

    while (getline(file, line))
    {
        stringstream ss(line);
        string username, password, role;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');

        if (username == login)
        {
            current_role = role;
            cout << "Aktualna rola: ";
            if (role == "user")
            {
                cout << "uzytkownik" << endl;
            }
            else if (role == "employee")
            {
                cout << "Pracownik" << endl;
            }
            else if (role == "admin")
            {
                cout << "Administrator" << endl;
            }
            cout << "Wybierz nowa role:" << endl;
            cout << "1. Administrator" << endl;
            cout << "2. Uzytkownik" << endl;
            cout << "3. Pracownik" << endl;
            char ch = getch();
            string new_role;
            switch (ch)
            {
                case '1':
                    new_role = "admin";
                    break;
                case '2':
                    new_role = "user";
                    break;
                case '3':
                    new_role = "employee";
                    break;
                default:
                    cout << "Nieprawidlowy wybor." << endl;
                    return;
            }
            lines.push_back(username + "," + password + "," + new_role);
        }
        else
        {
            lines.push_back(line);
        }
    }
    file.close();

    file.open("users.csv", ios::out | ios::trunc);
    for (const string &entry : lines)
    {
        file << entry << endl;
    }
    file.close();

    cout << "Rola uzytkownika zostala zmieniona." << endl;
    cout << "Nacisnij dowolny przycik aby kontynuowac. " << endl;
    getch();
    cin.ignore();
    clear_consol();
}


