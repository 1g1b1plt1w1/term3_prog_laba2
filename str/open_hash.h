#ifndef OPEN_HASH_H
#define OPEN_HASH_H

#include <iostream>
#include <string>
using namespace std;

enum class NodeStatus{
    EMPTY,
    USED,
    DELETED
};

struct HashNode {
    NodeStatus status;
    string val;
};

struct Map{
    size_t sz;
    size_t cap;
    HashNode* node;
};

Map hashOpen_create(size_t capacity);
void hashOpen_destroy(Map& hashOpen);

size_t hash_djb2(const string& key);
size_t hash_fnv1a(const string& key);
size_t hash_step(const string& key, size_t cap);

int hashOpen_find(const Map& hashOpen, const string& find_value,bool is_lineal = true);
void hashOpen_insert_lineal(Map& hashOpen, const string& new_value);
void hashOpen_insert_double(Map& hashOpen,const string& new_value);
bool hashOpen_del(Map& hashOpen, const string& del_value,bool is_lineal = true);

void restruct_map(Map& hashOpen,bool is_lineal = true);
#endif