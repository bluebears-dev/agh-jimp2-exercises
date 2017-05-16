//
// Created by pgorski42 on 09.05.17.
//

#include "Serialization.h"

using std::reference_wrapper;
using std::experimental::optional;
using std::vector;

namespace academia {
    std::string Room::TypeToString(Room::Type type) const {
        switch(type) {
            case Room::Type::CLASSROOM:
                return "CLASSROOM";
            case Room::Type::LECTURE_HALL:
                return "LECTURE_HALL";
            case Room::Type::COMPUTER_LAB:
                return "COMPUTER_LAB";
        }
    }

    void Room::Serialize(Serializer *engine) const {
        engine->Header("room");
        engine->IntegerField("id", id_);
        engine->StringField("name", name_);
        engine->StringField("type", TypeToString(type_));
        engine->Footer("room");
    }

    void Building::Serialize(Serializer *engine) const {
        engine->Header("building");
        engine->IntegerField("id", id_);
        engine->StringField("name", name_);

        vector<reference_wrapper<const Serializable>> rooms;
        for (const Serializable &room : rooms_)
            rooms.emplace_back(room);

        engine->ArrayField("rooms", rooms);
        engine->Footer("building");
    }

    int Building::Id() const {
        return id_;
    }

    void BuildingRepository::StoreAll(Serializer *engine) const {
        engine->Header("building_repository");
        vector<reference_wrapper<const Serializable>> array;
        for (const Serializable &element : buildings_)
            array.emplace_back(element);
        engine->ArrayField("buildings", array);
        engine->Footer("building_repository");
    }

    void BuildingRepository::Add(const Building &object) {
        buildings_.emplace_back(object);
    }

    optional<Building> BuildingRepository::operator[](int id) const {
        for (auto building : buildings_)
            if (building.Id() == id)
                return building;
        return {};
    }

    void XmlSerializer::Header(const std::string &object_name) {
        *output_ << '<' << object_name << '>';
    }

    void XmlSerializer::Footer(const std::string &object_name) {
        *output_ << "<\\" << object_name << '>';
    }

    void XmlSerializer::IntegerField(const std::string &field_name, int value) {
        Header(field_name);
        *output_ << value;
        Footer(field_name);
    }

    void XmlSerializer::DoubleField(const std::string &field_name, double value) {
        Header(field_name);
        *output_ << value;
        Footer(field_name);
    }

    void XmlSerializer::StringField(const std::string &field_name, const std::string &value) {
        Header(field_name);
        *output_ << value;
        Footer(field_name);
    }

    void XmlSerializer::BooleanField(const std::string &field_name, bool value) {
        Header(field_name);
        *output_ << value;
        Footer(field_name);
    }

    void XmlSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value) {
        Header(field_name);
        value.Serialize(this);
        Footer(field_name);
    }

    void XmlSerializer::ArrayField(const std::string &field_name,
                                   const std::vector<std::reference_wrapper<const academia::Serializable>> &value) {
        Header(field_name);
        for (const Serializable &element : value)
            element.Serialize(this);
        Footer(field_name);
    }

    void JsonSerializer::IntegerField(const std::string &field_name, int value) {
        if (first)
            first = false;
        else
            *output_ << ", ";
        *output_ << '\"' << field_name << "\": ";
        *output_ << value;
    }

    void JsonSerializer::DoubleField(const std::string &field_name, double value) {
        if (first)
            first = false;
        else
            *output_ << ", ";
        *output_ << '\"' << field_name << "\": ";
        *output_ << value;
    }

    void JsonSerializer::StringField(const std::string &field_name, const std::string &value) {
        if (first)
            first = false;
        else
            *output_ << ", ";
        *output_ << '\"' << field_name << "\": ";
        *output_ << '\"' << value << '\"';
    }

    void JsonSerializer::BooleanField(const std::string &field_name, bool value) {
        if (first)
            first = false;
        else
            *output_ << ", ";
        *output_ << '\"' << field_name << "\": ";
        *output_ << '\"' << value << "\": ";
    }

    void JsonSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value) {
        Header(field_name);
        value.Serialize(this);
        Footer(field_name);
    }

    void JsonSerializer::ArrayField(const std::string &field_name,
                                    const std::vector<std::reference_wrapper<const academia::Serializable>> &value) {
        if (first)
            first = false;
        else
            *output_ << ", ";
        *output_ << '\"' << field_name << "\": [";
        bool first_array = true;
        for (const Serializable &element : value) {
            if (first_array)
                first_array = false;
            else
                *output_ << ", ";
            element.Serialize(this);
        }
        *output_ << ']';
    }

    void JsonSerializer::Header(const std::string &object_name) {
        *output_ << '{';
        first = true;
    }

    void JsonSerializer::Footer(const std::string &object_name) {
        *output_ << '}';
    }
}

