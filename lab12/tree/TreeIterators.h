//
// Created by pgorski42 on 05.06.17.
//

#ifndef JIMP_EXERCISES_TREEITERATOR_H
#define JIMP_EXERCISES_TREEITERATOR_H

#include <Tree.h>

namespace tree {
    template <typename T>
    class TreeIterator {
    public:
        TreeIterator() = default;
        TreeIterator(Tree<T> *root) : ptr_(root) {};
        virtual ~TreeIterator() = default;

        virtual TreeIterator &operator++() = 0;
        T &operator*() {
            return *ptr_->Value();
        }
        bool operator!=(TreeIterator &iter) {
            return ptr_ != iter.ptr_;
        }
    protected:
        Tree<T> * const ptr_;
    };

    template <typename T>
    class PostOrderTreeIterator : public TreeIterator<T> {
    public:
        PostOrderTreeIterator(Tree<T> *root) : TreeIterator<T>(root) {};
        ~PostOrderTreeIterator() override {

        }

        TreeIterator<T> &operator++() override {
        }
    private:

    };

    template <typename T>
    class PostOrderTreeView {
    public:
        PostOrderTreeView(Tree<T> *root) {};
    };

    template <typename T>
    PostOrderTreeView<T> PostOrder(Tree<T> *root);
}

#endif //JIMP_EXERCISES_TREEITERATOR_H
