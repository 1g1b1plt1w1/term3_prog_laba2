#include "hash_open.h"
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

static const size_t HASHMAX     = 256 * 256;
static const double LOAD_LIMIT  = 0.9;

static size_t hash_index(const string& key, size_t cap) {
    return hash<string>{}(key) % cap;
}

static void HashOpen_alloc(HashOpen& h, size_t capacity) {
    if (capacity > HASHMAX) throw length_error("Объём превысил максимум");
    h.cap = (capacity < 16) ? 16 : capacity;
    h.size = 0;
    h.tab = new HashOpenEntry[h.cap];
    for (size_t i = 0; i < h.cap; i++) {
        h.tab[i].key.clear();
        h.tab[i].val.clear();
        h.tab[i].st = HOPEN_EMPTY;
    }
}

HashOpen HashOpen_create(size_t capacity) {
    HashOpen h{};
    HashOpen_alloc(h, capacity);
    return h;
}

void HashOpen_destroy(HashOpen& h) {
    delete[] h.tab;
    h.tab  = nullptr;
    h.cap  = 0;
    h.size = 0;
}

double HashOpen_load(const HashOpen& h) {
    if (h.cap == 0) return 0.0;
    return (double)h.size / (double)h.cap;
}

static void HashOpen_insert_direct(HashOpen& h, const string& k, const string& v) {
    size_t idx = hash_index(k, h.cap);
    size_t first_del = (size_t)-1;

    for (size_t i = 0; i < h.cap; i++) {
        size_t p = (idx + i) % h.cap;
        auto& e = h.tab[p];

        if (e.st == HOPEN_USED) {
            if (e.key == k) { e.val = v; return; } 
        } else if (e.st == HOPEN_DEL) {
            if (first_del == (size_t)-1) first_del = p;
        } else { // EMPTY
            size_t pos = (first_del == (size_t)-1) ? p : first_del;
            h.tab[pos].key = k;
            h.tab[pos].val = v;
            h.tab[pos].st  = HOPEN_USED;
            h.size++;
            return;
        }
    }
}

void HashOpen_restruct(HashOpen& h) {
    size_t new_cap = h.cap * 2;
    if (new_cap > HASHMAX) throw length_error("Объём превысил максимум");

    HashOpen nh{}; 
    HashOpen_alloc(nh, new_cap);

    for (size_t i = 0; i < h.cap; i++) {
        const auto& e = h.tab[i];
        if (e.st == HOPEN_USED) {
            HashOpen_insert_direct(nh, e.key, e.val);
        }
    }

    HashOpen_destroy(h);
    h = nh;
}

void HashOpen_put(HashOpen& h, string key, string val) {
    if (HashOpen_load(h) >= LOAD_LIMIT) HashOpen_restruct(h);
    HashOpen_insert_direct(h, key, val);
}

bool HashOpen_get(const HashOpen& h, string key, string& out) {
    size_t idx = hash_index(key, h.cap);
    for (size_t i = 0; i < h.cap; i++) {
        size_t p = (idx + i) % h.cap;
        const auto& e = h.tab[p];
        if (e.st == HOPEN_EMPTY) return false; 
        if (e.st == HOPEN_USED && e.key == key) { out = e.val; return true; }
    }
    return false;
}

bool HashOpen_has(const HashOpen& h, string key) {
    string dummy; 
    return HashOpen_get(h, key, dummy);
}

void HashOpen_del(HashOpen& h, string key) {
    size_t idx = hash_index(key, h.cap);
    for (size_t i = 0; i < h.cap; i++) {
        size_t p = (idx + i) % h.cap;
        auto& e = h.tab[p];
        if (e.st == HOPEN_EMPTY) return;   
        if (e.st == HOPEN_USED && e.key == key) {
            e.key.clear();
            e.val.clear();
            e.st = HOPEN_DEL;   
            h.size--;
            return;
        }
    }
}

size_t HashOpen_length(const HashOpen& h) { return h.size; }

string HashOpen_read(const HashOpen& h) {
    stringstream ss;
    for (size_t i = 0; i < h.cap; i++) {
        const auto& e = h.tab[i];
        if (e.st == HOPEN_USED)
            ss << "{" << e.key << ":" << e.val << "} ";
    }
    return ss.str();
}
