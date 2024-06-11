#include <iostream>
#include <cstring>
#include "../Utils/Utils.h"

#ifndef DATA_TABLES_CURRENCY_H
#define DATA_TABLES_CURRENCY_H

class Currency {
    int money;
    currency_type currency;
    char *symbol;
public:
    Currency() = default;

    Currency(int new_money, currency_type new_type);

    Currency(int new_money, const char *new_symbol);

    Currency(Currency &other);

    int get_money() const;

    currency_type get_currency_type() const;

    const char *get_currency_type_string() const;

    const char *get_symbol() const;

    void convert_to_BGN();

    void change_money(int new_money);

    bool operator==(const Currency &other) const;

    bool operator<=(const Currency &other) const;

    bool operator>=(const Currency &other) const;
};

#endif //DATA_TABLES_CURRENCY_H