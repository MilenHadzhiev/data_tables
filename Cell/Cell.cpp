#include "Cell.h"

#include <utility>

Cell::Cell() {
    content = "";
}


Cell::Cell(std::string new_content) {
    content = std::move(new_content);
}

Cell::Cell(const Cell &other) {
    content = other.get_content();
}

Cell::Cell(Cell &other) {
    content = other.get_content();
}

void Cell::change_content(std::string new_content) {
    content = std::move(new_content);
}

std::string Cell::get_content() const {
    return content;
}

Cell& Cell::operator=(Cell other) {
    std::swap(content, other.content);
    return *this;
}