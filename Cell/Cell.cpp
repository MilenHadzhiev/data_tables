#include "Cell.h"

Cell::Cell() {
    content = "";
}

Cell::Cell(std::string &new_content) {
    content = new_content;
}

Cell::Cell(Cell &other) {
    content = other.get_content();
}

void Cell::change_content(std::string &new_content) {
    content = new_content;
}

std::string Cell::get_content() {
    return content;
}

Cell& Cell::operator=(Cell other) {
    content = other.get_content();
    return *this;
}