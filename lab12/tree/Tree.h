//
// Created by pgorski42 on 30.05.17.
//

#ifndef JIMP_EXERCISES_TREE_H
#define JIMP_EXERCISES_TREE_H

#include <memory>

template <class T>
class Tree {
public:
    Tree() = default;
    Tree(const T &value) {
        value_ = value;
    };

    void Insert(const Tree& element);
    bool Find(const Tree& element);
    size_t Depth();
    size_t Size();
private:
    std::unique_ptr<Tree> left_;
    std::unique_ptr<Tree> right_;
    T value_;
};

template <class T>
void Tree::Insert<T>(const Tree& element) {
    if (left_ != nullptr and right_ != nullptr) {
        if (element.value_ > value_)
            right_->Insert(element);
        else
            left_->Insert(element);
    } else {
        if (element.value_ > value_)
            right_ = element.value_;
        else
            left_ = element.value_;
        if (element.left_ != nullptr)
            this->Insert(*element.left_);
        if (element.right_ != nullptr)
            this->Insert(*element.right_);
    }
}

template <class T>
bool Tree::Find<T>(const Tree &element) {
    if (left_ == nullptr and right_ == nullptr)
        return element.value_ == value_;
    if (element.value_ > value_)
        return Find(right_);
    else if (element.value_ < value_)
        return Find(left_);
}

template <class T>
size_t Tree::Size<T>() {
    size_t left_size = 0, right_size = 0;
    if (left_ != nullptr)
        left_size = left_->Size();
    if (right_ != nullptr)
        right_size = right_->Size();
    return 1 + left_size + right_size;
}

template <class T>
size_t Tree::Depth<T>() {
    size_t left_size = 0, right_depth = 0, depth = 0;
    if (left_ != nullptr)
        left_size = left_->Depth();
    if (right_ != nullptr)
        right_depth = right_->Depth();
    depth = (left_size > right_depth) ? left_size : right_depth;
    return 1 + depth;
}

#endif //JIMP_EXERCISES_TREE_H
