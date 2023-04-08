#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <opencv2/core/core.hpp>

void my_line(cv::Mat& image, const cv::Point p1, const cv::Point p2, const cv::Vec3b color);
void my_circle(cv::Mat& image, const cv::Point centre, const int radius, const cv::Vec3b color);

#endif // GRAPHICS_H
