#ifndef DATA_TABLES_TABLE_H
#define DATA_TABLES_TABLE_H

enum sorting_types {
    ASC, DESC
};

#include <string>
#include <vector>
#include "../Cell/Cell.h"
#include "../Row/Row.h"

class Table {
    std::string name;
    std::vector<Row> rows;
    int cols_count = get_cols_count();

    static void print_empty_string(unsigned int cell_len);

    unsigned int get_longest_column_length(unsigned int col_id) const;

public:
    Table();

    Table(std::string new_name);

    Table(std::string new_name, std::vector<Row> new_rows);

    Table(std::string new_name, Row &first_row);

    Table(const Table &other);

    Table(Table &other);

    void load(std::string &file_path);

    void save(std::string &file_path) const;

    void print() const;

    void edit(unsigned int row_id, unsigned int col_id, std::string new_content);

    void sort(unsigned int col_id, sorting_types to_sort = ASC);

    void clear();

    Table &operator=(Table other);

    void change_name(std::string &new_name);

    void change_cell_content_by_position(unsigned int row_id, unsigned int col_id, std::string new_content);

    void add_row(Row &new_row);

    void delete_row(unsigned int row_id);

    std::string get_name() const;

    std::string get_cell_content_by_id(unsigned int row_id, unsigned int col_id) const;

    int get_cols_count() const;

    int get_rows_count() const;
};

#endif //DATA_TABLES_TABLE_H
