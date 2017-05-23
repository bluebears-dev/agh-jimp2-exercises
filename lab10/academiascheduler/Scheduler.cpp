//
// Created by pgorski42 on 22.05.17.
//

#include "Scheduler.h"

using namespace std;

namespace academia {
    SchedulingItem::SchedulingItem(int course_id, int teacher_id, int room_id, int time_slot, int year)
            : course_id_(course_id), teacher_id_(teacher_id), room_id_(room_id), time_slot_(time_slot), year_(year) {}

    int SchedulingItem::CourseId() const {
        return course_id_;
    }

    int SchedulingItem::TeacherId() const {
        return teacher_id_;
    }

    int SchedulingItem::RoomId() const {
        return room_id_;
    }

    int SchedulingItem::TimeSlot() const {
        return time_slot_;
    }

    int SchedulingItem::Year() const {
        return year_;
    }

    SchedulingItem Schedule::operator[](unsigned int index) const {
        if (index < items_.size())
            return items_[index];
        else
            return items_[items_.size() - 1];
    }

    Schedule Schedule::OfTeacher(int teacher_id) const {
        vector<SchedulingItem> copied_items;
        copy_if(items_.begin(), items_.end(), back_inserter(copied_items),
                [teacher_id](const auto &item) { return item.TeacherId() == teacher_id; });
        return Schedule(copied_items);
    }

    Schedule Schedule::OfRoom(int room_id) const {
        vector<SchedulingItem> copied_items;
        copy_if(items_.begin(), items_.end(), back_inserter(copied_items),
                [room_id](const auto &item) { return item.RoomId() == room_id; });
        return Schedule(copied_items);
    }

    Schedule Schedule::OfYear(int year) const {
        vector<SchedulingItem> copied_items;
        copy_if(items_.begin(), items_.end(), back_inserter(copied_items),
                [year](const auto &item) { return item.Year() == year; });
        return Schedule(copied_items);
    }

    vector<int> Schedule::AvailableTimeSlots(int n_time_slots) const {
        set<int> unavailable;
        for_each(items_.begin(), items_.end(),
                 [&unavailable](const auto &item) { unavailable.insert(item.TimeSlot()); });

        vector<int> available;
        for (auto i = 1; i <= n_time_slots; ++i)
            if (unavailable.find(i) == unavailable.end())
                available.push_back(i);

        return available;
    }

    void Schedule::InsertScheduleItem(const SchedulingItem &item) {
        items_.push_back(item);
    }

    size_t Schedule::Size() const {
        return items_.size();
    }

    void GreedyScheduler::CheckIfPossible(const std::vector<int> &rooms,
                                          const std::map<int, std::set<int>> &courses_of_year, int n_time_slots) const {
        long possibilities = rooms.size() * n_time_slots;
        long needs = 0;
        for_each(courses_of_year.begin(), courses_of_year.end(),
                 [&needs](const auto &item) { needs += item.second.size(); });
        if (needs > possibilities)
            throw NoViableSolutionFound();
    }

    Schedule GreedyScheduler::PrepareNewSchedule(const std::vector<int> &rooms,
                                                 const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                                 const std::map<int, std::set<int>> &courses_of_year,
                                                 int n_time_slots) const {
        CheckIfPossible(rooms, courses_of_year, n_time_slots);
        Schedule schedule;

        auto available_years = courses_of_year;
        for (auto i = 1; i <= n_time_slots; ++i) {
            auto available_teachers = teacher_courses_assignment;
            auto available_rooms = rooms;

            for (auto &year : available_years) {
                auto &courses = year.second;
                if (not courses.empty() and not available_teachers.empty() and not available_rooms.empty()) {
                    auto course = courses.begin();
                    auto teacher = FindTeacher(available_teachers, *course);
                    while (teacher == available_teachers.end() and course != courses.end())
                        teacher = FindTeacher(available_teachers, *(++course));

                    if (teacher != available_teachers.end()) {
                        schedule.InsertScheduleItem(
                                SchedulingItem {*course, (*teacher).first, available_rooms.back(), i, year.first});

                        available_rooms.pop_back();
                        courses.erase(course);
                        available_teachers.erase(teacher);
                    }
                }
            }
        }
        return schedule;
    }

    std::map<int, std::vector<int>>::const_iterator
    GreedyScheduler::FindTeacher(const std::map<int, std::vector<int>> &teacher_courses_assignment, int course) const {
        auto teacher = find_if(teacher_courses_assignment.begin(), teacher_courses_assignment.end(),
                               [course](const auto &item) {
                                   return find(item.second.begin(), item.second.end(), course) != item.second.end();
                               });
        return teacher;
    }
}