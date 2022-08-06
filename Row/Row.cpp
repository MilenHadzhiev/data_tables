#include "Row.h"

Row::Row(std::vector<Cell> &new_cells) {
    cells = new_cells;
}

Row::Row(Row &other) {
    cells = other.cells;
}

Row &Row::operator=(Row other) {
    std::swap(cells, other.cells);
    return *this;
}

void Row::change_cell_content_by_position(unsigned int col_id, std::string new_content) {
    cells[col_id].change_content(new_content);
}

std::string Row::get_cell_content_by_position(unsigned int col_id) const {
    // pass column id ranging from 0 to n, where n = cells.size() // the amount of cells
    if (col_id < cells.size()) {
        return cells[col_id].get_content();
    }
    return " ";
}

int Row::get_cells_count() const {
    return (int) cells.size();
}