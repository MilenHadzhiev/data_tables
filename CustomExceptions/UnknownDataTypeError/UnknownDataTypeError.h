#include <iostream>
#ifndef DATA_TABLES_UNKNOWNDATATYPEERROR_H
#define DATA_TABLES_UNKNOWNDATATYPEERROR_H


class UnknownDataTypeError : public std::exception {
    std::string err_msg;
public:
    UnknownDataTypeError(unsigned long long int row, unsigned long long int col, std::string& data);

    const char* what () const noexcept override {
        return err_msg.c_str();
    }
};

#endif //DATA_TABLES_UNKNOWNDATATYPEERROR_H
