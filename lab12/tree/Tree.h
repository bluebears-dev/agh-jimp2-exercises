//
// Created by pgorski42 on 30.05.17.
//

#ifndef JIMP_EXERCISES_TREE_H
#define JIMP_EXERCISES_TREE_H

#include <memory>

namespace tree {
    template<class T>
    class Tree {
    public:
        Tree() : value_() {};

        Tree(const T &value) {
            value_ = value;
        };

        void Insert(const Tree &element);

        bool Find(const Tree &element);

        size_t Depth();

        size_t Size();

        const T &Value() const;

    private:
        std::unique_ptr<Tree> left_;
        std::unique_ptr<Tree> right_;
        T value_;
        bool empty;
    };

    template<class T>
    void Tree<T>::Insert(const Tree<T> &element) {
        if (left_ != nullptr and right_ != nullptr) {
            if (element.value_ > value_)
                right_->Insert(element);
            else
                left_->Insert(element);
        } else {
            if (element.value_ > value_)
                right_ = std::make_unique<Tree>(Tree{element.value_});
            else
                left_ = std::make_unique<Tree>(Tree{element.value_});
            if (element.left_ != nullptr)
                this->Insert(*element.left_);
            if (element.right_ != nullptr)
                this->Insert(*element.right_);
        }
    }

    template<class T>
    bool Tree<T>::Find(const Tree<T> &element) {
        if (left_ == nullptr and right_ == nullptr)
            return element.value_ == value_;
        if (element.value_ > value_)
            return Find(right_);
        else if (element.value_ < value_)
            return Find(left_);
    }

    template<class T>
    size_t Tree<T>::Size() {
        size_t left_size = 0, right_size = 0;
        if (left_ != nullptr)
            left_size = left_->Size();
        if (right_ != nullptr)
            right_size = right_->Size();
        return 1 + left_size + right_size;
    }

    template<class T>
    size_t Tree<T>::Depth() {
        size_t left_size = 0, right_depth = 0, depth = 0;
        if (left_ != nullptr)
            left_size = left_->Depth();
        if (right_ != nullptr)
            right_depth = right_->Depth();
        depth = (left_size > right_depth) ? left_size : right_depth;
        return 1 + depth;
    }

    template <class T>
    const T &Tree<T>::Value() const {
        return value_;
    }
}
#endif //JIMP_EXERCISES_TREE_H
