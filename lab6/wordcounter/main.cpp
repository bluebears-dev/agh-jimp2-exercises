//
// Created by pgorski42 on 13.04.17.
//

#include <iostream>
#include <WordCounter.h>

using namespace std;
using namespace datastructures;

int main() {
    WordCounter counter {Word("a"), Word("p"), Word("a"), Word("a"), Word("hi"), Word("voltage")};
    set<Word> expected_words {Word("a"),Word("hi"), Word("voltage"), Word("p")};
    counter.Words();
    for (auto i : expected_words)
        cout << i.Get() << endl;
    return 0;
}