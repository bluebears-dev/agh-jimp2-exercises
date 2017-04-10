//
// Created by pgorski42 on 10.04.17.
//

#include "TinyUrl.h"

namespace tinyurl {
    using std::string;
    using std::array;
    using std::map;
    using std::unique_ptr;
    using std::make_unique;


    char shift(char chr) {
        switch (chr) {
            case '9':
                chr = 'A';
                break;
            case 'Z':
                chr = 'a';
                break;
            case 'z':
                chr = '0';
                break;
            default:
                chr += 1;
        }
        return chr;
    }

    unique_ptr<TinyUrlCodec> Init() {
        return unique_ptr<TinyUrlCodec>(make_unique<TinyUrlCodec>());
    }

    void NextHash(array<char, 6> *state) {
        bool next;
        int i = 5;
        do {
            (*state)[i] = shift((*state)[i]);
            next = (*state)[i--] == '0';
        } while (next);
    }

    string Encode(const string &url, unique_ptr<TinyUrlCodec> *codec) {
        NextHash(&(*codec)->state);
        (*codec)->hash_map[(*codec)->state] = url;

        string hash;
        for (auto chr : (*codec)->state)
            hash += chr;
        return hash;
    }

    string Decode(const unique_ptr<TinyUrlCodec> &codec, const string &hash) {
        array<char, 6> state;

        if (hash.size() == 6)
            for (auto i = 0; i < 6; ++i)
                state[i] = hash[i];

        return codec->hash_map[state];
    }
}
