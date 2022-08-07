#include <iostream>
#include "Table.h"

unsigned int Table::get_longest_column_length(unsigned int col_id) const {
    int n = (int)rows.size();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i].get_cell_length(col_id) > max) {
            max = (int)rows[i].get_cell_length(col_id);
        }
    }
    return max;
}

void Table::print_empty_string(unsigned int cell_len) {
    for (unsigned int i = 0; i < cell_len; i++) {
        std::cout << ' ';
    }
}

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

void Table::load(std::ifstream &file) {

}

void Table::save(std::ostream &file) const {

}

void Table::print() const {
    unsigned int columns_count = get_cols_count();
    unsigned int rows_count = get_rows_count();
    for (unsigned int i = 0; i < rows_count; i++) {
        for (unsigned int j = 0; j < columns_count; j++) {
            unsigned int longest_cell_in_current_col = get_longest_column_length(j);
            std::string current_string = rows[i].get_cell_content_by_position(j);
            if(!(current_string.empty())) {
                std::cout << current_string;
                print_empty_string(longest_cell_in_current_col - current_string.length());
            } else {
                print_empty_string(longest_cell_in_current_col);
            }
            std::cout << '|';
        }
        std::cout << '\n';
    }
}

void Table::edit(unsigned int row_id, unsigned int col_id, std::string new_content) {
    change_cell_content_by_position(row_id, col_id, new_content);
}

void Table::sort(unsigned int col_id, sorting_types to_sort) {

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

std::string Table::get_name() const {
    return name;
}

std::string Table::get_cell_content_by_id(unsigned int row_id, unsigned int col_id) const {
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

int Table::get_cols_count() const {
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

int Table::get_rows_count() const {
    return (int)rows.size();
}