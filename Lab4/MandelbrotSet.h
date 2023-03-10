#ifndef MANDELBROTSET_H
#define MANDELBROTSET_H
#include <opencv2/opencv.hpp>

typedef double hue_type;
typedef size_t size_type;
typedef cv::Vec3b color_t;
typedef color_t (*colourizer_t)(const hue_type);

void draw_mandelbrot_set
(
    cv::Mat& input_image,
    const size_type iterations,
    const colourizer_t clrzer
);

extern const colourizer_t bw_colourizer;
extern const colourizer_t rgb_colourizer;

#endif // MANDELBROTSET_H
