#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
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
//    std::string filepath = "..\\Cell\\table.txt";
//    std::ifstream file(filepath);
//    if (file.is_open()){
//        std::cout << "AFfasd";
//        file.close();
//    }
//    table.save(filepath);
//    Table table_txt;
    std::string s1 = "34";
    std::string s2 = "234";
    std::string s3 = "52.34";
    std::string s4 = "$12.34";
    std::string s5 = "EUR 12.34";
    std::string s6 = "EUR12.34";
    std::string s7 = "BGN25.34";

    std::string s8 = "afs";
    std::cout << compare_string_to_current(s8, s1) << std::endl; //2
    std::cout << compare_string_to_current(s8, s2) << std::endl; //2
    std::cout << compare_string_to_current(s8, s3) << std::endl; //2
    std::cout << compare_string_to_current(s8, s4) << std::endl; //2
    std::cout << compare_string_to_current(s8, s5) << std::endl; //2
    std::cout << compare_string_to_current(s8, s6) << std::endl; //2
    std::cout << compare_string_to_current(s8, s7) << std::endl; //2
    std::cout << compare_string_to_current(s8, s8) << std::endl; //2
    return 0;
}