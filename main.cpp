#include <iostream>
#include <vector>
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 20;
vector<double> input_numbers(size_t count) { //функция ввода вектора
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max) { //функция поиска min max
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
make_histogram(const vector<double>& numbers, size_t bin_count){//функция сбора вектора bins

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

void show_histogram_text(const vector<double>& bins){ //функция вывода вектора x
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

void
svg_begin(double width, double height) { //готовая функция вывода заголовка svg файла
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() { //готовая функция вывода завершения svg файла
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}

void
svg_rect(double x, double y, double width, double height,
         string stroke = "black", string fill = "black"){
    cout<<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<
    "' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void
show_histogram_svg(const vector<size_t>& bins) {
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"blue", "yellow");
        top += BIN_HEIGHT;
    }
    svg_end();
}

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count); //Ввод данных через функцию input_numbers

    size_t bin_count;
    cerr << "Enter number bins: ";
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);

    //show_histogram_text(bins);
    show_histogram_svg(bins);
}
