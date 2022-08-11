#include "Utils.h"

std::string remove_whitespace(std::string *s) {
//    int i = 0;
    int n = (int) s->size();
    std::string res;
    res.reserve(n);
    bool string_start = false;
    if ((*s)[0] != ' ') {
        res = *s;
    } else {
        for (int i = 0; i < n; i++) {
            if ((*s)[i] != ' ') {
                string_start = true;
            }
            if (string_start) {
                res = s->substr(i, n);
                break;
            }
        }
    }
    string_start = false;
    if ((*s)[s->size() - 1] != ' ' ) {
        return res;
    }

    for (int i = n - 1; i > 0; i--){
        if ((*s)[i] != ' ') {
            string_start = true;
        }
        if (string_start) {
            res = res.substr(0, i);
            break;
        }
    }
    return res;
}

// USD 1 = BGN 1.92
// EUR 1 = BGN 1.96

double get_currency_value_in_BGN(currency_type current_currency, double value) {
    if (current_currency == USD) return value * 1.92;
    if (current_currency == EUR) return value * 1.96;
    return value;
}

bool is_string(std::string &s) {
    if (s[0] == '"' && s[s.size() - 1] == '"') {
        return true;
    }
    return false;
}

bool is_int(std::string &s) {
    int n = (int) s.size();
    for (int i = 0; i < n; i++) {
        if (s[0] == '+' || s[0] == '-') i++;
        if (s[i] == '\0') return true;
        if (!(std::isdigit(s[i]))) {
            return false;
        }
    }
    return true;
}

bool is_double(std::string &s) {
    int n = (int) s.size();
    bool flag_floating_point = false;
    for (int i = 0; i < n; i++) {
        if (s[0] == '+' || s[0] == '-') i++;
        if ((s[0] == '+' || s[0] == '-') && i == 1 && !(std::isdigit(s[i]))) return false;

        if (i == 0 && !(std::isdigit(s[i]))) return false;

        if (!(std::isdigit(s[i])) && s[i] != '.') return false;

        if (!(std::isdigit(s[i])) && s[i] == '.' && flag_floating_point) return false;

        if (!(std::isdigit(s[i])) && s[i] == '.' && !flag_floating_point) flag_floating_point = true;

    }
    return true;
}

bool is_currency(std::string &s) {
    int n = (int) s.size();
    std::string new_s;
    if (s[0] == '$') {
        for (int i = 1; i < n; i++) {
            new_s.push_back(s[i]);
        }
        new_s = remove_whitespace(&new_s);
        if (is_int(new_s) || is_double(new_s)) return true;
    }
    if (s[0] == 'E' && s[1] == 'U' && s[2] == 'R') {
        for (int i = 3; i < n; i++) {
            new_s.push_back(s[i]);
        }
        new_s = remove_whitespace(&new_s);
        if (is_int(new_s) || is_double(new_s)) return true;
    }
    if (s[0] == 'B' && s[1] == 'G' && s[2] == 'N') {
        for (int i = 3; i < n; i++) {
            new_s.push_back(s[i]);
        }
        new_s = remove_whitespace(&new_s);
        if (is_int(new_s) || is_double(new_s)) return true;
    }
    return false;
}

double get_currency_value(std::string &s) {
    int n = (int) s.size();
    std::string new_s;
    if (s[0] == '$') {
        for (int i = 1; i < n; i++) {
            new_s.push_back(s[i]);
        }
    } else { // BGN/EUR take indices 0, 1, 2 so the currency starts at s[3]
        for (int i = 3; i < n; i++) {
            new_s.push_back(s[i]);
        }
    }
    new_s = remove_whitespace(&new_s);
    return atof(new_s.c_str());
}

currency_type get_currency_type(std::string &s) {
    int n = (int) s.size();
    std::string new_s;
    if (s[0] == '$') {
        for (int i = 1; i < n; i++) {
            new_s.push_back(s[i]);
        }
        new_s = remove_whitespace(&new_s);
        if (is_int(new_s) || is_double(new_s)) return USD;
    }
    if (s[0] == 'E' && s[1] == 'U' && s[2] == 'R') {
        for (int i = 3; i < n; i++) {
            new_s.push_back(s[i]);
        }
        new_s = remove_whitespace(&new_s);
        if (is_int(new_s) || is_double(new_s)) return EUR;
    }
    return BGN;
}

// currency return v
// string return s
// int return i
// double return d
char is_data_valid(std::string &s) {
    if (is_string(s)) return 's';
    if (is_int(s)) return 'i';
    if (is_double(s)) return 'd';
    if (is_currency(s)) return 'v';
    return false;
}

unsigned short compare_string_to_current(std::string &s1, std::string &s2) {
    // return 1 if s1 is bigger, 2 if s2 is bigger
    // s1 is the current min/max
    // s2 is the candidate for min/max
    if (is_int(s1) || is_double(s1)) {
        if (is_int(s2) || is_double(s2)) {
            return stoi(s1) >= stoi(s2) ? 1 : 2;
        }
        if (is_currency(s2)) {
            double s2_value_bgn = get_currency_value_in_BGN(get_currency_type(s2), get_currency_value(s2));
            return atof(s1.c_str()) >= s2_value_bgn ? 1 : 2;
        }
        // only case left when s2 is string that can't be converted to int/double/currency ie actual string
        unsigned short s2_value = 0;
        return atof(s1.c_str()) >= s2_value ? 1 : 2;
    }
    if (is_currency(s1)) {
        double s1_value_bgn = get_currency_value_in_BGN(get_currency_type(s1), get_currency_value(s1));
        if (is_int(s2) || is_double(s2)) {
            return s1_value_bgn > atof(s2.c_str()) ? 1 : 2;
        }
        if (is_currency(s2)) {
            double s2_value_bgn = get_currency_value_in_BGN(get_currency_type(s2), get_currency_value(s2));
            return s1_value_bgn >= s2_value_bgn ? 1 : 2;
        }
        unsigned short s2_value = 0;
        return s1_value_bgn >= s2_value ? 1 : 2;
    }
    // only case left when s2 is string that can't be converted to int/double/currency ie actual string
    unsigned short s1_value = 0;
    if (is_int(s2) || is_double(s2)){
        return s1_value >= atof(s2.c_str()) ? 1 : 2;
    }
    if (is_currency(s2)) {
        double s2_value_bgn = get_currency_value_in_BGN(get_currency_type(s2), get_currency_value(s2));
        return s1_value >= s2_value_bgn ? 1 : 2;
    }
    // both s1 and s2 are strings that can't be converted to int/double/currency ie actual strings => both will evaluate to 0
    return 1;
}
