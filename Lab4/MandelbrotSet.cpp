#include "MandelbrotSet.h"
#include <complex>
#include <iostream>

#define MIN_REAL -2.0
#define MAX_REAL  1.0
#define MIN_IMAG -1.5
#define MAX_IMAG  1.5

typedef int coord_t;
typedef double proj_num_t;
typedef std::complex<proj_num_t> num_t;

inline bool can_draw(const cv::Mat& image, const coord_t x, const coord_t y)
{
    return x >= 0 && x < image.cols &&
           y >= 0 && y < image.rows;
}

inline bool draw
(
    cv::Mat& input_image,
    const coord_t x,
    const coord_t y,
    const color_t clr
)
{
    if(can_draw(input_image, x, y))
    {
        input_image.at<cv::Vec3b>(x, y) = clr;
        return true;
    }
    else
    {
        return false;
    }
}

inline color_t bw_colorizer_f (const hue_type t)
{
    return color_t
    (
        t*255,
        t*255,
        t*255
    );
}

inline color_t rgb_colorizer_f(const hue_type t)
{
    return color_t
    (
        static_cast<int>(9 * (1 - t) * pow(t, 3) * 255),
        static_cast<int>(15 * pow((1 - t), 2) * pow(t, 2) * 255),
        static_cast<int>(8.5 * pow((1 - t), 3) * t * 255)
    );
}

inline num_t project_to_complex(const coord_t x, const coord_t y, const cv::Mat& image)
{
    const size_type width  = image.cols;
    const size_type height = image.rows;
    const proj_num_t real  = MIN_REAL + (MAX_REAL - MIN_REAL) * x / width;
    const proj_num_t imag  = MIN_IMAG + (MAX_IMAG - MIN_IMAG) * y / height;
    return num_t(real, imag);
}

void process_point(const num_t z0, size_type& iterations, const size_type N)
{
    const proj_num_t sup_abs = 2.0;
    size_type& k = iterations;
    num_t zk;

    for(; k < N && abs(zk) < sup_abs; ++k)
    {
        zk = zk*zk + z0;
    }
}

void draw_mandelbrot_set
(
    cv::Mat& input_image,
    const size_type N,
    const colourizer_t clrzer
)
{
    if(!clrzer)
        throw std::runtime_error("Nullptr passed as colourizer!");
    const size_type cols = input_image.cols;
    const size_type rows = input_image.rows;

    for(size_type x = 0u; x < cols; ++x)
    {
        for(size_type y = 0u; y < rows; ++y)
        {
            const num_t cnum = project_to_complex(x, y, input_image);
            size_type iterations = 0u;
            process_point(cnum, iterations, N);
            const hue_type hue = static_cast<hue_type>(iterations) / N;
            draw(input_image, y, x, clrzer(hue));
        }
    }
}

const colourizer_t bw_colourizer  = bw_colorizer_f;
const colourizer_t rgb_colourizer = rgb_colorizer_f;
