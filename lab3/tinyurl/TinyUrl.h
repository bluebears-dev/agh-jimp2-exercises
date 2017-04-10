//
// Created by pgorski42 on 10.04.17.
//

#ifndef JIMP_EXERCISES_TINYURL_H
#define JIMP_EXERCISES_TINYURL_H

#include <utility>
#include <string>
#include <array>
#include <map>
#include <memory>

namespace tinyurl {

    struct TinyUrlCodec {
        std::array<char, 6> state;
        std::map<std::array<char, 6>, std::string> hash_map;
    };

    char shift(char chr);

    std::unique_ptr<TinyUrlCodec> Init();
    void NextHash(std::array<char, 6> *state);
    std::string Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec);
    std::string Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash);
}

#endif //JIMP_EXERCISES_TINYURL_H
