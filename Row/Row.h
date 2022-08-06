#ifndef DATA_TABLES_ROW_H
#define DATA_TABLES_ROW_H

#include "../Cell/Cell.h"
#include <vector>

class Row {
    std::vector<Cell> cells;
public:
    Row() = default;

    Row(std::vector<Cell> &new_cells);

    Row(Row &other);

    Row &operator=(Row other);

    void change_cell_content_by_position(unsigned int col_id, std::string new_content);

    std::string get_cell_content_by_position(unsigned int col_id) const;

    int get_cells_count() const;
};

#endif //DATA_TABLES_ROW_H
