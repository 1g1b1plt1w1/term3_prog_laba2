#ifndef LRU_H
#define LRU_H
#include <string>

using namespace std;

struct LruNode{
    int last_used = 0;
    string key;
    string value;
};

struct Lru{
    size_t cap;
    size_t sz;
    LruNode* node;
};

Lru Lru_create(const int& capacity);
string Lru_get(const Lru& lru, const string& x, const int& step);
void Lru_set(Lru& lru, const string& x, const string& y, const int& step);
void Lru_destroy(Lru& lru);
#endif