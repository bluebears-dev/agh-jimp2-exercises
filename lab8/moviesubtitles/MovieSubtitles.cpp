//
// Created by pgorski42 on 03.05.17.
//

#include <iostream>
#include "MovieSubtitles.h"

using namespace std::literals;
using std::string;
using std::stringstream;
using std::regex;
using std::regex_search;
using std::smatch;
using std::stoi;
using std::getline;
using std::endl;
using std::setw;
using std::setfill;
using std::pair;
using std::invalid_argument;

namespace moviesubs {
    void
    MovieSubtitles::ShiftAllSubtitlesBy(int miliseconds, int framerate, stringstream *in, stringstream *out) const {
        int line_number = 1;
        while (not in->eof()) {
            Delay(miliseconds, framerate, in, out, line_number);
            line_number++;
        }
    }

    void MicroDvdSubtitles::Delay(int miliseconds, int framerate, std::stringstream *in, std::stringstream *out,
                                  const int line_number) const {

        if (framerate < 0)
            throw invalid_argument("Framerate cannot be negative");
        string line;
        getline(*in, line);

        int num_matches = 0,
                previous = 0,
                step = framerate * miliseconds / 1000;

        string suffix = line;

        regex begin_pattern{R"(\{(\d+)\})"};
        smatch matches;
        while (regex_search(suffix, matches, begin_pattern)) {
            int number = stoi(matches[1].str()),
                    shifted = number + step;

            if (shifted < 0)
                throw NegativeFrameAfterShift(line, line_number);
            if (shifted < previous)
                throw SubtitleEndBeforeStart(line, line_number);
            *out << '{' << shifted << '}';

            num_matches++;
            suffix = matches.suffix();
            previous = shifted;
        }
        if (not suffix.empty()) {
            if (num_matches != 2)
                throw InvalidSubtitleLineFormat(line, line_number);
            *out << suffix << endl;
        }
    }

    void SubRipSubtitles::Delay(int miliseconds, int framerate, std::stringstream *in, std::stringstream *out,
                                const int line_number) const {
        regex begin_pattern{R"((\d{2}):(\d{2}):(\d{2}),(\d{3})( --> )*)"};
        string line;

        bool end_of_section = false;

        while (not end_of_section) {
            getline(*in, line);

            if (line.empty()) {
                if (not in->eof())
                    *out << endl;
                end_of_section = true;
            } else {
                smatch matches;

                while (regex_search(line, matches, begin_pattern)) {
                    int h = stoi(matches[1].str()),
                            m = stoi(matches[2].str()),
                            s = stoi(matches[3].str()),
                            ms = stoi(matches[4].str()),
                            tmp;

                    tmp = ResidueAdd(ms, miliseconds, 1000);
                    tmp = ResidueAdd(s, tmp, 60);
                    tmp = ResidueAdd(m, tmp, 60);
                    h += tmp;

                    *out << setfill('0') << setw(2) << h
                         << ':' << setw(2) << m
                         << ':' << setw(2) << s
                         << ',' << setw(3) << ms
                         << setfill(' ') << matches[5];
                    line = matches.suffix();
                }
                *out << line << endl;
            }
        }
    }

    int SubRipSubtitles::ResidueAdd(int &number1, int number2, int limit) const {
        int sum = (number1 + number2);
        number1 = sum % limit;
        return sum / limit;
    }

    NegativeFrameAfterShift::NegativeFrameAfterShift(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};

    SubtitleEndBeforeStart::SubtitleEndBeforeStart(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};

    InvalidSubtitleLineFormat::InvalidSubtitleLineFormat(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};
}
