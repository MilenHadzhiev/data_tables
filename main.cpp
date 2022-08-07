#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

#include "Currency/Currency.h"
#include "Cell/Cell.h"
#include "Row/Row.h"
#include "Table/Table.h"

int main() {
    Cell a;
    Cell c(a);
    std::string ac = "asfasgga";
    Cell acc(ac);
    Cell vd = acc;
    std::vector<Cell> arr;
    arr.push_back(acc);
    arr.push_back(a);
    arr.push_back(vd);
    arr.push_back(c);
    Row new_row(arr);
    std::vector<Row> row_vect;
    row_vect.push_back(new_row);
    Row empty_row;
    Table table("My table", row_vect);
    table.add_row(empty_row);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cout << "Shit...";
    }
    table.print();




//    std::cout << table.get_rows_count();
//    std::ifstream file("../table.txt");
//    std::string a;
//    file >> a;
//    if (file.is_open()) {
//        while(!(a.empty())) {
//            std::cout << a;
//            if (file.eof()) break;
//            file >> a;
//        }
//        file.close();
//    }

    return 0;
}
