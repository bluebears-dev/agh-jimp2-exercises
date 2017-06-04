//
// Created by pgorski42 on 04.06.17.
//

#include <iostream>
#include <TimeRecorder.h>

using namespace std;

int main() {
    auto ret_val = profiling::TimeRecorder([]() { return 1; });
    cout << ret_val.first << " " << ret_val.second;
    return 0;
}