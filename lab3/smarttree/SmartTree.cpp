//
// Created by pgorski42 on 10.04.17.
//

#include <iostream>
#include "SmartTree.h"

namespace datastructures {
    using std::unique_ptr;
    using std::make_unique;

    using std::string;
    using std::ostream;
    using std::stringstream;

    using std::regex;
    using std::regex_replace;
    using std::smatch;

    unique_ptr<SmartTree> CreateLeaf(int value) {
        unique_ptr<SmartTree> leaf(make_unique<SmartTree>());
        leaf->value = value;
        leaf->left = nullptr;
        leaf->right = nullptr;
        return leaf;
    }

    unique_ptr<SmartTree> InsertLeftChild(unique_ptr<SmartTree> tree,
                                          unique_ptr<SmartTree> left_subtree
    ) {
        tree->left = move(left_subtree);
        return tree;
    }

    unique_ptr<SmartTree> InsertRightChild(unique_ptr<SmartTree> tree,
                                           unique_ptr<SmartTree> right_subtree
    ) {
        tree->right = move(right_subtree);
        return tree;
    }

    void PrintTreeInOrder(const unique_ptr<SmartTree> &unique_ptr, ostream *out) {
        if (unique_ptr != nullptr) {
            PrintTreeInOrder(unique_ptr->left, out);
            (*out) << unique_ptr->value << ", ";
            PrintTreeInOrder(unique_ptr->right, out);
        }
    }

    string DumpTree(const unique_ptr<SmartTree> &tree) {
        stringstream stream;
        stream << "[";
        if (tree != nullptr) {;
            stream << tree->value;
            stream << " " << DumpTree(tree->left);
            stream << " " << DumpTree(tree->right);
        }
        else
            stream << "none";
        stream << "]";
        return stream.str();
    }

    unique_ptr<SmartTree> RestoreTree(const string &tree) {
        stringstream stream;
        stream << tree.substr(1, tree.length() - 2);

        if (stream.str() != "none") {
            size_t begin = tree.find('[', 1);
            string cut_tree = tree.substr(begin, tree.size() - 1 - begin);

            int value;
            stream >> value;

            size_t split = 0, counter = 0;
            for (size_t i = 0; i < cut_tree.size(); ++i) {
                if (cut_tree[i] == '[')
                    counter += 1;
                else if (cut_tree[i] == ']')
                    counter -= 1;
                else
                    continue;
                if (!counter) {
                    split = i;
                    i = cut_tree.size();
                }
            }

            auto node = CreateLeaf(value);
            node->left = move(RestoreTree(cut_tree.substr(0, split + 1)));
            node->right = move(RestoreTree(cut_tree.substr(split + 2)));
            return node;
        }
        return nullptr;
    }
}
