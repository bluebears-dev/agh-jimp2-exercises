//
// Created by pgorski42 on 01.04.17.
//

#ifndef JIMP_EXERCISES_POLYBIUS_H
#define JIMP_EXERCISES_POLYBIUS_H

#include <string>
#include <map>

std::string ToLowercase(const std::string &str);
std::string SwapChars(const std::string &str, char current, char after);

std::string PolybiusCrypt(std::string message);
std::string PolybiusDecrypt(std::string crypted);

#endif //JIMP_EXERCISES_POLYBIUS_H
