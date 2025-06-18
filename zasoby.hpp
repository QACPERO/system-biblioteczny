#include <iostream>

using namespace std;

class Item
{
protected:
    static int counter;
    int id;
    string status;  // dostepny/wypozyczony
    string addedDate; // Data dodania zasobu
public:
    Item();
    virtual void save() = 0;
    virtual void display() = 0;  // Aby wywielic dane zasobu
    //virtual void
    virtual ~Item();
};


class Book: public Item
{
private:
    string isbn;
    string author;
    string title;
    string genre;  // Gatunek ksiazki
public:
    Book();
    Book(string, string, string, string);
    void save();
    void display();
    ~Book();
};


class Music: public Item
{
private:
    string title;
    string genre;
    string format; // np. vinyl, cd
    string artist;
    string album;
public:
    Music();
    Music(string, string, string, string, string);
    void save();
    void display();
    ~Music();
};

class Audiobook: public Item
{
private:
    string title;
    string author;
    string duration; // np. "10h 30m"
public:
    Audiobook();
    Audiobook(string, string, string);
    void save();
    void display();
    ~Audiobook();
};


class Journal: public Item
{
private:
    string title;
    string issueNumber;
    string publicationDate;
public:
    Journal();
    Journal(string, string, string);
    void save();
    void display();
    ~Journal();
};


