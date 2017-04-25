//
// Created by pgorski42 on 25.04.17.
//

#include "Pesel.h"

using std::string;
using std::regex;
using std::regex_match;
using std::smatch;

namespace academia {

    Pesel::Pesel(std::string pesel) : pesel_(pesel) {
        Validate(pesel_);
    }

    void Pesel::CheckLength(std::string pesel) {
        if (pesel.length() != 11)
            throw InvalidPeselLength(pesel, pesel.length());
    }

    void Pesel::CheckCharacters(std::string pesel) {
        regex pattern{R"(\d{11})"};
        if (not regex_match(pesel, pattern))
            throw InvalidPeselCharacter(pesel);
    }

    void Pesel::CheckChecksum(std::string pesel) {
        int values[] = {9, 7, 3, 1, 9, 7, 3, 1, 9, 7};

        long checksum = 0;
        for (auto i = 0; i < pesel.length() - 1; ++i)
            checksum += values[i] * (pesel[i] - '0');

        if (checksum % 10 != pesel[10] - '0')
            throw InvalidPeselChecksum(pesel, checksum);
    }

    void Pesel::Validate(std::string pesel) {
        CheckLength(pesel);
        CheckCharacters(pesel);
        CheckChecksum(pesel);
    }
}
