//
// Created by pgorski42 on 02.04.17.
//

#include "TextPool.h"

using namespace pool;
using namespace std;

TextPool::TextPool(std::experimental::string_view &str) {
    pool.insert(str);
}

TextPool::TextPool(const initializer_list<experimental::string_view> &elements) {
    for (auto el : elements)
        if (pool.find(el) == pool.end())
            pool.insert(el);
}

TextPool::~TextPool() {
    pool.clear();
}

TextPool::TextPool(TextPool &&text_pool) {
    swap(this->pool, text_pool.pool);
}

TextPool &TextPool::operator=(TextPool &&text_pool) {
    if (this == &text_pool)
        return *this;
    swap(this->pool, text_pool.pool);
    return *this;
}

experimental::string_view TextPool::Intern(string const &str) {
    auto el = pool.find(str);
    if (el == pool.end())
        return *(pool.insert(experimental::string_view(str)).first);
    return *el;
}

size_t TextPool::StoredStringCount() const {
    return pool.size();
}
