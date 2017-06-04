//
// Created by pgorski42 on 05.06.17.
//

#ifndef JIMP_EXERCISES_SEQUENTIALGENERATOR_H
#define JIMP_EXERCISES_SEQUENTIALGENERATOR_H

template <typename T, typename U>
class SequentialIdGenerator {
public:
    SequentialIdGenerator(int start = 0) : counter_(start) {};

    T NextValue() {
        return T(counter_++);
    }

private:
    int counter_;
};

#endif //JIMP_EXERCISES_SEQUENTIALGENERATOR_H
