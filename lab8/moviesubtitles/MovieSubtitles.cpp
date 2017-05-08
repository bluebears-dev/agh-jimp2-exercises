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
using std::regex_match;
using std::smatch;
using std::stoi;
using std::stol;
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
        if (framerate < 0)
            throw invalid_argument("Framerate cannot be negative");

        string line;

        bool end_of_section = false,
             timestamp_present = false;

        while (not end_of_section) {
            getline(*in, line);

            if (line.empty()) {
                if (not in->eof())
                    *out << endl;
                end_of_section = true;
            } else {
                if (not timestamp_present) {
                    string suffix = line;
                    if (regex_match(line, regex(R"(\d{2}:\d{2}:\d{2},\d{3} --> \d{2}:\d{2}:\d{2},\d{3})"))) {
                        regex pattern{R"((\d{2}):(\d{2}):(\d{2}),(\d{3})( --> )*)"};
                        smatch matches;
                        timestamp_present = true;

                        int num_matches = 0;
                        long previous = 0;
                        while (regex_search(suffix, matches, pattern)) {
                            long h = stol(matches[1].str()),
                                    m = stol(matches[2].str()),
                                    s = stol(matches[3].str()),
                                    ms = stol(matches[4].str()),
                                    tmp,
                                    current;

                            ms += s * 1000;
                            s = 0;
                            ms += m * 1000 * 60;
                            m = 0;
                            ms += h * 1000 * 60 * 60;
                            h = 0;
                            current = ms;

                            tmp = ResidueAdd(ms, miliseconds, 1000);
                            if (ms < 0)
                                throw NegativeFrameAfterShift(line, line_number);
                            if (current < previous)
                                throw SubtitleEndBeforeStart(line, line_number);
                            tmp = ResidueAdd(s, tmp, 60);
                            tmp = ResidueAdd(m, tmp, 60);
                            h = tmp;

                            *out << setfill('0') << setw(2) << h
                                 << ':' << setw(2) << m
                                 << ':' << setw(2) << s
                                 << ',' << setw(3) << ms
                                 << setfill(' ') << matches[5];
                            num_matches++;
                            suffix = matches.suffix();
                            previous = current;
                        }
                    } else if (regex_match(line, regex(R"(^\d+)"))) {
                        int current_line_number = stoi(line);
                        if (current_line_number != line_number)
                            throw OutOfOrderFrames(line, line_number);
                    } else
                        throw InvalidSubtitleLineFormat(line, line_number);
                    *out << suffix << endl;
                } else
                    *out << line << endl;
            }
        }
    }

    long SubRipSubtitles::ResidueAdd(long &number1, long number2, int limit) const {
        long sum = (number1 + number2);
        number1 = sum % limit;
        return sum / limit;
    }

    NegativeFrameAfterShift::NegativeFrameAfterShift(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};

    SubtitleEndBeforeStart::SubtitleEndBeforeStart(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};

    InvalidSubtitleLineFormat::InvalidSubtitleLineFormat(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};

    MissingTimeSpecification::MissingTimeSpecification(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};

    OutOfOrderFrames::OutOfOrderFrames(std::string msg, int line) : SubtitlesValidationException(
            "At line "s + std::to_string(line) + ": " + msg, line) {};
}

