#ifndef HASH_OPEN_H
#define HASH_OPEN_H
#include <string>
#include <cstddef>

using namespace std;

struct Node {
    string data;
    Node* next;
    Node* prev;
};

struct Bucket {
    Node* head;
};

struct HashChain {
    size_t cap;
    size_t size;
    Bucket* b;
};

HashChain HashChain_create(size_t capacity);
void HashChain_destroy(HashChain& h);

void HashChain_add(HashChain& h, string key);
void HashChain_del(HashChain& h, string key);
bool HashChain_has(const HashChain& h, string key);

void HashChain_restruct(HashChain& h);

size_t HashChain_length(const HashChain& h);
string HashChain_read(const HashChain& h);
double HashChain_load(const HashChain& h);

#endif