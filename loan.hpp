#include <iostream>

using namespace std;

class Loan
{
private:
    static int counter;
    int id;
    string user_login;
    string item_id;
    string item_title;
    string loan_date;
    string return_date;
public:
    Loan();
    Loan(string, string);
    Loan(string, string, string);
    Loan(string, string, string, string, string);
    void save_loan();
    void save_return();
    void display_loan();
    void set_title();
    bool is_available();
};
