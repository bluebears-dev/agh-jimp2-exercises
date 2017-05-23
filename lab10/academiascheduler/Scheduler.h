//
// Created by pgorski42 on 22.05.17.
//

#ifndef JIMP_EXERCISES_SCHEDULER_H
#define JIMP_EXERCISES_SCHEDULER_H

#include <vector>
#include <set>
#include <map>
#include <exception>
#include <cstring>
#include <algorithm>

namespace academia {
    class SchedulingItem {
    public:
        SchedulingItem(int course_id, int teacher_id, int room_id, int time_slot, int year);

        int CourseId() const;

        int TeacherId() const;

        int RoomId() const;

        int TimeSlot() const;

        int Year() const;

    private:
        int course_id_;
        int teacher_id_;
        int room_id_;
        int time_slot_;
        int year_;
    };

    class Schedule {
    public:
        Schedule() = default;

        Schedule(const std::vector<SchedulingItem> &items) : items_(items) {};

        SchedulingItem operator[](unsigned int index) const;

        Schedule OfTeacher(int teacher_id) const;

        Schedule OfRoom(int room_id) const;

        Schedule OfYear(int year) const;

        std::vector<int> AvailableTimeSlots(int n_time_slots) const;

        void InsertScheduleItem(const SchedulingItem &item);

        size_t Size() const;

    private:
        std::vector<SchedulingItem> items_;
    };

    class NoViableSolutionFound : public std::runtime_error {
    public:
        NoViableSolutionFound() : std::runtime_error("Cannot create schedule.") {};
    };

    class Scheduler {
    public:
        virtual ~Scheduler() = default;
        virtual Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                    const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                    const std::map<int, std::set<int>> &courses_of_year,
                                    int n_time_slots
        ) const = 0;
    };

    class GreedyScheduler : public Scheduler {
    public:
        GreedyScheduler() = default;

        Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                    const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                    const std::map<int, std::set<int>> &courses_of_year,
                                    int n_time_slots) const override;

    private:
        void CheckIfPossible(const std::vector<int> &rooms,
                             const std::map<int, std::set<int>> &courses_of_year,
                             int n_time_slots) const;
        std::map<int, std::vector<int>>::const_iterator FindTeacher(const std::map<int, std::vector<int>> &teacher_courses_assignment, int course) const;
    };
}

#endif //JIMP_EXERCISES_SCHEDULER_H
