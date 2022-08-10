#ifndef DATA_TABLES_UTILS_H
#define DATA_TABLES_UTILS_H
#include <string>

std::string remove_whitespace(std::string *s);

bool is_int(std::string &s);

bool is_double(std::string &s);

bool is_currency(std::string &s);

char is_data_valid(std::string &s);
#endif //DATA_TABLES_UTILS_H
