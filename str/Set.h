#ifndef SET_H
#define SET_H
#include <string>
#include <vector>
#include "hash_open.h"
using namespace std;

struct Set {
    HashOpen map; 
};

Set   Set_create(size_t capacity = 128);
void  Set_destroy(Set& s);

void  Set_add(Set& s, string value);
void  Set_del(Set& s, string value);
bool  Set_has(const Set& s, string value);

size_t Set_length(const Set& s);
string Set_read(const Set& s);
vector<string> Set_keys(const Set& s);
#endif