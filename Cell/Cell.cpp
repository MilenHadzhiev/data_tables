#include "Cell.h"

Cell::Cell() {
    content = "";
    cell_type = Empty;
}


Cell::Cell(std::string& new_content) {
    content = std::move(new_content);
    assign_cell_type(content);
}

Cell::Cell(const Cell &other) : content(other.content), cell_type(other.cell_type) {}

Cell::Cell(Cell &other) : content(other.content), cell_type(other.cell_type) {}

Cell::Cell(Cell &&other) : content(std::move(other.content)), cell_type(std::move(other.cell_type)) {}

void Cell::assign_cell_type(const std::string& new_content) {
    cell_type = get_data_datatype(new_content);
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
    if (remove_whitespace(&s).empty()) return Empty;
    if (s[0] == '=') return Formula;
    if (is_string(s)) return String;
    if (is_int(s)) return Integer;
    if (is_double(s)) return Double;
    if (is_currency(s)) return Currency;
    return UnknownDataType;
}
