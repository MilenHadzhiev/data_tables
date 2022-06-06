#include "Currency.h"
#include <iostream>
#include <cstring>

Currency::Currency(int new_money, currency_type new_type) {
    money = new_money;
    currency = new_type;
    if (currency == EUR) {
        symbol = new char[2];
        strcpy(symbol, "€");
    } else if (currency == DOL) {
        symbol = new char[2];
        strcpy(symbol, "$");
    } else {
        symbol = new char[4];
        strcpy(symbol, "лв.");
    }
}

Currency::Currency(int new_money, const char *new_symbol) {
    if (strcmp(new_symbol, "$") == 0) {
        symbol = new char[2];
        strcpy(symbol, new_symbol);
        currency = DOL;
    } else if (strcmp(new_symbol, "€") == 0) {
        symbol = new char[2];
        strcpy(symbol, new_symbol);
        currency = EUR;
    } else if (strcmp(new_symbol, "лв.") == 0) {
        symbol = new char[4];
        strcpy(symbol, "лв.");
        currency = BGN;
    } else {
        throw std::invalid_argument("Currency must be BGN, EUR or DOL");
    }
    money = new_money;
}

Currency::Currency(Currency &other) {
    if (this != &other) {
        money = other.get_money();
        currency = other.get_currency_type();
        delete[] symbol;
        symbol = new char[strlen(other.get_symbol())];
        strcpy(symbol, other.get_symbol());
    }
}

int Currency::get_money() const {
    return money;
}

currency_type Currency::get_currency_type() const {
    return currency;
}

const char *Currency::get_currency_type_string() const {
    return currency == BGN ? "BGN" :
           currency == EUR ? "EUR" :
           "DOL";
}

const char *Currency::get_symbol() const {
    return symbol;
}

void Currency::change_currency(currency_type new_currency) {
    currency = new_currency;
}

void Currency::change_currency(const char *new_currency) {
    if (strcmp(new_currency, "$") == 0) {
        delete[] symbol;
        symbol = new char[2];
        strcpy(symbol, new_currency);
        currency = DOL;
    } else if (strcmp(new_currency, "€") == 0) {
        delete[] symbol;
        symbol = new char[2];
        strcpy(symbol, new_currency);
        currency = EUR;
    } else if (strcmp(new_currency, "лв.") == 0) {
        delete[] symbol;
        symbol = new char[4];
        strcpy(symbol, "лв.");
        currency = BGN;
    } else {
        throw std::invalid_argument("Currency must be BGN, EUR or DOL");
    }
}

void Currency::change_money(int new_money) {
    money = new_money;
}

bool Currency::operator==(const Currency &other) const {
    return money == other.get_money();
}

bool Currency::operator<=(const Currency &other) const {
    return money <= other.get_money();
}

bool Currency::operator>=(const Currency &other) const {
    return money >= other.get_money();
}