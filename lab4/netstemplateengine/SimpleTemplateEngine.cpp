//
// Created by pgorski42 on 13.04.17.
//

#include "SimpleTemplateEngine.h"

using std::string;
using std::unordered_map;
using std::regex;
using std::regex_replace;
using std::smatch;

namespace nets {

    View::View(string str) : template_(str) {}

    string View::Render(const unordered_map<string, string> &model) const {
        string replaced(template_);
        // find out which placeholders will be changed
        for (const auto &pair : model)
            replaced = regex_replace(replaced, {"\\{\\{" + pair.first + "\\}\\}"}, "{%{" + pair.first + "}%}");

        // clear out other placeholders
        replaced = regex_replace(replaced, {"\\{\\{[^{}]*\\}\\}"}, "");

        // replace content
        for (const auto &pair : model)
            replaced = regex_replace(replaced, {"\\{%\\{" + pair.first + "\\}%\\}"}, pair.second);
        return replaced;
    }
}