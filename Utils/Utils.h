#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#ifndef DATA_TABLES_UTILS_H
#define DATA_TABLES_UTILS_H

enum currency_type {
    BGN, EUR, USD
};

template<typename T, typename U>
void access_map_element(const std::unordered_map<T, U>& map, T& key, U& value);

std::string remove_whitespace(std::string *s);

// USD 1 = BGN 1.92
// EUR 1 = BGN 1.96

double get_currency_value_in_BGN(currency_type current_currency, double value);

bool is_string(const std::string &s);

bool is_int(const std::string &s);

int convert_to_int(const std::string &s);

bool is_double(const std::string &s);

bool is_currency(const std::string &s);

currency_type get_currency_type(const std::string &s);

#endif //DATA_TABLES_UTILS_H
