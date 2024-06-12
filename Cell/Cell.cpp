#include "Cell.h"

Cell::Cell() {
    content = "";
    cell_type = Empty;
}


Cell::Cell(std::string& new_content) {
    content = std::move(new_content);
    assign_cell_type(new_content);
}

Cell::Cell(const Cell &other) : content(other.content), cell_type(other.cell_type) {}

Cell::Cell(Cell &other) : content(other.content), cell_type(other.cell_type) {}

Cell::Cell(Cell &&other) : content(other.content), cell_type(other.cell_type) {}

void Cell::assign_cell_type(const std::string& new_content) {
    if (is_int(new_content)) cell_type = Integer;
    else if (is_currency(new_content)) cell_type = Currency;
    else if (is_double(new_content)) cell_type = Double;
    else if (is_string(new_content)) cell_type = String;
    else if (new_content[0] == '=') cell_type = Formula;
    else cell_type = UnknownDataType;
}

void Cell::change_content(std::string new_content) {
    content = std::move(new_content);
    assign_cell_type(new_content);
}

std::string Cell::get_content() const {
    return content;
}

Cell& Cell::operator=(const Cell& other) {
    if (this != &other) {
        content = other.content;
    }
    return *this;
}

unsigned int Cell::get_cell_length() const {
    return content.length();
}

cell_data_types Cell::get_data_datatype(const std::string &s) {
    if (s[0] == '=') return Formula;
    if (is_string(s)) return String;
    if (is_int(s)) return Integer;
    if (is_double(s)) return Double;
    if (is_currency(s)) return Currency;
    return UnknownDataType;
}
