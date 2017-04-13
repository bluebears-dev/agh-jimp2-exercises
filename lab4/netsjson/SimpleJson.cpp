//
// Created by pgorski42 on 13.04.17.
//

#include <iostream>
#include "SimpleJson.h"

using std::experimental::optional;
using std::string;
using std::stringstream;
using std::vector;
using std::map;
using std::pair;

using std::regex;
using std::regex_replace;
using std::regex_match;
using std::smatch;
using std::experimental::make_optional;

namespace nets {

    JsonValue::JsonValue(int value) {
        stringstream stream;
        stream << value;
        json_string_ = stream.str();
    }

    JsonValue::JsonValue(double value) {
        stringstream stream;
        stream << value;
        json_string_ = stream.str();
    }

    JsonValue::JsonValue(bool value) {
        if (value)
            json_string_ = "true";
        else
            json_string_ = "false";
    }

    JsonValue::JsonValue(string str) {
        str = regex_replace(str, regex{R"(\\)"}, "\\\\");
        str = regex_replace(str, regex{R"(\")"}, "\\\"");
        json_string_ = "\"" + str + "\"";
    }

    JsonValue::JsonValue(vector<JsonValue> array) {
        stringstream stream;
        stream << "[";

        bool first = true;
        for (const auto &value : array) {
            if (first)
                first = false;
            else
                stream << ", ";
            stream << value.ToString();
        }
        stream << "]";
        json_string_ = stream.str();
    }

    JsonValue::JsonValue(const map<std::string, JsonValue> &elements) {
        stringstream stream;
        stream << "{";

        bool first = true;
        for (const auto &element : elements) {
            if (first)
                first = false;
            else
                stream << ", ";
            stream << JsonValue{element.first}.ToString() << ": " << element.second.ToString();
        }
        stream << "}";
        json_string_ = stream.str();
    }

    optional<JsonValue> JsonValue::ValueByName(const string &name) const {
        auto begin = json_string_.find(name);

        if (begin == string::npos)
            return optional<JsonValue>();

        auto brackets = 0;
        begin += name.length() + 3;
        auto end = begin;

        for (auto i = begin; i < json_string_.length(); ++i) {
            if (json_string_[i] == '[')
                brackets += 1;
            else if (json_string_[i] == ']')
                brackets -= 1;

            if (!brackets and (json_string_[i] == ',' or json_string_[i] == ']')) {
                end = i + (json_string_[i] == ']');
                i = json_string_.length();
            }
        }

        return make_optional(JsonValue(json_string_.substr(begin, end - begin)));
    }

    string JsonValue::ToString() const {
        return json_string_;
    }
}