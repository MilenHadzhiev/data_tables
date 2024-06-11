#include "Currency.h"

Currency::Currency(int new_money, currency_type new_type) {
    money = new_money;
    currency = new_type;
    if (currency == EUR) {
        symbol = new char[2];
        strcpy(symbol, "€");
    } else if (currency == USD) {
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
        currency = USD;
    } else if (strcmp(new_symbol, "€") == 0) {
        symbol = new char[2];
        strcpy(symbol, new_symbol);
        currency = EUR;
    } else if (strcmp(new_symbol, "лв.") == 0) {
        symbol = new char[4];
        strcpy(symbol, "лв.");
        currency = BGN;
    } else {
        throw std::invalid_argument("Currency must be BGN, EUR or USD");
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
           "USD";
}

const char *Currency::get_symbol() const {
    return symbol;
}

void Currency::convert_to_BGN() {
    money = get_currency_value_in_BGN(currency, money);
    currency = BGN;
}

void Currency::change_money(int new_money) {
    money = new_money;
}

bool Currency::operator==(const Currency &other) const {
    return get_currency_value_in_BGN(currency, money) == get_currency_value_in_BGN(other.currency, other.money);
}

bool Currency::operator<=(const Currency &other) const {
    return get_currency_value_in_BGN(currency, money) <= get_currency_value_in_BGN(other.currency, other.money);
}

bool Currency::operator>=(const Currency &other) const {
    return get_currency_value_in_BGN(currency, money) >= get_currency_value_in_BGN(other.currency, other.money);
}