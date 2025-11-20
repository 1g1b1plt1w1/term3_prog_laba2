#pragma once
#include <string>

vector<Set> parse_subsets(const string& input);
size_t intersection_size(const Set& a, const Set& b);
string Set_to_string(const Set& s);