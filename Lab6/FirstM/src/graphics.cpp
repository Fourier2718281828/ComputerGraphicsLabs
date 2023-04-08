#include "graphics.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

bool can_draw(const cv::Mat& image, const int x, const int y)
{
    return x >= 0 && x < image.rows &&
           y >= 0 && y < image.cols;
}

bool draw_if_can(cv::Mat& image, const int x, const int y, const cv::Vec3b color)
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

void my_line(cv::Mat& image, const cv::Point p1, const cv::Point p2, const cv::Vec3b color)
{
    using std::abs;
    using std::swap;
    int x0 = p1.y;
    int y0 = p1.x;
    int x1 = p2.y;
    int y1 = p2.x;

    bool steep = false;
    if(abs(x1 - x0) < abs(y1 - y0))
    {
        swap(x0, y0);
        swap(x1, y1);
        steep = true;
    }
    if(x0 > x1)
    {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = abs(dy)*2;
    int error2 = 0;

    for(int x = x0, y = y0; x <= x1; ++x)
    {
        if(steep && can_draw(image, y, x))
        {
            image.at<cv::Vec3b>(y, x) = color;
        }
        else if(can_draw(image, x, y))
        {
            image.at<cv::Vec3b>(x, y) = color;
        }

        error2 += derror2;
        if(error2 > dx)
        {
            y += y1 > y0 ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void my_circle(cv::Mat& image, const cv::Point centre, const int radius, const cv::Vec3b color)
{
    int x0 = centre.y;
    int y0 = centre.x;
    int delta = 1 - 2 * radius;
    int error = 0;

    for(int x = 0, y = radius; y >= 0;)
    {
        /*image.at<cv::Vec3b>(x0 + x, y0 + y) = color;
        image.at<cv::Vec3b>(x0 + x, y0 - y) = color;
        image.at<cv::Vec3b>(x0 - x, y0 + y) = color;
        image.at<cv::Vec3b>(x0 - x, y0 - y) = color;

        image.at<cv::Vec3b>(x0 + y, y0 + x) = color;
        image.at<cv::Vec3b>(x0 + y, y0 - x) = color;
        image.at<cv::Vec3b>(x0 - y, y0 + x) = color;
        image.at<cv::Vec3b>(x0 - y, y0 - x) = color;*/

        draw_if_can(image, x0 + x, y0 + y, color);
        draw_if_can(image, x0 + x, y0 - y, color);
        draw_if_can(image, x0 - x, y0 + y, color);
        draw_if_can(image, x0 - x, y0 - y, color);
        draw_if_can(image, x0 + y, y0 + x, color);
        draw_if_can(image, x0 + y, y0 - x, color);
        draw_if_can(image, x0 - y, y0 + x, color);
        draw_if_can(image, x0 - y, y0 - x, color);

        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0)
        {
            ++x;
            delta += 2 * x + 1;
        }
        else if (delta > 0 && error > 0)
        {
            --y;
            delta -= 2 * y + 1;
        }
        else
        {
            ++x;
            --y;
            delta += 2 * (x - y);
        }
    }
}
