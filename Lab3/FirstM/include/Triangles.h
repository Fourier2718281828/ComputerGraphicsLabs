#ifndef TRIANGLES_H
#define TRIANGLES_H
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

void safe_draw_triangle
(
    cv::Mat& image,
    const cv::Point& p00,
    const cv::Point& p10,
    const cv::Point& p20,
    const cv::Vec3b& color
);

void draw_triangle
(
    cv::Mat& image,
    const cv::Point& p00,
    const cv::Point& p10,
    const cv::Point& p20,
    const cv::Vec3b& color
);
#endif // TRIANGLES_H
