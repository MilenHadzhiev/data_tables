#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
#include "../Cell/Cell.h"
#include "../Row/Row.h"
#include "../Utils/Utils.h"
#include "../CustomExceptions/MissingCommaError/MissingCommaError.h"
#include "../CustomExceptions/UnknownDataTypeError/UnknownDataTypeError.h"
#ifndef DATA_TABLES_TABLE_H
#define DATA_TABLES_TABLE_H

enum sorting_types {
    ASC, DESC
};

class Table {
    std::string file_name;
    std::vector<Row> rows;
    static const std::unordered_map<char, unsigned short> operators;

    static void print_empty_string(unsigned int cell_len);

    bool is_table_loaded() const;

    unsigned int get_longest_column_length(unsigned int col_id) const;

    std::vector<std::string> convert_infix_to_potfix_notation(const std::string& content) const;

    void merge(sorting_types to_sort, unsigned int col_id,int left, int mid, int right);
    void mergesort(sorting_types to_sort, unsigned int col_id, int start, int end);
    unsigned short compare_strings(const std::string &s1, const std::string &s2) const;
    static double get_string_numeric_value(const std::string &s);

    void check_inconsistency(const std::string& currently_read_line);

    static unsigned long long int count_cells_from_row(const std::string& row_as_string);
public:
    Table();

    Table(std::string new_name);

    Table(std::string new_name, std::vector<Row> new_rows);

    Table(std::string new_name, Row &first_row);

    Table(const Table &other);

    Table(Table &other);

    Table(Table &&other);

    void load(const std::string &file_path);

    void save() const;

    void save_as(const std::string &file_path) const;

    void print() const;

    void edit(unsigned int row_id, unsigned int col_id, std::string new_content);

    void sort(unsigned int col_id, sorting_types to_sort = ASC);

    void clear();

    Table &operator=(Table other);

    std::string calculate_formula_result(const std::string& content) const;

    void change_name(std::string &new_name);

    void change_cell_content_by_position(unsigned int row_id, unsigned int col_id, std::string new_content);

    void add_row(Row &new_row);

    void delete_row(unsigned int row_id);

    std::string get_name() const;

    std::string get_cell_content(unsigned int row_id, unsigned int col_id) const;

    int get_cols_count() const;

    int get_rows_count() const;
};

#endif //DATA_TABLES_TABLE_H
