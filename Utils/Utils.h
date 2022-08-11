#ifndef DATA_TABLES_UTILS_H
#define DATA_TABLES_UTILS_H

#include <string>
#include "../Currency/Currency.h"

std::string remove_whitespace(std::string *s);

// USD 1 = BGN 1.92
// EUR 1 = BGN 1.96

double get_currency_value_in_BGN(currency_type current_currency, double value);

bool is_string(std::string &s);

bool is_int(std::string &s);

bool is_double(std::string &s);

bool is_currency(std::string &s);

double get_currency_value(std::string &s);

currency_type get_currency_type(std::string &s);

char is_data_valid(std::string &s);

unsigned short compare_string_to_current(std::string &s1, std::string &s2);

#endif //DATA_TABLES_UTILS_H
