#include "Table.h"


int Table::get_cols_count() {
    int n = (int)rows.size();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i].get_cells_count() > max) {
            max = rows[i].get_cells_count();
        }
    }
    return max;
}