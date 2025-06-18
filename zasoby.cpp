#include <iostream>
#include <fstream>
#include "zasoby.hpp"
#include "funkcje.hpp"

using namespace std;

int Item::counter = remember_id("items.csv");


// klasa Item
Item::Item() : id(++counter), status("dostepny"), addedDate(get_current_date()) {}

Item::~Item() {}


// klasa Book
Book::Book() : isbn(""), author(""), title(""), genre("") {}

Book::Book(string i, string a, string t, string g) : isbn(i), author(a), title(t), genre(g) {}

Book::~Book() {}

void Book::save() {
    fstream file;
    file.open("items.csv", ios::app);
    file << id << "," << "ksiazka" << "," << title << "," << author << "," << genre << "," << isbn << "," << addedDate << "," << status << endl;
    file.close();
    cout << "Dodano pomyslnie." << endl;
    cout << "Nacisnij dowolny przycisk aby kontunuowac." << endl;
    getch();
}

void Book::display() {
    cout << "Ksiazka: " << title << " - Autor: " << author << endl;
}


// klasa Music
Music::Music() : genre(""), format(""), artist(""), album("") {}

Music::Music(string t, string g, string f, string a, string al) : title(t), genre(g), format(f), artist(a), album(al) {}

Music::~Music() {}

void Music::save() {
    fstream file;
    file.open("items.csv", ios::app);
    file << id << "," << "muzyka" << "," << title << "," << artist << "," << album << "," << genre << "," << format << "," << addedDate << "," << status << endl;
    file.close();
    cout << "Dodano pomyslnie." << endl;
    cout << "Nacisnij dowolny przycisk aby kontunuowac." << endl;
    getch();
}


void Music::display() {
    cout << "Muzyka: " << album << " - Artysta: " << artist << " - Gatunek: " << genre << " - Format: " << format << endl;
}


// klasa Audiobook
Audiobook::Audiobook() : title(""), author(""), duration("") {}

Audiobook::Audiobook(string t, string a, string d) : title(t), author(a), duration(d) {}

Audiobook::~Audiobook() {}

void Audiobook::save() {
    fstream file;
    file.open("items.csv", ios::app);
    file << id << "," << "audiobook" << "," << title << "," << author << "," << duration << "," << addedDate << "," << status << endl;
    file.close();
    cout << "Dodano pomyslnie." << endl;
    cout << "Nacisnij dowolny przycisk aby kontunuowac." << endl;
    getch();
}

void Audiobook::display() {
    cout << "Audiobook: " << title << " - Autor: " << author << " - Czas trwania: " << duration << endl;
}


// klasa Journals
Journal::Journal() : title(""), issueNumber(""), publicationDate("") {}

Journal::Journal(string t, string in, string pd) : title(t), issueNumber(in), publicationDate(pd) {}

Journal::~Journal() {}

void Journal::save() {
    fstream file;
    file.open("items.csv", ios::app);
    file << id << "," << "czasopismo" << "," << title << "," << issueNumber << "," << publicationDate << "," << addedDate << "," << status << endl;
    file.close();
    cout << "Dodano pomyslnie." << endl;
    cout << "Nacisnij dowolny przycisk aby kontunuowac." << endl;
    getch();
}


void Journal::display() {
    cout << "Czasopismo: " << title << " - Numer: " << issueNumber << " - Data publikacji: " << publicationDate << endl;
}
