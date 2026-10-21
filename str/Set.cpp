#include <iostream>
#include "Set.h"
#include "open_hash.h"

using namespace std;

Set Set_create(size_t capacity) {
    Set s{hashOpen_create(capacity)};
    return s;
}

void Set_destroy(Set& s) {
    hashOpen_destroy(s.map);
}

void Set_add(Set& s, const string& value) {
    hashOpen_insert_lineal(s.map, value);
}

bool Set_del(Set& s, const string& value) {
    return hashOpen_del(s.map, value);
}

bool Set_has(const Set& s, const string& value) {
    return hashOpen_find(s.map, value) != -1;
}

vector<string> Set_keys(const Set& s) {
    vector<string> keys;
    for (size_t i = 0; i < s.map.cap; i++) {
        if (s.map.node[i].status == NodeStatus::USED) {
            keys.push_back(s.map.node[i].val);
        }
    }
    return keys;
}

