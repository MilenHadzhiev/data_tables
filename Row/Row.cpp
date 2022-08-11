#include "Row.h"

Row::Row(std::vector<Cell> &new_cells) {
    cells = new_cells;
}

Row::Row(const Row &other) {
    cells = other.cells;
}

Row::Row(Row &other) {
    cells = other.cells;
}

Row &Row::operator=(Row other) {
    std::swap(cells, other.cells);
    return *this;
}

void Row::change_cell_content_by_position(unsigned int col_id, std::string new_content) {
    int s = (int)get_cells_count();
    if (col_id > s) {
        for(int i = s; i < col_id - 1; i++) {
            cells.emplace_back();
        }
        cells.emplace_back(new_content);
    }
    cells[col_id - 1].change_content(std::move(new_content));
}

std::string Row::get_cell_content_by_position(unsigned int col_id) const {
    // pass column id ranging from 0 to n, where n = cells.size() // the amount of cells
    if (col_id <= cells.size()) {
        return cells[col_id - 1].get_content();
    }
    return "";
}

unsigned int Row::get_cells_count() const {
    return (int) cells.size();
}

unsigned int Row::get_cell_length(unsigned int cell_id) const {
    if (cell_id >= cells.size()) {
        return 0;
    }
    return cells[cell_id].get_cell_length();
}