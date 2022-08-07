#ifndef DATA_TABLES_CELL_H
#define DATA_TABLES_CELL_H

#include <string>

class Cell {
    std::string content;
public:
    Cell();

    Cell(std::string new_content);

    Cell(const Cell &other);

    Cell(Cell &other);

    Cell &operator=(Cell other);

    void change_content(std::string new_content);

    std::string get_content() const;
    unsigned int get_cell_length() const;
};

#endif //DATA_TABLES_CELL_H