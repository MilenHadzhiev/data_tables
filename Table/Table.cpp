#include "Table.h"

const std::unordered_map<char, unsigned short> Table::operators = {{'^', 2}, { '*', 1 }, { '/', 1 }, { '+', 0 }, { '-', 0 }};

unsigned int Table::get_longest_column_length(unsigned int col_id) const {
    int n = (int) rows.size();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i].get_cell_length(col_id) > max) {
            max = (int) rows[i].get_cell_length(col_id);
        }
    }
    return max;
}

void Table::print_empty_string(unsigned int cell_len) {
    for (unsigned int i = 0; i < cell_len; i++) {
        std::cout << ' ';
    }
}

Table::Table() {
    file_name = "";
}

Table::Table(std::string new_name) : file_name(std::move(new_name)) {}

Table::Table(std::string new_name, std::vector<Row> new_rows) {
    file_name = std::move(new_name);
    rows = std::move(new_rows);
}

Table::Table(std::string new_name, Row &first_row) {
    file_name = std::move(new_name);
    rows.push_back(first_row);
}

Table::Table(const Table &other) {
    file_name = other.file_name;
    rows = other.rows;
}

Table::Table(Table &other) {
    file_name = other.file_name;
    rows = other.rows;
}

bool Table::is_table_loaded() const {
    return file_name != "" || get_rows_count() != 0;
}


void Table::load(std::string &file_path) {
    if (!rows.empty()) {
        std::cout << "Table is already populated. Close current table and try again\n";
        return;
    }
    file_name = file_path;
    std::ifstream file(file_path);
    if (file.is_open()) {
        std::string current_line;
        int row = 0;
        while (!(file.eof())) {
            std::vector<Cell> cells_current_row;
            while (std::getline(file, current_line)) {
                row++;
                std::string current_cell_content;
                int line_size = (int) current_line.size();
                if (current_line.empty()) {
                    cells_current_row.emplace_back();
                } else {
                    int column = 0;
                    for (int i = -1; i < line_size; i++) {
                        column++;
                        while (current_line[++i] != ',') {
                            if (i >= line_size) break;
                            current_cell_content.push_back(current_line[i]);
                        }
                        current_cell_content = remove_whitespace(&current_cell_content);

                        if (Cell::get_data_datatype(current_cell_content) == UnknownDataType) {
                            clear();
                            std::cout << "Error, couldn't load table: row " << row << ", col: " << column << ", "
                                      << current_cell_content << " is an unknown data type.\n";
                            return;
                        }
                        cells_current_row.emplace_back(current_cell_content);
                        current_cell_content = "";
                        i--; // to avoid skipping a char, because i gets incremented twice
                    }
                }
                rows.emplace_back(cells_current_row);
                cells_current_row.clear();
            }
        }
        file.close();
    } else {
        std::cout << "Error: File could not be opened.\n";
    }
}

void Table::save() const {
    save_as(file_name != "" ? file_name : "new_data_table.txt");
}

void Table::save_as(const std::string &file_path) const {
    if (!is_table_loaded()) {
        std::cout << "Error: No table to save.\n";
        return;
    }
    std::ofstream file(file_path.c_str());
    if (file.is_open()) {
        int n = (int) get_cols_count();
        for (const Row &row: rows) {
            for (int i = 0; i < n; i++) {
                int r_c = (int) row.get_cells_count();
                if (i < r_c) {
                    std::string current_cell = row.get_cell_content_by_position(i + 1);
                    if (is_string(current_cell) && !(current_cell[0] == '"' && current_cell[current_cell.size() - 1] == '"')) {
                        file << '"' << current_cell << "\"";
                    } else {
                        file << current_cell;
                    }
                }
                file << ", ";
            }
            file << '\n';
        }
        file.close();
    } else {
        std::cout << "Error: File could not be opened/created to save data table.\n";
    }
}

std::string Table::calculate_formula_result(const std::string &content) const {
    std::vector<std::string> postfix_notation = convert_infix_to_potfix_notation(content);
    std::stack<double> st;
    for (int i = 0; i < postfix_notation.size(); ++i) {
        if (postfix_notation[i] != "+" && postfix_notation[i] != "-" && postfix_notation[i] != "/"
            && postfix_notation[i] != "*" && postfix_notation[i] != "^") {
            st.push(get_string_numeric_value(postfix_notation[i]));
        } else {
            double b = st.top();
            st.pop();
            double a = st.top();
            st.pop();
            if (postfix_notation[i] == "+")
                st.push(a + b);
            else if (postfix_notation[i] == "-")
                st.push(a - b);
            else if (postfix_notation[i] == "*")
                st.push(a * b);
            else if (postfix_notation[i] == "^")
                st.push(pow(a, b));
            else
                try {
                    st.push(a / b);
                }
                catch (std::exception &e) {
                    std::cout << "ERROR";
                    throw e;
                }
        }
    }
    return std::to_string(st.top());
}

std::vector<std::string> Table::convert_infix_to_potfix_notation(const std::string &content) const {
    std::vector<std::string> result;
    std::stack<char> seen_operators;
    unsigned int i = 1;  // content[0] is =

    while (i < content.size()) {
        char symbol = content[i++];
        if (operators.find(symbol) == operators.end()) {  // means the symbol is a number/cell
            if (symbol == 'R') { // current element of the formula is a ref to another cell
                try {
                    std::string cell_row;
                    std::string cell_col;
                    while (content[i] != 'C') {
                        cell_row += content[i++];
                    }
                    int row = convert_to_int(cell_row);
                    i++; // to skip the C;
                    while (int(content[i]) > 47 && content[i] < 58) {
                        cell_col += content[i++];
                    }
                    int col = convert_to_int(cell_col);

                    result.push_back(get_cell_content(row, col));
                } catch (std::exception) {
                    result.push_back("0");
                }
            } else {  // we have a number
                std::string res(1, symbol);
                while (operators.find(content[i]) == operators.end()) {
                    res += content[i++];
                }
                result.push_back(res); // res is just an int/float
            }
        } else if (seen_operators.empty()) {
            seen_operators.push(symbol);
        } else {
            unsigned short current_element_weight;
            unsigned short stack_element_weight;
            current_element_weight = operators.at(symbol);
            stack_element_weight = operators.at(seen_operators.top());
//            access_map_element(operators, symbol, current_element_weight);
//            access_map_element(operators, seen_operators.top(), stack_element_weight);

            while (current_element_weight <= stack_element_weight && !seen_operators.empty()) {
                std::string stack_top(1, seen_operators.top());
                result.push_back(stack_top);
                seen_operators.pop();
                if (!seen_operators.empty()) {
                    stack_element_weight = operators.at(seen_operators.top());
//                    access_map_element(operators, seen_operators.top(), stack_element_weight);
                }
            }
            seen_operators.push(symbol);
        }
    }
    while (!seen_operators.empty()) {
        std::string stack_top(1, seen_operators.top());
        result.emplace_back(stack_top);
        seen_operators.pop();
    }
    return result;
}


void Table::print() const {
    unsigned int columns_count = get_cols_count();
    unsigned int rows_count = get_rows_count();
    if (!is_table_loaded()) {
        std::cout << "No table has been loaded.\n";
        return;
    }
    if (get_rows_count() == 0) {
        std::cout << "Table " << file_name << " is empty.\n";
    }
    std::cout << "Table " << file_name << "\n";
    for (unsigned int i = 0; i < rows_count; i++) {
        for (unsigned int j = 0; j < columns_count; j++) {
            unsigned int longest_cell_in_current_col = get_longest_column_length(j);
            std::string current_string = get_cell_content(i + 1, j + 1);
            std::cout << ' ';
            if (!(current_string.empty())) {
                std::cout << current_string;
                print_empty_string(longest_cell_in_current_col - current_string.length());
            } else {
                print_empty_string(longest_cell_in_current_col);
            }
            std::cout << ' ';
            std::cout << '|';
        }
        std::cout << '\n';
    }
}

void Table::edit(unsigned int row_id, unsigned int col_id, std::string new_content) {
    change_cell_content_by_position(row_id, col_id, new_content);
}

void Table::merge(sorting_types to_sort, const unsigned int col_id, const int left, const int mid, const int right) {
    const int left_sub_array_size = mid - left + 1;
    const int right_sub_array_size = right - mid;

    std::vector<std::string> left_sub_array;
    std::vector<std::string> right_sub_array;
    for (unsigned int i = 0; i < left_sub_array_size; ++i)
        left_sub_array.push_back(rows[left + i].get_cell_content_by_position(col_id));

    for (unsigned int i = 0; i < right_sub_array_size; ++i)
        right_sub_array.push_back(rows[mid + 1 + i].get_cell_content_by_position(col_id));

    int left_sub_array_idx = 0, right_sub_array_idx = 0;
    int merged_array_idx = left;

    while (left_sub_array_idx < left_sub_array_size && right_sub_array_idx < right_sub_array_size) {
        if ((to_sort == DESC && compare_strings(left_sub_array[left_sub_array_idx], right_sub_array[right_sub_array_idx]) == 1) ||
            (to_sort == ASC && compare_strings(right_sub_array[right_sub_array_idx], left_sub_array[left_sub_array_idx]) == 1))
            rows[merged_array_idx].change_cell_content_by_position(col_id, left_sub_array[left_sub_array_idx++]);
        else
            rows[merged_array_idx].change_cell_content_by_position(col_id, right_sub_array[right_sub_array_idx++]);

        merged_array_idx++;
    }

    while (left_sub_array_idx < left_sub_array_size)
        rows[merged_array_idx++].change_cell_content_by_position(col_id, left_sub_array[left_sub_array_idx++]);

    while (right_sub_array_idx < right_sub_array_size)
        rows[merged_array_idx++].change_cell_content_by_position(col_id, right_sub_array[right_sub_array_idx++]);
}

void Table::mergesort(sorting_types to_sort, const unsigned int col_id, const int start, const int end) {
    if (start >= end) return;

    int middle = start + (end - start) / 2;
    mergesort(to_sort, col_id, start, middle);
    mergesort(to_sort, col_id, middle + 1, end);
    merge(to_sort, col_id, start, middle, end);
}

void Table::sort(unsigned int col_id, sorting_types to_sort) {
    if (!is_table_loaded()) {
        std::cout << "No table to sort.\n";
        return;
    }
    if (col_id - 1 > get_cols_count()) {
        std::cout << "There are only " << get_cols_count() << " columns in the table.\n";
        return;
    }
    mergesort(to_sort, col_id, 0, rows.size() - 1);
//    if (to_sort == ASC) {
//        sort_asending(col_id, get_rows_count());
//    } else {
//        sort_descending(col_id, get_rows_count());
//    }
}

void Table::clear() {
    rows.clear();
    file_name = "";
}

Table &Table::operator=(Table other) {
    std::swap(file_name, other.file_name);
    std::swap(rows, other.rows);
    return *this;
}

void Table::change_name(std::string &new_name) {
    file_name = new_name;
}

void Table::change_cell_content_by_position(unsigned int row_id, unsigned int col_id, std::string new_content) {
    if (file_name == "") {
        std::cout << "Table not initialized.\n";
        return;
    } else if (Cell::get_data_datatype(new_content) == UnknownDataType) {
        std::cout << "Unsupported data type.\n";
        return;
    }
    if (row_id >= get_rows_count()) {
        for (unsigned int i = get_rows_count(); i < row_id; ++i) {
            rows.emplace_back();
        }
    }
    if (rows[row_id - 1].get_cells_count() == 0) {
        std::vector<Cell> this_row;
        for (int i = 0; i < col_id; i++) {
            this_row.emplace_back();
        }
        this_row[col_id - 1].change_content(new_content);
        rows[row_id - 1] = this_row;

    }
    rows[row_id - 1].change_cell_content_by_position(col_id, new_content);
}

void Table::add_row(Row &new_row) {
    rows.push_back(new_row);
}

void Table::delete_row(unsigned int row_id) {
    this->rows.erase(rows.begin() + (row_id - 1));
}

std::string Table::get_name() const {
    return file_name;
}

std::string Table::get_cell_content(unsigned int row_id, unsigned int col_id) const {
    if (rows.empty()) {
        return "Table is empty.\n";
    } else if (row_id > get_rows_count()) {
        throw std::invalid_argument("Row doesn't exist.\n");
    } else if (col_id > get_cols_count()) {
        throw std::invalid_argument("Column doesn't exist.\n");
    } else if (rows[row_id - 1].get_cells_count() == 0) return "\n";
    std::string cell_content = rows[row_id - 1].get_cell_content_by_position(col_id);
    return cell_content[0] == '=' ? calculate_formula_result(cell_content) : cell_content;
}

int Table::get_cols_count() const {
    if (rows.empty()) {
        return 0;
    }
    int n = (int) rows.size();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i].get_cells_count() > max) {
            max = rows[i].get_cells_count();
        }
    }
    return max;
}

int Table::get_rows_count() const {
    return (int) rows.size();
}

unsigned short Table::compare_strings(const std::string &s1, const std::string &s2) const {
    // return 1 if s1 is bigger, 2 if s2 is bigger
    // s1 is the current min/max
    // s2 is the candidate for min/max
    std::string s1_to_use_for_comparison;
    std::string s2_to_use_for_comparison;
    if (s1[0] == '=') s1_to_use_for_comparison = this->calculate_formula_result(s1);
    else s1_to_use_for_comparison = s1;

    if (s2[0] == '=') s2_to_use_for_comparison = this->calculate_formula_result(s2);
    else s2_to_use_for_comparison = s2;

    if (is_int(s1_to_use_for_comparison) || is_double(s1_to_use_for_comparison)) {
        if (is_int(s2_to_use_for_comparison) || is_double(s2_to_use_for_comparison)) {
            return stod(s1_to_use_for_comparison) >= stod(s2_to_use_for_comparison) ? 1 : 2;
        }
        if (is_currency(s2_to_use_for_comparison)) {
            double s2_value_bgn = get_currency_value_in_BGN(get_currency_type(s2_to_use_for_comparison), get_string_numeric_value(s2_to_use_for_comparison));
            return std::stod(s1_to_use_for_comparison) >= s2_value_bgn ? 1 : 2;
        }
        // only case left when s2 is string that can't be converted to int/double/currency ie actual string
        unsigned short s2_value = 0;
        return std::stod(s1_to_use_for_comparison) >= s2_value ? 1 : 2;
    }
    if (is_currency(s1_to_use_for_comparison)) {
        double s1_value_bgn = get_currency_value_in_BGN(get_currency_type(s1_to_use_for_comparison), get_string_numeric_value(s1_to_use_for_comparison));
        if (is_int(s2_to_use_for_comparison) || is_double(s2_to_use_for_comparison)) {
            return s1_value_bgn > std::stod(s2_to_use_for_comparison) ? 1 : 2;
        }
        if (is_currency(s2)) {
            double s2_value_bgn = get_currency_value_in_BGN(get_currency_type(s2_to_use_for_comparison), get_string_numeric_value(s2_to_use_for_comparison));
            return s1_value_bgn >= s2_value_bgn ? 1 : 2;
        }
        unsigned short s2_value = 0;
        return s1_value_bgn >= s2_value ? 1 : 2;
    }
    // only case left when s1 is string that can't be converted to int/double/currency ie actual string
    unsigned short s1_value = 0;
    if (is_int(s2_to_use_for_comparison) || is_double(s2_to_use_for_comparison)) {
        return s1_value >= std::stod(s2_to_use_for_comparison) ? 1 : 2;
    }
    if (is_currency(s2_to_use_for_comparison)) {
        double s2_value_bgn = get_currency_value_in_BGN(get_currency_type(s2_to_use_for_comparison), get_string_numeric_value(s2_to_use_for_comparison));
        return s1_value >= s2_value_bgn ? 1 : 2;
    }
    // both s1 and s2 are strings that can't be converted to int/double/currency ie actual strings => both will evaluate to 0
    return 1;
}

double Table::get_string_numeric_value(const std::string &s) {
    if (s.empty()) return 0;
    if (is_double(s) || is_int(s)) return std::stod(s);
    int n = (int) s.size();
    std::string new_s;
    if (is_currency(s)) {
        for (const char& current : s) {
            if (std::isdigit(current) || current == '.') {
                new_s += current;
            }
        }
    }
    if (is_string(s)) return 0;
    new_s = remove_whitespace(&new_s);
    if (new_s == "") {
        return 0;
    }
    return std::stod(new_s);
}
