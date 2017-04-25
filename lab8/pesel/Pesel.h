//
// Created by pgorski42 on 25.04.17.
//

#ifndef JIMP_EXERCISES_PESEL_H
#define JIMP_EXERCISES_PESEL_H

#include <stdexcept>
#include <string>
#include <regex>

namespace academia {
    class AcademiaDataValidationError : public std::runtime_error {
    public:
        AcademiaDataValidationError(std::string str) : std::runtime_error(str) {}
    };

    class InvalidPeselLength : public AcademiaDataValidationError {
    public:
        InvalidPeselLength(std::string pesel, int length) : AcademiaDataValidationError(
                "Invalid PESEL(" + pesel + ") length: " + std::to_string(length)) {}
    };

    class InvalidPeselCharacter : public AcademiaDataValidationError {
    public:
        InvalidPeselCharacter(std::string pesel) : AcademiaDataValidationError(
                "Invalid PESEL(" + pesel + ") character set") {}
    };

    class InvalidPeselChecksum : public AcademiaDataValidationError {
    public:
        InvalidPeselChecksum(std::string pesel, int checksum) : AcademiaDataValidationError(
                "Invalid PESEL(" + pesel + ") checksum: " + std::to_string(checksum)) {}
    };

    class Pesel {
    public:
        Pesel(std::string pesel);

        static void CheckLength(std::string pesel);

        static void CheckCharacters(std::string pesel);

        static void CheckChecksum(std::string pesel);

        static void Validate(std::string pesel);

    private:
        std::string pesel_;
    };
}


#endif //JIMP_EXERCISES_PESEL_H
