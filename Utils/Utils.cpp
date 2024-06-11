#include "Utils.h"

template<typename T, typename U>
void access_map_element(const std::unordered_map<T, U>& map, T& key, U& value) {
    auto res = map.find(key);
    if (res == map.end()) throw std::invalid_argument("Key not found");
    value = res->second;
}

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

double get_currency_value_in_BGN(const currency_type current_currency, const double value) {
    if (current_currency == USD) return value * 1.92;
    if (current_currency == EUR) return value * 1.96;
    return value;
}

bool is_string(const std::string &s) {
    if (s[0] == '"' && s[s.size() - 1] == '"') {
        return true;
    }
    return false;
}

bool is_int(const std::string &s) {
    int n = (int) s.size();
    for (int i = 0; i < n; i++) {
        if (s[0] == '+' || s[0] == '-') {
            i++;
            continue;
        }
        if (s[i] == '\0') return true;
        if (!(std::isdigit(s[i]))) {
            return false;
        }
    }
    return true;
}


int convert_to_int(const std::string& s) {
    unsigned int zeros = s.size();
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
        res += (atoi(&s[i]) * zeros);
        zeros--;
    }
    return res;
}

bool is_double(const std::string &s) {
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

bool is_currency(const std::string &s) {
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


currency_type get_currency_type(const std::string &s) {
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