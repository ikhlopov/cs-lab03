#include <iostream>
#include <vector>
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
svg_begin(double width, double height) { //������� ������� ������ ��������� svg �����
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() { //������� ������� ������ ���������� svg �����
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
    size_t max_bin = bins[0];
    for (size_t x : bins) {
        if (x > max_bin)max_bin = x;
     }

    bool scale_flag = false;
    if (max_bin*BLOCK_WIDTH > IMAGE_WIDTH) scale_flag = true;
    if(max_bin)
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        double bin_width = bin*BLOCK_WIDTH;
        if(scale_flag) bin_width = (static_cast<double>(bin)/max_bin)* IMAGE_HEIGHT;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black", "#e3256b");
        top += BIN_HEIGHT;
    }
    svg_end();
}

