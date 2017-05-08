//
// Created by pgorski42 on 03.05.17.
//

#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <sstream>
#include <iomanip>
#include <regex>
#include <stdexcept>

namespace moviesubs {
    class SubtitlesValidationException : public std::runtime_error {
    protected:
        int line;

    public:
        virtual int LineAt() const { return line; }
        SubtitlesValidationException(std::string str, int line) : line(line), std::runtime_error(str) {}
    };

    class NegativeFrameAfterShift : public SubtitlesValidationException {
    public:
        NegativeFrameAfterShift(std::string msg, int line);
    };

    class SubtitleEndBeforeStart : public SubtitlesValidationException {
    public:
        SubtitleEndBeforeStart(std::string msg, int line);
    };

    class InvalidSubtitleLineFormat : public SubtitlesValidationException {
    public:
        InvalidSubtitleLineFormat(std::string msg, int line);
    };


    class MovieSubtitles {
    public:
        int current_line;

        void
        ShiftAllSubtitlesBy(int miliseconds, int framerate, std::stringstream *in, std::stringstream *out) const;

    protected:
        virtual void
        Delay(int miliseconds, int framerate, std::stringstream *in, std::stringstream *out, const int line_number) const = 0;
    };

    class MicroDvdSubtitles : public MovieSubtitles {
    protected:
        virtual void
        Delay(int miliseconds, int framerate, std::stringstream *in, std::stringstream *out, const int line_number) const override;
    };

    class SubRipSubtitles : public MovieSubtitles {
    protected:
        virtual void
        Delay(int miliseconds, int framerate, std::stringstream *in, std::stringstream *out, const int line_number) const override;

    private:
        int ResidueAdd(int &number1, int number2, int limit) const;
    };
}


#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
