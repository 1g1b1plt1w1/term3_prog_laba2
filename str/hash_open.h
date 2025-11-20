#ifndef HASH_OPEN_H
#define HASH_OPEN_H

#include <string>
using namespace std;

enum HashOpenState : unsigned char { HOPEN_EMPTY = 0, HOPEN_USED = 1, HOPEN_DEL = 2 };

struct HashOpenEntry {
    string key;
    string val;
    HashOpenState st;
};

struct HashOpen {
    size_t cap;
    size_t size;
    HashOpenEntry* tab;
};

HashOpen HashOpen_create(size_t capacity);
void     HashOpen_destroy(HashOpen& h);

void     HashOpen_put(HashOpen& h, string key, string val);
bool     HashOpen_get(const HashOpen& h, string key, string& out);
bool     HashOpen_has(const HashOpen& h, string key);
void     HashOpen_del(HashOpen& h, string key);


double   HashOpen_load(const HashOpen& h);
void     HashOpen_restruct(HashOpen& h);
size_t   HashOpen_length(const HashOpen& h);
string   HashOpen_read(const HashOpen& h); 

#endif