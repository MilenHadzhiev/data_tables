#include <string>
#include <unordered_map>
#include <utility>
#include "../Utils/Utils.h."

#ifndef DATA_TABLES_CELL_H
#define DATA_TABLES_CELL_H

enum cell_data_types {
    Formula, String, Integer, Double, Currency, UnknownDataType
};


class Cell {
    std::string content;
    cell_data_types cell_type;
public:

    static cell_data_types get_data_datatype(const std::string &s);

    Cell();

    Cell(std::string& new_content);

    Cell(const Cell &other);

    Cell(Cell &other);

    Cell(Cell &&other);

    Cell &operator=(const Cell& other);

    void change_content(std::string new_content);

    std::string get_content() const;
    unsigned int get_cell_length() const;
};

#endif //DATA_TABLES_CELL_H