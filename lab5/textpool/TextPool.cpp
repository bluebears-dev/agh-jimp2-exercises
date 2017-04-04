//
// Created by pgorski42 on 02.04.17.
//

#include "TextPool.h"

using namespace pool;
using namespace std;

TextPool::TextPool(std::experimental::string_view &str) {
    pool_.insert(str);
}

TextPool::TextPool(const initializer_list<experimental::string_view> &elements) {
    for (auto el : elements)
        pool_.insert(el);
}

TextPool::TextPool(TextPool &&text_pool) {
    swap(this->pool_, text_pool.pool_);
}

TextPool &TextPool::operator=(TextPool &&text_pool) {
    if (this != &text_pool)
        swap(this->pool_, text_pool.pool_);
    return *this;
}

experimental::string_view TextPool::Intern(string const &str) {
    auto el = pool_.insert(experimental::string_view(str)).first;
    return *el;
}

size_t TextPool::StoredStringCount() const {
    return pool_.size();
}
