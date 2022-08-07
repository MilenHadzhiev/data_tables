#ifndef DATA_TABLES_TABLE_H
#define DATA_TABLES_TABLE_H

#include <string>
#include <vector>
#include "../Cell/Cell.h"
#include "../Row/Row.h"

class Table {
    std::string name;
    std::vector<Row> rows;
    int cols_count = get_cols_count();
public:
    Table();

    Table(std::string new_name, std::vector<Row> new_rows);

    Table(std::string new_name, Row &first_row);

    Table(const Table &other);

    Table(Table &other);

    Table &operator=(Table other);

    void change_name(std::string &new_name);

    void change_cell_content_by_position(unsigned int row_id, unsigned int col_id, std::string new_content);

    void add_row(Row &new_row);

    std::string get_name();

    std::string get_cell_content_by_id(unsigned int row_id, unsigned int col_id);

    int get_cols_count();

    int get_rows_count();
};

#endif //DATA_TABLES_TABLE_H
