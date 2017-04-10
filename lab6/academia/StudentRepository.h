//
// Created by pgorski42 on 04.04.17.
//

#ifndef JIMP_EXERCISES_STUDENT_H
#define JIMP_EXERCISES_STUDENT_H

#include <iostream>
#include <string>
#include <initializer_list>

namespace academia {

    class StudyYear {
        int year_;
    public:
        StudyYear(int student_year = 1);

        StudyYear &operator++();
        StudyYear &operator--();

        bool operator<(const StudyYear &student_year) const;
        bool operator==(const StudyYear &student_year) const;

        operator int() const;

        friend std::ostream &operator<<(std::ostream &stream, const StudyYear& study_year);
        friend std::istream &operator>>(std::istream &stream, StudyYear& study_year);
    };

    class Student {
        std::string id_, first_name_, last_name_, program_;
        StudyYear year_;
    public:
        Student() = default;
        Student(std::string id, std::string first_name, std::string last_name, std::string program, StudyYear year);

        const std::string &Id() const;
        const std::string &FirstName() const;
        const std::string &LastName() const;
        const std::string &Program() const;
        const StudyYear &Year() const;

        bool operator==(const Student &student) const;

        void ChangeLastName(const std::string &last_name);
    };

    class StudentRepository {
    public:
        size_t StudentCount();
    };

    std::ostream &operator<<(std::ostream &stream, const StudyYear& study_year);
    std::istream &operator>>(std::istream &stream, StudyYear& study_year);
}


#endif //JIMP_EXERCISES_STUDENT_H
