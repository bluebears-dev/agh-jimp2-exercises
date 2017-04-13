//
// Created by pgorski42 on 13.04.17.
//

#ifndef JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#define JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H

#include <string>
#include <regex>
#include <unordered_map>

namespace nets {
    class View {
    public:
        View(std::string str);
        std::string Render(const std::unordered_map<std::string, std::string> &model) const;
    private:
        std::string template_;
    };
}


#endif //JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
