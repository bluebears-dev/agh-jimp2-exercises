//
// Created by pgorski42 on 04.06.17.
//

#ifndef JIMP_EXERCISES_TEACHERHASH_H
#define JIMP_EXERCISES_TEACHERHASH_H

#include <string>
#include <algorithm>

namespace academia {

    class TeacherId {
    public:
        TeacherId(int id) : id_(id) {};

        operator int() const {
            return id_;
        }

    private:
        int id_;
    };

    class Teacher {
    public:
        Teacher(TeacherId id, const char *name, const char *department) : id_(id), name_(name), department_(department) {}

        const TeacherId &Id() const {
            return id_;
        }

        const std::string &Name() const {
            return name_;
        }

        const std::string &Department() const {
            return department_;
        }

        bool operator!=(const Teacher &teacher) const;
        bool operator==(const Teacher &teacher) const;

    private:
        TeacherId id_;
        std::string name_;
        std::string department_;
    };

    class TeacherHash {
    public:
        size_t operator()(const Teacher &teacher) const;
        size_t Combine(size_t lhs, size_t rhs) const;
    };
}

#endif //JIMP_EXERCISES_TEACHERHASH_H
