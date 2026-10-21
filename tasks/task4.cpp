#include "task4.h"
#include <sstream>
#include <iostream>

using namespace std;

static int count_capitals(const string& s) {
    int cnt = 0;
    for (char c : s) {
        if (c >= 'A' && c <= 'Z') {
            cnt++;
        }
    }
    return cnt;
}

static string to_lower_case(const string& s) {
    string res = s;
    for (char& c : res) {
        if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>(c - 'A' + 'a');
        }
    }
    return res;
}

int count_stress_errors(const Array& dict, const string& text) {
    stringstream ss(text);
    string word;
    int errors = 0;

    while (ss >> word) {
        string lower_word = to_lower_case(word);
        bool in_dict = false;
        bool exact_match = false;

        for (size_t i = 0; i < Array_length(dict); i++) {
            string dict_word = Array_get(dict, i);
            if (to_lower_case(dict_word) == lower_word) {
                in_dict = true;
                if (dict_word == word) {
                    exact_match = true;
                    break;
                }
            }
        }

        if (in_dict) {
            if (!exact_match) {
                errors++;
            }
        } else {
            if (count_capitals(word) != 1) {
                errors++;
            }
        }
    }

    return errors;
}

void run_task4() {
    cout << "Введите количество слов в словаре: ";
    int dict_quantity = 0;
    if (!(cin >> dict_quantity)) {
        return;
    }
    Array dict = Array_create(dict_quantity > 0 ? dict_quantity : 16);
    for (int i = 0; i < dict_quantity; i++) {
        string temp;
        cin >> temp;
        Array_push_back(dict, temp);
    }
    string sentence;
    cout << "Введите предложение: ";
    cin.ignore();
    getline(cin, sentence);
    int errors = count_stress_errors(dict, sentence);
    cout << errors << endl;
    Array_destroy(dict);
}