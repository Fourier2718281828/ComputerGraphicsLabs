#ifndef TRIANGLES_H
#define TRIANGLES_H
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>



void safe_draw_triangle
(
    cv::Mat& image,
    const cv::Point3f& p00,
    const cv::Point3f& p10,
    const cv::Point3f& p20,
    const cv::Vec3b& color
);

#endif // TRIANGLES_H
