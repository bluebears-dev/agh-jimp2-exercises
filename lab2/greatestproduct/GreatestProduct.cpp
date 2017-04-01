//
// Created by pgorski42 on 01.04.17.
//

#include <iostream>
#include "GreatestProduct.h"

using namespace std;

void fill(vector<int> &list, int k, int value) {
    for (auto i = 0; i < k; ++i)
        list.push_back(value);
}

int GreatestProduct(const vector<int> &numbers, int k) {
    if (k > numbers.size()) {
        cerr << "Given number is larger than vector." << endl;
        return 0;
    }

    vector<int> largest;
    vector<int> smallest;

    fill(largest, k, numeric_limits<int>::min());
    fill(smallest, k, numeric_limits<int>::max());
    for (const auto number : numbers) {
        for (auto i = largest.begin(); i < largest.end(); ++i)
            if (*i < number) {
                largest.insert(i, number);
                largest.pop_back();
                i = largest.end();
            }
        for (auto i = smallest.begin(); i < smallest.end(); ++i)
            if (*i > number) {
                smallest.insert(i, number);
                smallest.pop_back();
                i = smallest.end();
            }
    }

    auto large = largest.begin(),
         small = smallest.begin();

    auto product = 1;
    for (auto i = k; i > 0; i -= 2) {
        int first  = *large * *(large + 1),
            second = *small * *(small + 1);

        // Special case if k is odd
        if (i == 3) {
            if (first * *(large + 2) > *large * second)
                product *= first * *(large + 2);
            else
                product *= *large * second;
            i = 0; // end loop
        }
        else {
            if (first > second) {
                product *= first ;
                large += 2;
            } else {
                product *= second;
                small += 2;
            }
        }
    }

    return product;
}
