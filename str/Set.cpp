#include "Set.h"

Set Set_create(size_t capacity){
    Set s;
    s.map = HashOpen_create(capacity);
    return s;
}

void Set_destroy(Set& s){
    HashOpen_destroy(s.map);
}

void Set_add(Set& s, string value){
    HashOpen_put(s.map, value, "1");
}

void Set_del(Set& s, string value){
    HashOpen_del(s.map, value);
}

bool Set_has(const Set& s, string value){
    return HashOpen_has(s.map, value);
}

size_t Set_length(const Set& s){
    return HashOpen_length(s.map);
}

string Set_read(const Set& s){
    string all = HashOpen_read(s.map);
    string out;
    out.reserve(all.size());
    bool in_key=false, after_colon=false;
    for(char c: all){
        if(c=='{'){ in_key=true; after_colon=false; out.push_back('{'); continue; }
        if(c=='}'){ in_key=false; out.push_back('}'); out.push_back(' '); continue; }
        if(!in_key){ continue; }
        if(c==':'){ after_colon=true; continue; }
        if(!after_colon){ out.push_back(c); }
    }
    return out;
}
vector<string> Set_keys(const Set& s) {
    vector<string> out;
    string raw = HashOpen_read(s.map);
    string num;
    bool in_key = false, after_colon = false;

    for (char c : raw) {
        if (c == '{') {
            in_key = true;
            after_colon = false;
            num.clear();
            continue;
        }
        if (c == '}') {
            in_key = false;
            if (!num.empty()) out.push_back(num);
            continue;
        }
        if (!in_key) continue;
        if (c == ':') {
            after_colon = true;
            continue;
        }
        if (!after_colon) num.push_back(c);
    }

    return out;
}


