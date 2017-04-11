//
// Created by pgorski42 on 11.04.17.
//

#include "ArrayFill.h"

namespace arrays {

    void FillArray(size_t size, const ArrayFill &filler, std::vector<int> *v) {
        v->clear();
        v->reserve(size);
        for (size_t i = 0; i < size; i++) {
            v->emplace_back(filler.Value(i));
        }
    }

    IncrementalFill::IncrementalFill(int value, int step) : value_(value), step_(step) {}

    int IncrementalFill::Value(int index) const {
        return step_ * index + value_;
    }

    RandomFill::RandomFill(std::unique_ptr<std::default_random_engine> engine,
                           std::unique_ptr<std::uniform_int_distribution<int>> distribution) :
    engine_(move(engine)), distribution_(move(distribution)) {}

    int RandomFill::Value(int index) const {
        return (*distribution_)(*engine_);
    }

    SquaredFill::SquaredFill(int coefficient, int offset) : coefficient_(coefficient), offset_(offset) {}

    int SquaredFill::Value(int index) const {
        return coefficient_ * index * index + offset_;
    }

    UniformFill::UniformFill(int value) : value_(value) {}

    int UniformFill::Value(int index) const {
        return value_;
    }
}