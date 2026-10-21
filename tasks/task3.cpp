#include "task3.h"
#include "Set.h"
#include <iostream>

using namespace std;

int count_genome_similarity(const string& first, const string& second) {
    if (second.size() < 2 || first.size() < 2) {
        return 0;
    }

    Set second_set = Set_create();
    for (size_t i = 0; i + 1 < second.size(); i++) {
        Set_add(second_set, second.substr(i, 2));
    }

    int count = 0;
    for (size_t i = 0; i + 1 < first.size(); i++) {
        if (Set_has(second_set, first.substr(i, 2))) {
            count++;
        }
    }

    Set_destroy(second_set);
    return count;
}

void run_task3() {
    string first_genom;
    string second_genom;
    cout << "Введите первый геном: ";
    cin >> first_genom;
    cout << "Введите второй геном: ";
    cin >> second_genom;
    int count = count_genome_similarity(first_genom, second_genom);
    cout << count << endl;
}