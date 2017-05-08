//
// Created by pgorski42 on 03.05.17.
//

#include <MovieSubtitles.h>
#include <memory>
#include <iostream>

using namespace std;
using namespace moviesubs;

int main() {
    auto subs = make_unique<SubRipSubtitles>();
    stringstream in {"1\n00:05:54,555 --> 00:05:56,722\nText\n\n2\n00:06:06,433 --> 00:06:07,801\nNEWLINE\n"};
    stringstream out;
    subs->ShiftAllSubtitlesBy(300, 24, &in, &out);
    cout << out.str();
}