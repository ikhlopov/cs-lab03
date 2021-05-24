#include "histogram.h"
#include "svg_module.h"
#include <vector>
#include <cassert>
#include <iostream>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}void

test_same() {
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_one() {
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
//////////////////////////////////////
void
test2_pos(){
    size_t i = 1;
    vector<size_t> bins = {3, 2, 1};
    string res = show_proc(bins, i, false);
    assert(res == "33%");
}

test2_emp(){
    size_t i = 1;
    vector<size_t> bins = {};
    string res = show_proc(bins, i, false);
    assert(res == "");
}

int
main() {
     test_positive();
     test_negative();
     test_same();
     test_one();
     test_empty();

     test2_pos();
     test2_emp();
}
