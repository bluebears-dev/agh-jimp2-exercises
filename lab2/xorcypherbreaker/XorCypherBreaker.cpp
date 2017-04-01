//
// Created by pgorski42 on 01.04.17.
//

#include <iostream>
#include "XorCypherBreaker.h"


using namespace std;

char Xor(char chr, char key) {
    return chr ^ key;
}

vector<string> xor_decrypt(const vector<char> &cryptogram, int key_length, const string &key) {
    vector<string> output;
    string str;
    char chr;
    for (auto i = 0; i < cryptogram.size(); ++i) {
        chr = Xor(cryptogram[i], key[i % key_length]);
        if (chr == ' ') {
            output.push_back(str);
            str = "";
        }
        else
            str += chr;
    }
    output.push_back(str);
    return output;
}

int match_with(const vector<string> &text, const vector<string> &dictionary) {
    int matches = 0;
    for (const auto &word : text)
        if (find(dictionary.begin(), dictionary.end(), word) != dictionary.end())
            matches += 1;
    return matches;
}

void next_key(std::string &key) {
    long current = key.length() - 1;
    if (key == "zzz")
        key = "aaa";
    else
        key[current] += 1;
        while (current >= 0) {
            if (key[current] > 'z') {
                key[current] = 'a';
                key[current - 1] += 1;
            }
            current--;
        }
}

string
XorCypherBreaker(const vector<char> &cryptogram, int key_length, const vector<string> &dictionary) {
    string key = "aaa";
    vector<string> output;
    bool found = false;
    while (!found) {
        output = xor_decrypt(cryptogram, key_length, key);

        int matches = match_with(output, dictionary);
        if (matches > 0 and matches >= output.size() / 3)
            found = true;
        else
            next_key(key);
    }
    return string(key);
}


