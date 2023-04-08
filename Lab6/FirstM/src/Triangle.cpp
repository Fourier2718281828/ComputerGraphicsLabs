#include "Triangle.h"
#include "ZBuffer.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef bool (*const DrawPixelFunc)(cv::Mat& image, const int x, const int y, const float z, const cv::Vec3b color);

void zbuffer_draw(cv::Mat& image, const int x, const int y, const float z, const cv::Vec3b color)
{
    ZBuffer& zbuff = ZBuffer::getInstance();
    std::size_t xc = static_cast<std::size_t>(x);
    std::size_t yc = static_cast<std::size_t>(y);
    std::size_t linearized = yc*zbuff.hor_size() + xc;

    if ( zbuff.buffer()[linearized] < z)
    {
        zbuff.buffer()[linearized] = z;
        image.at<cv::Vec3b>(x, y) = color;
    }
}

inline bool can_draw2(const cv::Mat& image, const int x, const int y)
{
    return x >= 0 && x < image.cols &&
           y >= 0 && y < image.rows;
}

inline bool draw_if_can2(cv::Mat& image, const int x, const int y, const float z, const cv::Vec3b color)
{
    if(can_draw2(image, x, y))
    {
        zbuffer_draw(image, x, y, z, color);
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

inline void sort_three_points(cv::Point3f& t0, cv::Point3f& t1, cv::Point3f& t2)
{
    if(t0.y > t1.y)
        std::swap(t0, t1);
    if(t0.y > t2.y)
        std::swap(t0, t2);
    if(t1.y > t2.y)
        std::swap(t1, t2);
}

void generic_triangle
(
    cv::Mat& image,
    const cv::Point3f& p00,
    const cv::Point3f& p10,
    const cv::Point3f& p20,
    const cv::Vec3b& color,
    const DrawPixelFunc draw

)
{
    cv::Point3f p0 = p00;
    cv::Point3f p1 = p10;
    cv::Point3f p2 = p20;
    sort_three_points(p0, p1, p2);

    const float total_height = p2.y - p0.y;
    if(total_height <= 0)
    {
        throw std::runtime_error("invalid triangle");
    }

    const float segment1_h = p1.y - p0.y;
    for(float y = p0.y; y <= p1.y; ++y)
    {
        if(segment1_h == 0) break;
        const float t1 = static_cast<float>(y - p0.y) / total_height;
        const float t2 = static_cast<float>(y - p0.y) / segment1_h;
        cv::Point3f pt1 = p0 + (p2 - p0)*t1;
        cv::Point3f pt2 = p0 + (p1 - p0)*t2;
        if(pt1.x > pt2.x)
            std::swap(pt1, pt2);
        for(float j = pt1.x; j <= pt2.x; ++j)
        {
            draw(image, y, j, (pt1.z + pt2.z)*0.5, color);
        }
    }

    const float segment2_h = p2.y - p1.y;
    for(float y = p1.y; y <= p2.y; ++y)
    {
        if(segment2_h == 0) break;
        const float t1 = static_cast<float>(y - p0.y) / total_height;
        const float t2 = static_cast<float>(y - p1.y) / segment2_h;
        cv::Point3f pt1 = p0 + (p2 - p0)*t1;
        cv::Point3f pt2 = p1 + (p2 - p1)*t2;
        if(pt1.x > pt2.x)
            std::swap(pt1, pt2);
        for(float j = pt1.x; j <= pt2.x; ++j)
        {
            draw(image, y, j, (pt1.z + pt2.z)*0.5, color);
        }
    }
}

void safe_draw_triangle
(
    cv::Mat& image,
    const cv::Point3f& p00,
    const cv::Point3f& p10,
    const cv::Point3f& p20,
    const cv::Vec3b& color
)
{
    generic_triangle(image, p00, p10, p20, color, &draw_if_can2);
}
