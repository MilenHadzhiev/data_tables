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

void print_allowed_commands() {
    std::cout << "Allowed actions: \n\t- create <table_name>\n\t- open <file_name>\n\t- save\n\t- save_as <file_name>\n\t- print\n";
    std::cout << "\t- edit <row> <column> <new_value>\n\t- sort <column> asc/desc\n\t- close\n\t- exit\n";
}


int main() {
    print_allowed_commands();
    std::string command;
    Table table;

    while (true) {
        std::cin >> command;
        if (command == "exit") break;
        try {
            if (command == "create") {
                std::string new_table_name;
                std::cin >> new_table_name;
                table.clear();
                table = Table(new_table_name);
            }
            else if (command == "open") {
                std::string file;
                std::cin >> file;
                table.load(file);
            } else if (command == "save") {
                table.save();
            } else if (command == "save_as") {
                std::string new_file_name;
                std::cin >> new_file_name;
                table.save_as(new_file_name);
            } else if (command == "print") {
                table.print();
            } else if (command == "edit") {
                unsigned int row, col;
                std::string new_value;
                std::cin >> row >> col;
                std::cin >> new_value;
                table.edit(row, col, new_value);
            } else if (command == "sort") {
                unsigned int column_id;
                std::string asc_desc;
                std::cin >> column_id;
                std::cin >> asc_desc;
                table.sort(column_id, asc_desc == "ASC" || asc_desc == "asc" ? ASC : DESC);
            } else if (command == "close") {
                std::cout << "Saving and closing table.\n";
                table.save();
                table.clear();
            } else {
                std::cout << "Command not recognized.\n";
                print_allowed_commands();
            }
        } catch (std::exception& e) {
            std::cout << "Unknown exception occurred: " << e.what();
        }
    }
    std::string filepath = "../table.txt";
//    table.save_as(filepath);
//    std::ifstream file(filepath);
//    if (file.is_open()){
//        std::cout << "AFfasd";
//        file.close();
//    }
//    table.save_as(filepath);
    Table table_txt;
    table_txt.load("../table112.txt");
    table_txt.print();
    std::string a = table_txt.get_cell_content(1, 2);
    std::cout << "formula reslt: " << a;
    table_txt.sort(2, DESC);
    std::cout << std::endl;
    table_txt.print();
    std::cout<< '\n';
    table_txt.sort(3, DESC);
    table_txt.print();
//    table_txt.edit(1, 5, "=R2C4^2+R2C3-R3C6*R3C1+R3C1^R3C1");
    std::cout << "R1C5: " << table_txt.get_cell_content(1, 4);
    table_txt.save_as(filepath);
//    table_txt.edit/
//    double a = std::stod("122345.678");
//    std::cout << a;
    return 0;
}