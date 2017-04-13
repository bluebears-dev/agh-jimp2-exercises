//
// Created by pgorski42 on 13.04.17.
//

#include "WordCounter.h"

using std::string;
using std::ostream;
using std::istream;
using std::initializer_list;
using std::set;

namespace datastructures {

    Counts::Counts(int count) : count_(count) {}
    int Counts::Get() const {
        return count_;
    }
    void Counts::Set(int count) {
        Counts::count_ = count;
    }

    bool Counts::operator<(const Counts &count) const {
        return count_ < count.count_;
    }
    bool Counts::operator>(const Counts &count) const {
        return count_ > count.count_;
    }

    bool Counts::operator==(const Counts &count) const {
        return count_ == count.count_;
    }
    Counts &Counts::operator++() {
        count_++;
        return *this;
    }

    Counts Counts::operator++(int) {
        auto count = *this;
        count_++;
        return count;
    }

    Counts::operator int() const {
        return count_;
    }

    Word::Word(string word) : word_(word) {}
    const string &Word::Get() const {
        return word_;
    }

    bool Word::operator<(const Word &word) const {
        return word_ < word.word_;
    }
    bool Word::operator==(const Word &word) const {
        return word_ == word.word_;
    }

    WordCounter WordCounter::FromInputStream(istream &stream) {
        return WordCounter();
    }
    
    WordCounter::WordCounter(const initializer_list<Word> &words) {
        for (auto word : words)
            word_list_[word]++;
    }

    Counts WordCounter::operator[](const string &word) const {
        auto words = word_list_;
        return words[word];
    }

    ostream &operator<<(ostream &stream, const WordCounter &word_counter) {
        return stream;
    }

    long WordCounter::DistinctWords() const {
        return word_list_.size();
    }
    long WordCounter::TotalWords() const {
        long total = 0;
        for (auto word : word_list_)
            total += word.second.Get();
        return total;
    }

    set<Word> WordCounter::Words() const {
        set<Word> words;
        for (auto word : word_list_)
            words.insert(word.first);
        return words;
    }
}
