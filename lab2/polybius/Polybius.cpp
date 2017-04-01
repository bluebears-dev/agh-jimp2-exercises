//
// Created by pgorski42 on 01.04.17.
//

#include "Polybius.h"

using namespace std;

string ToLowercase(const string &str) {
    string lower("");
    for (auto ch = str.begin(); ch < str.end(); ++ch)
        lower += (*ch >= 'A' and *ch <= 'Z') ? (*ch + ' ') : *ch;
    return lower;
}

string SwapChars(const string &str, char current, char after) {
    string swapped("");
    for (auto ch = str.begin(); ch < str.end(); ++ch)
        swapped += (*ch == current) ? (after) : *ch;
    return swapped;
}

string PolybiusCrypt(string message) {
    string prepared_message(SwapChars(ToLowercase(message), 'j', 'i'));
    map<char, string> polybius_table = {{'a', "11"}, {'b', "12"}, {'c', "13"}, {'d', "14"}, {'e', "15"},
                                     {'f', "21"}, {'g', "22"}, {'h', "23"}, {'i', "24"}, {'k', "25"},
                                     {'l', "31"}, {'m', "32"}, {'n', "33"}, {'o', "34"}, {'p', "35"},
                                     {'q', "41"}, {'r', "42"}, {'s', "43"}, {'t', "44"}, {'u', "45"},
                                     {'v', "51"}, {'w', "52"}, {'x', "53"}, {'y', "54"}, {'z', "55"}};
    string crypted("");
    for (auto ch = prepared_message.begin(); ch < prepared_message.end(); ++ch)
        crypted += polybius_table[*ch];
    return crypted;
}

string PolybiusDecrypt(string crypted) {
    if (crypted.length() % 2)
        return crypted;

    map<string, char> polybius_table = {{"11", 'a'}, {"12", 'b'}, {"13", 'c'}, {"14", 'd'}, {"15", 'e'},
                                        {"21", 'f'}, {"22", 'g'}, {"23", 'h'}, {"24", 'i'}, {"25", 'k'},
                                        {"31", 'l'}, {"32", 'm'}, {"33", 'n'}, {"34", 'o'}, {"35", 'p'},
                                        {"41", 'q'}, {"42", 'r'}, {"43", 's'}, {"44", 't'}, {"45", 'u'},
                                        {"51", 'v'}, {"52", 'w'}, {"53", 'x'}, {"54", 'y'}, {"55", 'z'}};
    string encrypted("");
    string pair("");
    for (auto ch = crypted.begin(); ch < crypted.end(); ++ch) {
        pair = *ch;
        pair += *(++ch);
        encrypted += polybius_table[pair];
    }
    return encrypted;
}
