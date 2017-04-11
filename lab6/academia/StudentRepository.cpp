//
// Created by pgorski42 on 04.04.17.
//

#include "StudentRepository.h"

namespace academia {
    using std::ostream;
    using std::istream;

    using std::initializer_list;
    using std::string;

    StudyYear::StudyYear(int student_year) {
        year_ = student_year;
    }

    StudyYear &StudyYear::operator++() {
        ++year_;
        return *this;
    }

    StudyYear &StudyYear::operator--() {
        --year_;
        return *this;
    }

    bool StudyYear::operator<(const StudyYear &student_year) const {
        return this->year_ < student_year.year_;
    }

    bool StudyYear::operator==(const StudyYear &student_year) const {
        return this->year_ == student_year.year_;
    }

    StudyYear::operator int() const {
        return year_;
    }

    ostream &operator<<(ostream &stream, const StudyYear &study_year) {
        stream << "StudyYear - " << study_year.year_;
        return stream;
    }

    istream &operator>>(istream &stream, StudyYear &study_year) {
        string str;
        stream >> str;
        stream >> str;
        stream >> str;
        study_year.year_ = stoi(str);
        return stream;
    }

    Student::Student(string id, string first_name, string last_name, string program, StudyYear year)
        : id_(id), first_name_(first_name), last_name_(last_name), program_(program), year_(year){}

    const string &Student::Id() const {
        return id_;
    }

    const string &Student::FirstName() const {
        return first_name_;
    }

    const string &Student::LastName() const {
        return last_name_;
    }

    const string &Student::Program() const {
        return program_;
    }

    const StudyYear &Student::Year() const {
        return year_;
    }

    void Student::ChangeLastName(const string &last_name) {
        last_name_ = last_name;
    }

    bool Student::operator==(const Student &student) const {
        return (id_ == student.id_ and first_name_ == student.first_name_ and
                last_name_ == student.last_name_ and
                program_ == student.program_ and
                year_ == student.year_);
    }

    StudentRepository::StudentRepository() {
        // sentinel node
        repository_.push_back(Student{"-1", 0, 0, 0, 0});
    }

    StudentRepository::StudentRepository(const initializer_list<Student> &elements) {
        this->repository_ = elements;
        repository_.push_back(Student{"-1", 0, 0, 0, 0});
    }

    Student &StudentRepository::operator[](string id) {
        for (auto i = repository_.begin(); i != repository_.end(); ++i)
            if (i->Id() == id)
                return *i;
        return *repository_.end();
    }

    bool StudentRepository::operator==(const StudentRepository &student_repository) const {
        for (auto i = repository_.begin(); i != repository_.end(); ++i) {
            bool found = false;
            for (auto j = student_repository.repository_.begin(); j != student_repository.repository_.end() and !found; ++j) {
                if (*i == *j)
                    found = true;
            }
            if (!found)
                return false;
        }
        return true;
    }

    size_t StudentRepository::StudentCount() const {
        return repository_.size();
    }
}