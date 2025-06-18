#include <iostream>
#include <vector>
#include "uzytkownicy.hpp"

vector<Account> lines_into_class(vector<string> vec);

vector<string> split(const string& line, char delimiter);

void load_file_csv(fstream file, vector<Account> &users_return);

vector<Account> load_users_from_csv(const string& filename);
