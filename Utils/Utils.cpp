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
    if (s[0] == '$') {
        std::string new_s;
        for (int i = 1; i < n; i++) {
            new_s.push_back(s[i]);
        }
        if (is_int(new_s) || is_double(new_s)) return true;
    }
//    if (s[0] == "€") {
//
//    }
//    if (s[n-1] == '.' && s[n-2] == 'в')
    return false;
}
// currency return v

// string return s
// int return i
// double return d
char is_data_valid(std::string &s) {
    if (s[0] == '"' && s[s.size() - 1] == '"')
        return 's'; // s.size() = # of chars s.size() - 1 == \0 s.size() - 2 -> actual last char
    if (is_int(s)) return 'i';
    if (is_double(s)) return 'd';
    if (is_currency(s)) return 'v';
    return false;
}
