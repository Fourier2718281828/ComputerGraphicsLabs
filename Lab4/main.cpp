#include <opencv2/opencv.hpp>
#include "MandelbrotSet.h"

int main()
{
    using namespace cv;
    const size_type rows = 800;
    const size_type cols = 800;
    const size_type N    = 100;
    Mat  bw_mand_set(rows, cols, CV_8UC3, cv::Scalar(0));
    Mat rgb_mand_set(rows, cols, CV_8UC3, cv::Scalar(0));
    draw_mandelbrot_set(bw_mand_set, N, bw_colourizer);
    draw_mandelbrot_set(rgb_mand_set, N, rgb_colourizer);
    imshow("BW Mandelbrot Set", bw_mand_set);
    imshow("RGB Mandelbrot Set", rgb_mand_set);
    waitKey(0);

    return EXIT_SUCCESS;
}
