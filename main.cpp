#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "linked_list.h"
#include "one_linked_list.h"
#include "array.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"
#include "hash_open.h"
#include "hash_chain.h"
#include "Set.h"
#include "lru.h"
#include "task1.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
using namespace std;

void tasks(int choise){
    switch(choise){
        case 1:{
            string expr; 
            cin >> expr;

            string out;
            if(!eval_logic_with_stack(expr, out)) cout << "ERROR\n";
            else cout << out << "\n";
            break;
        }
        case 3: {
            cout << "Введите множество подмножеств в формате {{1,2,3},{2,3,4},...}:\n";
            string line;
            cin >> ws;
            getline(cin, line);

            vector<Set> sets = parse_subsets(line);

            if (sets.size() < 2) {
                cout << "Недостаточно множеств.\n";
                return;
            }

            size_t best = 0;
            int bi = -1, bj = -1;

            for (int i = 0; i < sets.size(); ++i) {
                for (int j = i + 1; j < sets.size(); ++j) {
                    size_t k = intersection_size(sets[i], sets[j]);
                    if (k > best) {
                        best = k;
                        bi = i;
                        bj = j;
                    }
                }
    }

        cout << "Множество 1: " << Set_to_string(sets[bi]) << "\n";
        cout << "Множество 2: " << Set_to_string(sets[bj]) << "\n";
        cout << "Общих элементов: " << best << "\n";
        break;
        }  
        case 4:{
            
                Array arr = Array_create(8);
            
                cout << "Введите элементы массива через пробел:\n";
                string val;
                while (cin >> val) {
                    Array_push_back(arr, val);
                    if (cin.peek() == '\n') break;
                }
            
                Array subset = Array_create(8);
            
                cout << "\nВсе различные подмассивы:\n";
                generate_subarrays(arr, subset, 0);
            
                Array_destroy(subset);
                Array_destroy(arr);
                break;
        }
        case 5:{
            Tree t = Tree_create();

            int x;
            cin >> x;
            while (x != 0) {
                t.root = Tree_insert(t.root, x);
                cin >> x;
            }

            if (check_avl(t.root)) cout << "YES\n";
            else cout << "NO\n";

            break;
        }
        case 7: {
            int cap, Q;{{1, 2, 3}, {2, 3, 4}, {5, 6}, {3, 4, 5}}
            cin >> cap >> Q;
        
            LRU c = LRU_create(cap);
        
            for (int i = 0; i < Q; i++) {
                string cmd;
                cin >> cmd;
        
                if (cmd == "SET") {
                    string x, y;
                    cin >> x >> y;
                    LRU_set(c, x, y);
                }
                else if (cmd == "GET") {
                    string x;
                    cin >> x;
                    cout << LRU_get(c, x) << " ";
                }
            }
            cout << "\n";
            break;
        }
        
    }
}

int main(){
    int choise;
    cout << "Enter task ";
    cin >> choise;
    while(choise != 0){
        tasks(choise);
        cout <<"Enter task ";
        cin >> choise;
    }
}