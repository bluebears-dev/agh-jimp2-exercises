//
// Created by pgorski42 on 09.05.17.
//

#include "Serialization.h"

using std::reference_wrapper;
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

}

