#include <iostream>
#include "uzytkownicy.hpp"
#include "funkcje.hpp"
#include "obsluga_programu.hpp"


using namespace std;
int main()
{
    Account* current_user;
    current_user = new Account();
    while(true)
    {
        clear_consol();
        login(current_user);
        clear_consol();

        program(current_user);
    }


    delete current_user;
    return 0;
}
