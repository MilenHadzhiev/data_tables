#ifndef DATA_TABLES_TABLE_H
#define DATA_TABLES_TABLE_H
#include "../Cell/Cell.h"
#include <cstring>
#include "../Row/Row.h"
class Table{
    string name;
    Row* rows;
    Col* cols;
    Cell* cells;

public:
    Table();
};

#endif //DATA_TABLES_TABLE_H
