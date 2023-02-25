#include "Triangles.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef bool (*const DrawPixelFunc)(cv::Mat& image, const int x, const int y, const cv::Vec3b color);

inline bool can_draw(const cv::Mat& image, const int x, const int y)
{
    return x >= 0 && x < image.rows &&
           y >= 0 && y < image.cols;
}

inline bool draw_if_can(cv::Mat& image, const int x, const int y, const cv::Vec3b color)
{
    if(can_draw(image, x, y))
    {
        image.at<cv::Vec3b>(x, y) = color;
        return true;
    }
    else
    {
        return false;
    }
}

inline bool unsafe_draw(cv::Mat& image, const int x, const int y, const cv::Vec3b color)
{
    image.at<cv::Vec3b>(x, y) = color;
    return true;
}

inline void sort_three_points(cv::Point& t0, cv::Point& t1, cv::Point& t2)
{
    if(t0.y > t1.y)
        std::swap(t0, t1);
    if(t0.y > t2.y)
        std::swap(t0, t2);
    if(t1.y > t2.y)
        std::swap(t1, t2);
}

void draw_half_triangle_on_sorted_points
(
    cv::Mat& image,
    const cv::Point& p0,
    const cv::Point& p1,
    const cv::Point& p2,
    const cv::Vec3b& color,
    const DrawPixelFunc draw,
    const int total_height
)
{
    const int segment_h = p1.y - p0.y;
    for(int y = p0.y; y <= p1.y; ++y)
    {
        if(segment_h == 0) break;
        //parametrising the move along two current sides:
        //t1, t2 are parameters \in [0, 1]
        //Notice: t1 goes through the whole edge
        //whereas t2 only throug the current segment (half of triangle).
        const float t1 = static_cast<float>(y - p0.y) / total_height;
        const float t2 = static_cast<float>(y - p0.y) / segment_h;
        cv::Point pt1 = p0 + (p2 - p0)*t1;
        cv::Point pt2 = p0 + (p1 - p0)*t2;
        if(pt1.x > pt2.x)
            std::swap(pt1, pt2);
        for(int j = pt1.x; j <= pt2.x; ++j)
        {
            draw(image, y, j, color);
        }
    }
}

void generic_triangle
(
    cv::Mat& image,
    const cv::Point& p00,
    const cv::Point& p10,
    const cv::Point& p20,
    const cv::Vec3b& color,
    const DrawPixelFunc draw

)
{
    cv::Point p0 = p00;
    cv::Point p1 = p10;
    cv::Point p2 = p20;
    sort_three_points(p0, p1, p2);

    const int total_height = p2.y - p0.y;
    if(total_height <= 0)
        throw std::runtime_error("invalid triangle");

    const int segment1_h = p1.y - p0.y;
    for(int y = p0.y; y <= p1.y; ++y)
    {
        if(segment1_h == 0) break;
        //parametrising the move along two current sides:
        //t1, t2 are parameters \in [0, 1]
        //Notice: t1 goes through the whole edge
        //whereas t2 only throug the current segment (half of triangle).
        const float t1 = static_cast<float>(y - p0.y) / total_height;
        const float t2 = static_cast<float>(y - p0.y) / segment1_h;
        cv::Point pt1 = p0 + (p2 - p0)*t1;
        cv::Point pt2 = p0 + (p1 - p0)*t2;
        if(pt1.x > pt2.x)
            std::swap(pt1, pt2);
        for(int j = pt1.x; j <= pt2.x; ++j)
        {
            draw(image, y, j, color);
        }
    }

    const int segment2_h = p2.y - p1.y;
    for(int y = p1.y; y <= p2.y; ++y)
    {
        if(segment2_h == 0) break;
        //parametrising the move along two current sides:
        //t1, t2 are parameters \in [0, 1]
        //Notice: t1 goes through the whole edge
        //whereas t2 only throug the current segment (half of triangle).
        const float t1 = static_cast<float>(y - p0.y) / total_height;
        const float t2 = static_cast<float>(y - p1.y) / segment2_h;
        cv::Point pt1 = p0 + (p2 - p0)*t1;
        cv::Point pt2 = p1 + (p2 - p1)*t2;
        if(pt1.x > pt2.x)
            std::swap(pt1, pt2);
        for(int j = pt1.x; j <= pt2.x; ++j)
        {
            draw(image, y, j, color);
        }
    }
}

void safe_draw_triangle
(
    cv::Mat& image,
    const cv::Point& p00,
    const cv::Point& p10,
    const cv::Point& p20,
    const cv::Vec3b& color
)
{
    generic_triangle(image, p00, p10, p20, color, &draw_if_can);
}

void draw_triangle
(
    cv::Mat& image,
    const cv::Point& p00,
    const cv::Point& p10,
    const cv::Point& p20,
    const cv::Vec3b& color
)
{
    generic_triangle(image, p00, p10, p20, color, &unsafe_draw);
}
