#include "lru.h"
#include "linked_list.h"
#include "hash_open.h"
#include <string>
using namespace std;

LRU LRU_create(size_t capacity) {
    LRU c;
    c.cap   = capacity;
    c.order = Linked_create();
    c.map   = HashOpen_create(capacity * 2);
    return c;
}

void LRU_destroy(LRU& c) {
    Linked_destroy(c.order);
    HashOpen_destroy(c.map);
}

void LRU_touch(LRU& c, const string& key) {
    Linked_del_by_value(c.order, key);
    Linked_push_back(c.order, key);
}

void LRU_set(LRU& c, const string& key, const string& val) {
    if (HashOpen_has(c.map, key)) {
        HashOpen_put(c.map, key, val);
        LRU_touch(c, key);
        return;
    }

    if (HashOpen_length(c.map) >= c.cap) {
        if (c.order.head) {
            string victim = c.order.head->data;
            Linked_pop_front(c.order);
            HashOpen_del(c.map, victim);
        }
    }

    Linked_push_back(c.order, key);
    HashOpen_put(c.map, key, val);
}

string LRU_get(LRU& c, const string& key) {
    string val;
    if (!HashOpen_get(c.map, key, val)) {
        return "-1";
    }

    LRU_touch(c, key);
    return val;
}
