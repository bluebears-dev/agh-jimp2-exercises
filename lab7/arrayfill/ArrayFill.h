//
// Created by pgorski42 on 11.04.17.
//

#ifndef JIMP_EXERCISES_ARRAYFILL_H
#define JIMP_EXERCISES_ARRAYFILL_H

#include <vector>
#include <string>
#include <random>
#include <memory>

namespace arrays {

    class ArrayFill {
    public:
        virtual ~ArrayFill() = default;

        virtual int Value(int index) const = 0;
    };

    void FillArray(size_t size, const ArrayFill &filler, std::vector<int> *v);

    class IncrementalFill : public ArrayFill {
        int value_;
        int step_;
    public:
        IncrementalFill(int value, int step = 1);

        virtual int Value(int index) const override;
    };

    class RandomFill : public ArrayFill {
        std::unique_ptr<std::default_random_engine> engine_;
        std::unique_ptr<std::uniform_int_distribution<int>> distribution_;
    public:
        RandomFill(std::unique_ptr<std::default_random_engine> engine,
                   std::unique_ptr<std::uniform_int_distribution<int>> distribution);
        virtual int Value(int index) const override;
    };

    class SquaredFill : public ArrayFill {
        int offset_;
        int coefficient_;
    public:
        SquaredFill(int coefficient = 1, int offset = 0);
        virtual int Value(int index) const override;
    };

    class UniformFill : public ArrayFill {
        int value_;
    public:
        UniformFill(int value = 0);
        virtual int Value(int index) const override;
    };
}

#endif //JIMP_EXERCISES_ARRAYFILL_H
