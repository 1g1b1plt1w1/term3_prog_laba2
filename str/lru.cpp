#include <iostream>
#include "lru.h"
#include <climits>
constexpr int MAX_CAP = 256*256;

Lru Lru_create(const int& capacity){
    Lru lru{0,0,nullptr};
    lru.cap = (capacity < MAX_CAP)? capacity:MAX_CAP;
    lru.node = new LruNode[capacity];
    return lru;
}

void Lru_destroy(Lru& lru){
    delete[] lru.node;
    lru.node = nullptr;
    lru.sz = 0;
    lru.cap = 0;
}

string Lru_get(const Lru& lru,const string& x,const int& step){
    for (int i = 0;i < lru.cap;i++){
            if (lru.node[i].key == x){
                lru.node[i].last_used = step;
                return lru.node[i].value;
            }
        }
    return "-1";
}

void update_lru_node(Lru& lru,const string& x,const string& y,const int& step,const size_t idx){
    lru.node[idx].key = x;
    lru.node[idx].value = y;
    lru.node[idx].last_used = step + 1;
}

void Lru_set(Lru& lru,const string& x,const string& y,const int& step){

    for (int i = 0;i < (int)lru.sz;i++){
        if (lru.node[i].key == x){
            update_lru_node(lru,x,y,step,i);
            return;
        }
    }
    size_t del_idx = 0;
    int min_last_used = INT_MAX;
    if (lru.sz >= lru.cap){
        for (int i = 0;i < (int)lru.cap;i++){
            if (lru.node[i].last_used < min_last_used){
                min_last_used = lru.node[i].last_used;
                del_idx = i;
            }
        }
        update_lru_node(lru,x,y,step,del_idx);
    } else{
        update_lru_node(lru,x,y,step,lru.sz);
        lru.sz++;
    }
}