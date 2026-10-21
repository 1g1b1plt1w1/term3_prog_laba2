#include <open_hash.h>
#include <iostream>
#include <utility>
constexpr size_t MAX_CAP = 256*256;
using namespace std;
Map hashOpen_create(size_t capacity){
    Map hashOpen = {0, 0, nullptr};
    if (capacity > MAX_CAP){
        throw length_error("Слишком большой capacity");
    }
    hashOpen.cap = (capacity > 16)? capacity : 16; 
    hashOpen.node = new HashNode[hashOpen.cap];
    for (size_t i = 0; i < hashOpen.cap; i++){
        hashOpen.node[i].status = NodeStatus::EMPTY;
    }
    return hashOpen;
}

void hashOpen_destroy(Map& hashOpen){
    delete[] hashOpen.node;
    hashOpen.node = nullptr;
    hashOpen.sz = 0;
    hashOpen.cap = 0;
}

size_t hash_djb2(const string& key){
    size_t hash = 5381;
    for (const unsigned char c:key){
        hash = ((hash<<5) + hash) + c;
    }
    return hash;
}

size_t hash_fnv1a(const string& key) {
    size_t hash = 14695981039346656037ULL;
    for (unsigned char c : key) {
        hash ^= c;
        hash *= 1099511628211ULL;
    }
    return hash;
}

size_t hash_step(const string& key, size_t cap) {
    size_t step = hash_fnv1a(key) % cap;
    if (step % 2 == 0) {
        step++;
    }
    return step;
}

int hashOpen_find(const Map& hashOpen,const string& find_value,bool is_lineal){
    int idx = hash_djb2(find_value) % hashOpen.cap;
    if (hashOpen.node[idx].status == NodeStatus::USED
        && hashOpen.node[idx].val == find_value){
        return idx;
    } else if(hashOpen.node[idx].status == NodeStatus::EMPTY){
        return -1;
    } else{
        size_t step;
        if (is_lineal){
            for (int i = (idx + 1) % hashOpen.cap; i != idx; i = (i + 1) % hashOpen.cap){
            if (hashOpen.node[i].status == NodeStatus::USED &&
                hashOpen.node[i].val == find_value){
                return i;
            }
            if (hashOpen.node[i].status == NodeStatus::EMPTY){
                return -1;
            }
        }
        }
        else {
            step = hash_step(find_value,hashOpen.cap);
            for (int i = (idx + step) % hashOpen.cap;i != idx;i = (i+ step)% hashOpen.cap){
            if (hashOpen.node[i].status == NodeStatus::USED &&
                hashOpen.node[i].val == find_value){
                return i;
            }
            if (hashOpen.node[i].status == NodeStatus::EMPTY){
                return -1;
            }
        }
        };
        return -1;
    }
}

void hashOpen_insert_lineal(Map& hashOpen,const string& new_value){

    if (hashOpen_find(hashOpen,new_value) != -1){
        return;
    }

    if (hashOpen.sz == hashOpen.cap){
        throw out_of_range("Таблица переполнена");
    }
    int idx = hash_djb2(new_value) % hashOpen.cap;
    if (hashOpen.node[idx].status == NodeStatus::EMPTY ||
        hashOpen.node[idx].status == NodeStatus::DELETED){
        hashOpen.node[idx].val = new_value;
        hashOpen.node[idx].status = NodeStatus::USED;
    } else{
        int new_idx = -1;
        for (int i = (idx + 1) % hashOpen.cap; i != idx; i = (i + 1) % hashOpen.cap){
            if (hashOpen.node[i].status == NodeStatus::EMPTY ||
                hashOpen.node[i].status == NodeStatus::DELETED){
                new_idx = i;
                break;
            }
        }
        if (new_idx == -1) {
            throw out_of_range("Таблица переполнена");
        }
        hashOpen.node[new_idx].val = new_value;
        hashOpen.node[new_idx].status = NodeStatus::USED;
    }
    hashOpen.sz++;

    if (static_cast<double>(hashOpen.sz) / hashOpen.cap > 0.9){
        restruct_map(hashOpen);
    }
}

void hashOpen_insert_double(Map& hashOpen,const string& new_value){

    if (hashOpen_find(hashOpen,new_value) != -1){
        return;
    }

    if (hashOpen.sz == hashOpen.cap){
        throw out_of_range("Таблица переполнена");
    }
    int idx = hash_djb2(new_value) % hashOpen.cap;
    if (hashOpen.node[idx].status == NodeStatus::EMPTY ||
        hashOpen.node[idx].status == NodeStatus::DELETED){
        hashOpen.node[idx].val = new_value;
        hashOpen.node[idx].status = NodeStatus::USED;
    } else{
        int new_idx = -1;
        size_t step = hash_step(new_value,hashOpen.cap);
        for (int i = (idx + step) % hashOpen.cap;i != idx;i = (i+ step)% hashOpen.cap){
            if (hashOpen.node[i].status == NodeStatus::EMPTY ||
                hashOpen.node[i].status == NodeStatus::DELETED){
                new_idx = i;
                break;
            }
        }
        if (new_idx == -1) {
            throw out_of_range("Таблица переполнена");
        }
        hashOpen.node[new_idx].val = new_value;
        hashOpen.node[new_idx].status = NodeStatus::USED;
    }
    hashOpen.sz++;

    if (static_cast<double>(hashOpen.sz) / hashOpen.cap > 0.9){
        restruct_map(hashOpen);
    }
}

bool hashOpen_del(Map& hashOpen,const string& del_value,bool is_lineal){
    int idx = hashOpen_find(hashOpen,del_value,is_lineal);
    if (idx == -1){
        return false;
    }
    hashOpen.node[idx].status = NodeStatus::DELETED;
    hashOpen.node[idx].val.clear();
    hashOpen.sz --;
    return true;
}

void restruct_map(Map& hashOpen,bool is_lineal){
    Map new_hashOpen = hashOpen_create(hashOpen.cap * 2);
    if (is_lineal){
    for (size_t i = 0; i < hashOpen.cap; i++){
        if (hashOpen.node[i].status == NodeStatus::USED){
            hashOpen_insert_lineal(new_hashOpen,hashOpen.node[i].val);
        }
    }
    }
    else{
        for (size_t i = 0; i < hashOpen.cap; i++){
        if (hashOpen.node[i].status == NodeStatus::USED){
            hashOpen_insert_double(new_hashOpen,hashOpen.node[i].val);
        }
    }
    }

    swap(hashOpen.node,new_hashOpen.node);
    swap(hashOpen.sz,new_hashOpen.sz);
    swap(hashOpen.cap,new_hashOpen.cap);
    hashOpen_destroy(new_hashOpen);
}