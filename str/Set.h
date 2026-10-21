#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <vector>
#include "open_hash.h"

using namespace std;

struct Set {
    Map map;
};

Set Set_create(size_t capacity = 16);
void Set_destroy(Set& s);

void Set_add(Set& s, const string& value);
bool Set_del(Set& s, const string& value);
bool Set_has(const Set& s, const string& value);
vector<string> Set_keys(const Set& s);

#endif