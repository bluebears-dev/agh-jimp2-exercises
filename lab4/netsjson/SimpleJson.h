//
// Created by pgorski42 on 13.04.17.
//

#ifndef JIMP_EXERCISES_SIMPLEJSON_HPP
#define JIMP_EXERCISES_SIMPLEJSON_HPP

#include <experimental/optional>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

namespace nets {
    class JsonValue {
    public:
        JsonValue(int value);
        JsonValue(double value);
        JsonValue(bool value);
        JsonValue(std::string str);
        JsonValue(std::vector<JsonValue> array);
        JsonValue(const std::map<std::string, JsonValue> &elements);

        std::experimental::optional<JsonValue> ValueByName(const std::string &name) const;
        std::string ToString() const;
    private:
        std::string json_string_;
    };
}

#endif //JIMP_EXERCISES_SIMPLEJSON_HPP
