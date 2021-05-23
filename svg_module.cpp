#include <iostream>
#include <vector>
#include <math.h>
#include "histogram.h"
#include "svg_module.h"
using namespace std;

const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 20;

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
svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black"){
    cout<<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<
    "' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void
show_histogram_svg(const vector<size_t>& bins) {

    size_t max_bin = bins[0];//поиск максимальной корзины
    for (size_t x : bins) {
        if (x > max_bin)max_bin = x;
     }

    double numbers_count = 0;//подсчет всех чисел
    for (size_t bin : bins) numbers_count+=bin;

    bool scale_flag = false; //Условие введения изображения в формат масштабирования
    if (max_bin*BLOCK_WIDTH > IMAGE_WIDTH-2*TEXT_WIDTH-5) scale_flag = true;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {

        double bin_width; //Определение размера прямоугольника
        if(scale_flag) bin_width = (static_cast<double>(bin)/max_bin) * (IMAGE_WIDTH-2*TEXT_WIDTH-5);
        else bin_width = bin*BLOCK_WIDTH;

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black", "#e3256b");

        double proc = round(((bin/numbers_count)*100)); //расчет и выведение процента.
        string proc_s = to_string(static_cast<int>(proc))+ "%";
        svg_text(IMAGE_WIDTH-TEXT_WIDTH, top+TEXT_BASELINE, proc_s);

        top += BIN_HEIGHT;
    }
    svg_end();
}

