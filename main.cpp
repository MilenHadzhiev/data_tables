#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <stack>
#include "Currency/Currency.h"
#include "Cell/Cell.h"
#include "Row/Row.h"
#include "Table/Table.h"
#include "Utils/Utils.h"

void change_address(std::string *s) {
    std::string as = "dfasfasf";
    s = &as;
}

int main() {
//    Cell a;
//    Cell c(a);
//    std::string ac = "asfasgga";
//    Cell acc(ac);
//    Cell vd = acc;
//    std::vector<Cell> arr;
//    arr.push_back(acc);
//    arr.push_back(a);
//    arr.push_back(vd);
//    arr.push_back(c);
//    Row new_row(arr);
//    std::vector<Row> row_vect;
//    row_vect.push_back(new_row);
//    Row empty_row;
//    Table table("My table", row_vect);
//    table.add_row(empty_row);
//    table.print();
    std::string filepath = "../table.txt";
//    table.save_as(filepath);
//    std::ifstream file(filepath);
//    if (file.is_open()){
//        std::cout << "AFfasd";
//        file.close();
//    }
//    table.save_as(filepath);
    Table table_txt;
    table_txt.load(filepath);
    table_txt.print();
    std::string a = table_txt.get_cell_content(1, 2);
    std::cout << "formula reslt: " << a;
    table_txt.sort(2, DESC);
    std::cout << std::endl;
    table_txt.print();
    std::cout<< '\n';
    table_txt.sort(3, DESC);
    table_txt.print();
    table_txt.edit(1, 5, "=R2C4^2+R2C3-R3C6*R3C1+R3C1^R3C1");
    std::cout << "R1C5: " << table_txt.get_cell_content(1, 5);
    table_txt.save_as(filepath);
//    table_txt.edit/
//    double a = std::stod("122345.678");
//    std::cout << a;
    return 0;
}