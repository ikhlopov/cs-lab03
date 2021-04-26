#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double>
input_numbers(istream& in, size_t count) { //������� ����� �������
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}

vector<size_t>
make_histogram(const vector<double>& numbers, size_t bin_count){//������� ����� ������� bins

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

void show_histogram_text(const vector<size_t>& bins){ //������� ������ ������� x
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


int main()
{
    Input data = read_input(cin);

    const auto bins = make_histogram(data.numbers, data.bin_count);

    show_histogram_svg(bins);
}
