#include <iostream>
#include <sstream>
#include <string>
#include "task7.h"
#include "../str/lru.h"

using namespace std;

void run_task7() {
    int cap, Q;
    cout << "Введите емкость кэша (cap): ";
    cin >> cap;
    cout << "Введите количество запросов (Q): ";
    cin >> Q;
    cin.ignore();

    Lru lru = Lru_create(cap);
    int step = 0;

    cout << "Введите запросы (SET x y / GET x):\n";

    bool first_output = true;
    for (int i = 0; i < Q; ) {
        string line;
        getline(cin, line);
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        while (ss >> token && i < Q) {
            if (token == "SET") {
                string key, val;
                if (ss >> key >> val) {
                    Lru_set(lru, key, val, step++);
                    i++;
                }
            } else if (token == "GET") {
                string key;
                if (ss >> key) {
                    string result = Lru_get(lru, key, step++);
                    if (!first_output) cout << " ";
                    cout << result;
                    first_output = false;
                    i++;
                }
            }
        }
    }

    if (!first_output) cout << endl;

    Lru_destroy(lru);
}

