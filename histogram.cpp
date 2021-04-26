#include <vector>
#include <iostream>
#include "histogram.h"
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

void find_minmax(const vector<double>& numbers, double& min, double& max) { //функция поиска min max
    if (numbers.size() == 0) return;
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}

vector<size_t>
make_histogram(Input data){//функция сбора вектора bins
    const auto bin_count = data.bin_count;
    const auto numbers = data.numbers;
    double min, max;
    size_t number_count = numbers.size();
    find_minmax(numbers,min,max);
    vector<size_t> bins(bin_count);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins){ //функция вывода вектора x
    size_t bin_count = bins.size();
    size_t max_bin = bins[0];
    for (size_t x : bins) {
        if (x > max_bin)max_bin = x;
     }
    size_t height;
    for (int i = 0; i < bin_count; i++) {
        height = bins[i];
        if (max_bin > MAX_ASTERISK)
            height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_bin);
        if (bins[i] < 100) cout << " ";
        if (bins[i] < 10) cout << " ";
        cout << bins[i] << "|";
        for (int j = 0; j < height; j++) cout << "*";
        cout << endl;
    }
}
