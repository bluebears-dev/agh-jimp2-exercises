//
// Created by pgorski42 on 04.06.17.
//

#include "TeacherHash.h"

using namespace std;

bool academia::Teacher::operator!=(const academia::Teacher &teacher) const {
    return (id_ != teacher.Id()) || (name_ != teacher.Name()) || (department_ != teacher.Department());
}

bool academia::Teacher::operator==(const academia::Teacher &teacher) const {
    return !(*this != teacher);
}

size_t academia::TeacherHash::Combine(size_t lhs, size_t rhs) const {
    return (lhs * 3 + rhs);
}

size_t academia::TeacherHash::operator()(const academia::Teacher &teacher) const {
    int id = teacher.Id();

    size_t id_hash = hash<int>()(id);
    size_t name_hash = hash<string>()(teacher.Name());
    size_t department_hash = hash<string>()(teacher.Department());

    return Combine(department_hash, Combine(id_hash, name_hash));
}
