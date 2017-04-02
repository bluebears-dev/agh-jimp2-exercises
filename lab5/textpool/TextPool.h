//
// Created by pgorski42 on 02.04.17.
//

#ifndef JIMP_EXERCISES_TEXTPOOL_H
#define JIMP_EXERCISES_TEXTPOOL_H

#include <initializer_list>
#include <string>
#include <experimental/string_view>
#include <set>
#include <utility>

namespace pool {

    class TextPool {
        std::set<std::experimental::string_view> pool;
    public:
        TextPool() = default;
        TextPool(std::experimental::string_view &str);
        TextPool(const std::initializer_list<std::experimental::string_view> &elements);
        ~TextPool();

        TextPool(const TextPool &text_pool) = delete;
        TextPool& operator=(const TextPool &text_pool) = delete;

        TextPool(TextPool &&text_pool);
        TextPool& operator=(TextPool &&text_pool);

        std::experimental::string_view Intern(const std::string &str);
        size_t StoredStringCount() const;
    };

}

#endif //JIMP_EXERCISES_TEXTPOOL_H
