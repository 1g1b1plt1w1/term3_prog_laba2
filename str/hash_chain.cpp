#include "hash_chain.h"
#include <functional>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

static const size_t HASHMAX = 256 * 256;
static const double LOAD_LIMIT = 0.9;

static size_t hash_index(const string& key, size_t cap) {
    return std::hash<string>{}(key) % cap;
}

static Node* node_new(string s) {
    return new Node{s, nullptr, nullptr};
}

static void bucket_clear(Node* n) {
    while (n) {
        Node* nx = n->next;
        delete n;
        n = nx;
    }
}

static void HashChain_alloc(HashChain& h, size_t cap) {
    if (cap > HASHMAX) throw length_error("Объём превысил максимум");
    h.cap = (cap < 16) ? 16 : cap;
    h.size = 0;
    h.b = new Bucket[h.cap];
    for (size_t i = 0; i < h.cap; i++) h.b[i].head = nullptr;
}

HashChain HashChain_create(size_t cap) {
    HashChain h{};
    HashChain_alloc(h, cap);
    return h;
}

void HashChain_destroy(HashChain& h) {
    if (h.b) {
        for (size_t i = 0; i < h.cap; i++)
            bucket_clear(h.b[i].head);
        delete[] h.b;
        h.b = nullptr;
    }
    h.cap = 0;
    h.size = 0;
}

double HashChain_load(const HashChain& h) {
    return (double)h.size / (double)h.cap;
}

void HashChain_restruct(HashChain& h) {
    size_t new_cap = h.cap * 2;
    if (new_cap > HASHMAX) throw length_error("Объём превысил максимум");
    HashChain nh = HashChain_create(new_cap);
    for (size_t i = 0; i < h.cap; i++) {
        for (Node* cur = h.b[i].head; cur; cur = cur->next) {
            size_t j = hash_index(cur->data, nh.cap);
            Node* n = node_new(cur->data);
            n->next = nh.b[j].head;
            if (nh.b[j].head) nh.b[j].head->prev = n;
            nh.b[j].head = n;
            nh.size++;
        }
    }
    HashChain_destroy(h);
    h = nh;
}

void HashChain_add(HashChain& h, string key) {
    if (HashChain_load(h) >= LOAD_LIMIT)
        HashChain_restruct(h);
    size_t i = hash_index(key, h.cap);
    for (Node* cur = h.b[i].head; cur; cur = cur->next)
        if (cur->data == key) return;
    Node* n = node_new(key);
    n->next = h.b[i].head;
    if (h.b[i].head) h.b[i].head->prev = n;
    h.b[i].head = n;
    h.size++;
}

void HashChain_del(HashChain& h, string key) {
    size_t i = hash_index(key, h.cap);
    for (Node* cur = h.b[i].head; cur; cur = cur->next) {
        if (cur->data == key) {
            if (cur->prev) cur->prev->next = cur->next;
            else h.b[i].head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            delete cur;
            h.size--;
            return;
        }
    }
}

bool HashChain_has(const HashChain& h, string key) {
    size_t i = hash_index(key, h.cap);
    for (Node* cur = h.b[i].head; cur; cur = cur->next)
        if (cur->data == key) return true;
    return false;
}

size_t HashChain_length(const HashChain& h) { return h.size; }

string HashChain_read(const HashChain& h) {
    stringstream ss;
    for (size_t i = 0; i < h.cap; i++)
        for (Node* cur = h.b[i].head; cur; cur = cur->next)
            ss << "{" << cur->data << "} ";
    return ss.str();
}
