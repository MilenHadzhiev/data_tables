#include <iostream>
#ifndef DATA_TABLES_MISSINGCOMMAERROR_H
#define DATA_TABLES_MISSINGCOMMAERROR_H

class MissingCommaError : public std::exception {
    std::string err_msg;
public:
    MissingCommaError(unsigned long long int row, unsigned long long int col)
        : err_msg("Potential missing comma on row: " + std::to_string(row) + ", col: " + std::to_string(col) + ".\n") {}

    const char* what() const noexcept override {
        return err_msg.c_str();
    }
};
#endif //DATA_TABLES_MISSINGCOMMAERROR_H
