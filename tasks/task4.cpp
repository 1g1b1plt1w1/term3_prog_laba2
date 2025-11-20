#include <iostream>
#include <string>
#include "task4.h"
#include "array.h"
using namespace std;


void generate_subarrays(const Array& src, Array& subset, size_t index) {
    if (index == Array_length(src)) {
        cout << "{";
        for (size_t i = 0; i < Array_length(subset); i++) {
            cout << Array_get(subset, i);
            if (i + 1 < Array_length(subset)) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    generate_subarrays(src, subset, index + 1);


    Array_push_back(subset, Array_get(src, index));
    generate_subarrays(src, subset, index + 1);

    subset.size--;
}