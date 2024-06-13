#include "UnknownDataTypeError.h"

UnknownDataTypeError::UnknownDataTypeError(unsigned long long int row, unsigned long long int col, std::string &data) {
    err_msg = "Unknown data type: " + data + " on row: " + std::to_string(row) + ", col: " + std::to_string(col) + ".\n";
}

