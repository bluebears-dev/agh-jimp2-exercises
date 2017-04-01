//
// Created by pgorski42 on 01.04.17.
//

#ifndef JIMP_EXERCISES_XORCYPHERBREAKER_H
#define JIMP_EXERCISES_XORCYPHERBREAKER_H

#include <string>
#include <vector>
#include <algorithm>

char Xor(char chr, char key);
std::vector<std::string> xor_decrypt(const std::vector<char> &cryptogram, int key_length, const std::string &key);
int match_with(const std::vector<std::string> &text, const std::vector<std::string> &dictionary);
void next_key(std::string &key);
std::string XorCypherBreaker(const std::vector<char> &cryptogram,
                             int key_length,
                             const std::vector<std::string> &dictionary);

#endif //JIMP_EXERCISES_XORCYPHERBREAKER_H
