#ifndef SVG_MODULE_H_INCLUDED
#define SVG_MODULE_H_INCLUDED
#include <string>
void
svg_begin(double width, double height);

void
svg_end();

void
svg_text(double left, double baseline, string text);

void
svg_rect(double x, double y, double width, double height, string stroke, string fill);

string
show_proc (const vector<size_t>& bins, size_t i,bool scale_flag);

void
show_histogram_svg(const vector<size_t>& bins);

#endif // SVG_MODULE_H_INCLUDED
