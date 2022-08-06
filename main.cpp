#include <iostream>
#include <cstring>
#include "Currency/Currency.h"
#include "Cell/Cell.h"
#include "Row/Row.h"
#include <typeinfo>
#include <fstream>
#include <vector>

int main() {
    std::string ac = "asfasgga";
    Cell acc(ac);
    Cell vd = acc;
//    Cell array[] = {acc, vd};
//    int size = sizeof(array) / sizeof(array[0]);
//    std::vector<Cell> arr(array, array + size);
    std::vector<Cell> arr;
    arr.push_back(acc);
    arr.push_back(vd);
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
