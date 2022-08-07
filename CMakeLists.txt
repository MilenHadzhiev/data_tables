cmake_minimum_required(VERSION 3.20)
project(data_tables)

set(CMAKE_CXX_STANDARD 14)

add_executable(data_tables main.cpp Table/Table.h Cell/Cell.h Cell/Cell.cpp Table/Table.cpp Currency/Currency.h Row/Row.cpp Row/Row.h Currency/Currency.cpp)
