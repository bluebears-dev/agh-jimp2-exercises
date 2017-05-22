//
// Created by pgorski42 on 16.05.17.
//

#include <set>
#include <map>
#include <vector>
#include <numeric>
#include "Algo.h"

using namespace std;

namespace algo {
    set<string> Keys(const map<string, int> &m) {
        set<string> s;
        transform(m.begin(), m.end(), inserter(s, s.begin()), [](const auto &element) {return element.first;});
        return s;
    }

    vector<int> Values(const map<string, int> &m) {
        vector<int> numbers;
        transform(m.begin(), m.end(), inserter(numbers, numbers.begin()), [](const auto &element) {return element.second;});
        return numbers;
    }

    map<string, int> DivisableBy(const map<string, int> &m, int divisor) {
        map<string, int> mp;
        copy_if(m.begin(), m.end(), inserter(mp, mp.begin()), [divisor](const auto &element) {return element.second % divisor;});
        return mp;
    };
    
    void SortInPlace(vector<int> *v) {
        sort(v->begin(), v->end());
    }

    vector<int> Sort(const vector<int> &v) {
        vector<int> vec = v;
        SortInPlace(&vec);
        return vec;
    }

    void SortByFirstInPlace(vector<pair<int,int>> *v) {
        sort(v->begin(), v->end(), [](const auto &pair1, const auto &pair2) {return pair1.first < pair2.first;});
    }

    void SortBySecondInPlace(vector<pair<int,int>> *v) {
        sort(v->begin(), v->end(), [](const auto &pair1, const auto &pair2) {return pair1.second < pair2.second;});
    }

    void SortByThirdInPlace(vector<tuple<int,int,int>> *v) {
        sort(v->begin(), v->end(), [](const tuple<int,int,int> &set1, const tuple<int,int,int> &set2) {return (get<2>(set1) < get<2>(set2));});
    }

    vector<string> MapToString(const vector<double> &v) {
        vector<string> vec;
        transform(v.begin(), v.end(), back_inserter(vec), [](double num) {return to_string(num);});
        return vec;
    }

    string Join(const string &joiner, const vector<double> &v) {
        auto vec = MapToString(v);
        string result = joiner;
//        result += accumulate(std::next(vec.begin()), vec.end(), vec.begin(), [](string &str1, string &str2) {return str1 + str2;});
        return result;

    }

    int Sum(const vector<int> &v) {
        return accumulate(v.begin(), v.end(), 0);
    }

    int Product(const vector<int> &v) {
        return accumulate(v.begin(), v.end(), 1);
    }

    bool Contains(const vector<int> &v, int element) {
        return find(v.begin(), v.end(), element) != v.end();
    }

    bool ContainsKey(const map<string, int> &v, const string &key) {
        return v.find(key) != v.end();
    }

    bool ContainsValue(const map<string, int> &v, int value) {
        return find_if(v.begin(), v.end(), [value](const auto &element) {return element.second == value;}) != v.end();
    }

    vector<string> RemoveDuplicates(const vector<string> &v) {
        vector<string> vec = v;
        unique(vec.begin(), vec.end());
        return vec;
    }

    void RemoveDuplicatesInPlace(vector<string> *v) {
        unique(v->begin(), v->end());
    }

    void InitializeWith(int initial_value, vector<int> *v) {
        fill(v->begin(), v->end(), initial_value);
    }

    vector<int> InitializedVectorOfLength(int length, int initial_value) {
        vector<int> v(length);
        fill_n(v.begin(), length, initial_value);
        return v;
    }

    int HowManyShortStrings(const vector<string> &v, int inclusive_short_length) {
        return count_if(v.begin(), v.end(), [inclusive_short_length](const auto &str) {return str.length() == inclusive_short_length;});
    }
    
    void CopyInto(const vector<int> &v, int n_elements, vector<int> *out) {
        copy(v.begin(), v.begin() + n_elements, back_inserter(*out));
    }
}