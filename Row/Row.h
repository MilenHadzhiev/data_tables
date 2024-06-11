#include "../Cell/Cell.h"
#include <vector>

#ifndef DATA_TABLES_ROW_H
#define DATA_TABLES_ROW_H

class Row {
    std::vector<Cell> cells;
public:
    Row() = default;

    Row(std::vector<Cell> &new_cells);

    Row(const Row &other);

    Row(Row &other);

    Row &operator=(Row other);

    void change_cell_content_by_position(unsigned int col_id, std::string new_content);

    std::string get_cell_content_by_position(unsigned int col_id) const;

    unsigned int get_cells_count() const;

    unsigned int get_cell_length(unsigned int cell_id) const;
};

#endif //DATA_TABLES_ROW_H
