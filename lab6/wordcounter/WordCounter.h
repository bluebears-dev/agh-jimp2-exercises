//
// Created by pgorski42 on 13.04.17.
//

#ifndef JIMP_EXERCISES_WORDCOUNTER_H
#define JIMP_EXERCISES_WORDCOUNTER_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <map>
#include <set>

namespace datastructures {
    class Counts {
    public:
        Counts(int count = 0);

        operator int() const;

        bool operator<(const Counts &count) const;
        bool operator>(const Counts &count) const;
        bool operator==(const Counts &count) const;

        Counts &operator++();
        Counts operator++(int);

        int Get() const;
        void Set(int count);
    private:
        int count_;
    };

    class Word {
    public:
        Word(std::string word);

        bool operator<(const Word &word) const;
        bool operator==(const Word &word) const;

        const std::string &Get() const;
    private:
        std::string word_;
    };

    class WordCounter {
    public:
        static WordCounter FromInputStream(std::istream &stream);

        WordCounter() = default;
        WordCounter(const std::initializer_list<Word> &words);

        Counts operator[](const std::string &word) const;
        friend std::ostream &operator<<(std::ostream &stream, const WordCounter &word_counter);

        long DistinctWords() const;
        long TotalWords() const;
        std::set<Word> Words() const;
    private:
        std::map<Word, Counts> word_list_;
    };

    std::ostream &operator<<(std::ostream &stream, const WordCounter &word_counter);
}

#endif //JIMP_EXERCISES_WORDCOUNTER_H
