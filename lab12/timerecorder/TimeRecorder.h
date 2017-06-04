//
// Created by pgorski42 on 04.06.17.
//

#ifndef JIMP_EXERCISES_ELAPSED_H
#define JIMP_EXERCISES_ELAPSED_H

#include <chrono>
#include <ctime>
#include <utility>

namespace profiling {
    template<typename T>
    auto TimeRecorder(T object) {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        auto return_value = object();
        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_time = end - start;
        return std::make_pair(return_value, elapsed_time.count() * 1000);
    };
}
#endif //JIMP_EXERCISES_ELAPSED_H
