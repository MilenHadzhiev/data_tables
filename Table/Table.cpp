#include <iostream>
#include <fstream>
#include "Table.h"
#include "../Utils/Utils.h"


unsigned int Table::get_longest_column_length(unsigned int col_id) const {
    int n = (int) rows.size();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i].get_cell_length(col_id) > max) {
            max = (int) rows[i].get_cell_length(col_id);
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

Table::Table(std::string new_name) : name(std::move(new_name)) {}

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

void Table::load(std::string &file_path) {
    if (!rows.empty()) {
        std::cout << "Table is already populated.\n";
        return;
    }
    std::ifstream file(file_path);
    if (file.is_open()) {
        std::string current_line;
        int row = 0;
        while (!(file.eof())) {
            std::vector<Cell> cells_current_row;
            while (std::getline(file, current_line)) {
                row++;
                std::string current_cell_content;
                int line_size = (int) current_line.size();
                if (current_line.empty()) {
                    cells_current_row.emplace_back();
                } else {
                    int column = 0;
                    for (int i = -1; i < line_size; i++) {
                        column++;
                        while (current_line[++i] != ',') {
                            if (i >= line_size) break;
                            current_cell_content.push_back(current_line[i]);
                        }
                        current_cell_content = remove_whitespace(&current_cell_content);

                        if (!(is_data_valid(current_cell_content))) {
                            clear();
                            std::cout << "Error, couldn't load table: row " << row << ", col: " << column << ", "
                                      << current_cell_content << " is an unknown data type.\n";
                            return;
                        }
                        cells_current_row.emplace_back(current_cell_content);
                        current_cell_content = "";
                        i--; // to avoid skipping a char, because i gets incremented twice
                    }
                }
                rows.emplace_back(cells_current_row);
                cells_current_row.clear();
            }
        }
        file.close();
    } else {
        std::cout << "Error: File could not be opened.";
    }
}

// TODO
void Table::save(std::string &file_path) const {
    std::ofstream file(file_path);
    if (file.is_open()) {


        file.close();
    } else {
        std::cout << "Error: File could not be opened.\n";
    }

}

void Table::print() const {
    unsigned int columns_count = get_cols_count();
    unsigned int rows_count = get_rows_count();
    for (unsigned int i = 0; i < rows_count; i++) {
        for (unsigned int j = 0; j < columns_count; j++) {
            unsigned int longest_cell_in_current_col = get_longest_column_length(j);
            std::string current_string = rows[i].get_cell_content_by_position(j);
            std::cout << ' ';
            if (!(current_string.empty())) {
                std::cout << current_string;
                print_empty_string(longest_cell_in_current_col - current_string.length());
            } else {
                print_empty_string(longest_cell_in_current_col);
            }
            std::cout << ' ';
            std::cout << '|';
        }
        std::cout << '\n';
    }
}

void Table::edit(unsigned int row_id, unsigned int col_id, std::string new_content) {
    change_cell_content_by_position(row_id, col_id, new_content);
}

// TODO
void Table::sort(unsigned int col_id, sorting_types to_sort) {

}

void Table::clear() {
    int n = (int) rows.size();
    for (int i = 0; i < n; i++) { // for row in rows
        int m = (int) rows[i].get_cells_count();
        for (int j = 0; j < m; j++) { // for cell in row
            rows[i].change_cell_content_by_position(j, "");
        }
    }
}

Table &Table::operator=(Table other) {
    std::swap(name, other.name);
    std::swap(rows, other.rows);
    return *this;
}

void Table::change_name(std::string &new_name) {
    name = new_name;
}

void Table::change_cell_content_by_position(unsigned int row_id, unsigned int col_id, std::string new_content) {
    if (rows.empty()) {
        std::cout << "Table not initialized.\n";
    }
    else if (row_id > get_rows_count()) {
        std::cout << "Row doesn't exist.\n";
    } else if (!(is_data_valid(new_content))) {
        std::cout << "Invalid data.\n";
    } else if (col_id > get_cols_count()) {
        std::cout << "Column doesn't exist.\n";
    } else if (rows[row_id - 1].get_cells_count() == 0) {
        std::vector<Cell> this_row;
        for (int i = 0; i < col_id - 2; i++) {
            this_row.emplace_back();
        }
        this_row.emplace_back(new_content);
        rows[row_id] = this_row;
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
        return "Table is empty.\n";
    } else if (row_id > get_rows_count()) {
        return "Row doesn't exist.\n";
    } else if (col_id > get_cols_count()) {
        throw std::invalid_argument("Column doesn't exist.\n");
    } else if (rows[row_id - 1].get_cells_count() == 0) return "\n";
    return rows[row_id - 1].get_cell_content_by_position(col_id - 1);
}

int Table::get_cols_count() const {
    if (rows.empty()) {
        return 0;
    }
    int n = (int) rows.size();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i].get_cells_count() > max) {
            max = rows[i].get_cells_count();
        }
    }
    return max;
}

int Table::get_rows_count() const {
    return (int) rows.size();
}