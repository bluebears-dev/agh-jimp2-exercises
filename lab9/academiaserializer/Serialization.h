//
// Created by pgorski42 on 09.05.17.
//

#ifndef JIMP_EXERCISES_SERIALIZATION_H
#define JIMP_EXERCISES_SERIALIZATION_H

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <initializer_list>
#include <experimental/optional>

namespace academia {
    class Serializable;

    class Serializer {
    protected:
        std::ostream *output_;
    public:
        Serializer(std::ostream *out) : output_(out) {};

        virtual ~Serializer() {};

        virtual void IntegerField(const std::string &field_name, int value) = 0;

        virtual void DoubleField(const std::string &field_name, double value) = 0;

        virtual void StringField(const std::string &field_name, const std::string &value) = 0;

        virtual void BooleanField(const std::string &field_name, bool value) = 0;

        virtual void SerializableField(const std::string &field_name, const academia::Serializable &value) = 0;

        virtual void ArrayField(const std::string &field_name,
                                const std::vector<std::reference_wrapper<const academia::Serializable>> &value) = 0;

        virtual void Header(const std::string &object_name) = 0;

        virtual void Footer(const std::string &object_name) = 0;
    };

    class Serializable {
    public:
        virtual void Serialize(Serializer *engine) const = 0;

        virtual ~Serializable() {};
    };

    class Room : public Serializable {
    public:
        enum class Type {
            COMPUTER_LAB,
            LECTURE_HALL,
            CLASSROOM
        };

        Room(int id, const std::string &name, Type type) : id_(id), name_(name), type_(type) {};
        Room(const Room &room) : id_(room.id_), name_(room.name_), type_(room.type_) {}

        void Serialize(Serializer *engine) const override;

        std::string TypeToString(Type type) const;

    private:
        int id_;
        std::string name_;
        Type type_;
    };

    class Building : public Serializable {
    public:
        Building(int id, const std::string &name, const std::initializer_list<const Room> &elements)
                : id_(id), name_(name) {
            for (auto element : elements)
                rooms_.emplace_back(element);
        }

        void Serialize(Serializer *engine) const override;

        int Id() const;

    private:
        int id_;
        std::string name_;
        std::vector<Room> rooms_;
    };

    class BuildingRepository {
    public:
        BuildingRepository(const std::initializer_list<const Building> &elements) {
            for (auto element : elements)
                buildings_.emplace_back(element);
        }

        void StoreAll(Serializer *engine) const;
        void Add(const Building &object);
        std::experimental::optional<Building> operator[](int id) const;
    private:
        std::vector<Building> buildings_;
    };

    class XmlSerializer : public Serializer {
    public:
        XmlSerializer(std::ostream *out) : Serializer(out) {}

        void IntegerField(const std::string &field_name, int value) override;

        void DoubleField(const std::string &field_name, double value) override;

        void StringField(const std::string &field_name, const std::string &value) override;

        void BooleanField(const std::string &field_name, bool value) override;

        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;

        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;

        void Header(const std::string &object_name) override;

        void Footer(const std::string &object_name) override;
    };

    class JsonSerializer : public Serializer {
    public:
        JsonSerializer(std::ostream *out) : first(true), Serializer(out) {}

        void IntegerField(const std::string &field_name, int value) override;

        void DoubleField(const std::string &field_name, double value) override;

        void StringField(const std::string &field_name, const std::string &value) override;

        void BooleanField(const std::string &field_name, bool value) override;

        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;

        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;

        void Header(const std::string &object_name) override;

        void Footer(const std::string &object_name) override;

    private:
        bool first;
    };
}

#endif //JIMP_EXERCISES_SERIALIZATION_H
