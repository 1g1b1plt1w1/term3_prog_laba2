#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Set.h"
using namespace std;

vector<Set> parse_subsets(const string& input) {
    vector<Set> result;
    string num;

    bool inside = false;
    Set cur;

    for (char c : input) {

        if (c == '{') {
            if (!inside) {
                inside = true;
                cur = Set_create(8);
            }
            continue;
        }

        if (c == '}') {
            if (!num.empty()) {
                Set_add(cur, num);
                num.clear();
            }
            if (inside) {
                result.push_back(cur);
                inside = false;
            }
            continue;
        }

        if (!inside) continue;

        if (isdigit(c)) num.push_back(c);
        else {
            if (!num.empty()) {
                Set_add(cur, num);
                num.clear();
            }
        }
    }

    return result;
}


size_t intersection_size(const Set& a, const Set& b) {
    vector<string> A = Set_keys(a);
    size_t count = 0;

    for (auto& x : A)
        if (Set_has(b, x))
            count++;

    return count;
}

string Set_to_string(const Set& s) {
    vector<string> v = Set_keys(s);
    string out = "{";
    for (int i = 0; i < v.size(); i++) {
        out += v[i];
        if (i + 1 < v.size()) out += ",";
    }
    out += "}";
    return out;
}