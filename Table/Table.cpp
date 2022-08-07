#include <iostream>
#include "Table.h"

Table::Table() {
    name = "New table";
}

Table::Table(std::string new_name, std::vector<Row> new_rows) {
    name = std::move(new_name);
    rows = std::move(new_rows);
}

Table::Table(std::string new_name, Row &first_row) {
    name = std::move(new_name);
    rows.push_back(first_row);
}

Table::Table(const Table &other) {
    name = other.name;
    rows = other.rows;
}

Table::Table(Table &other) {
    name = other.name;
    rows = other.rows;
}

Table& Table::operator=(Table other) {
    std::swap(name, other.name);
    std::swap(rows, other.rows);
    return *this;
}

void Table::change_name(std::string &new_name) {
    name = new_name;
}

void Table::change_cell_content_by_position(unsigned int row_id, unsigned int col_id, std::string new_content) {
    if (rows.empty()) {
        std::cout << "A cell at row " << row_id << " and col " << col_id << " doesn't exist.";
    } else if (rows[row_id - 1].get_cells_count() == 0) {
        std::cout << " ";
    } else {
        rows[row_id - 1].change_cell_content_by_position(col_id - 1, new_content);
    }
}

void Table::add_row(Row &new_row) {
    rows.push_back(new_row);
}

std::string Table::get_name() {
    return name;
}

std::string Table::get_cell_content_by_id(unsigned int row_id, unsigned int col_id) {
    if (rows.empty()) {
        return " ";
    } else if (rows[row_id - 1].get_cells_count() == 0) return " ";
    else if (row_id > get_rows_count()) {
        throw std::invalid_argument("No such row");
    }
    else if (col_id > get_cols_count()) {
        throw std::invalid_argument("No such column");
    }
    return rows[row_id - 1].get_cell_content_by_position(col_id - 1);
}

int Table::get_cols_count() {
    if (rows.empty()) {
        return 0;
    }
    int n = (int)rows.size();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i].get_cells_count() > max) {
            max = rows[i].get_cells_count();
        }
    }
    return max;
}

int Table::get_rows_count() {
    return (int)rows.size();
}