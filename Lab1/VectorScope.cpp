/*#include "VectorScope.h"
#include "opencv2/imgproc.hpp"

void draw_axes(cv::Mat& VectorScopeM, cv::Vec3b color, const cv::Point centre, const int radius)
{
    cv::line
    (
        VectorScopeM,
        centre - cv::Point(radius, 0),
        centre + cv::Point(radius, 0),
        color,
        1,
        CV_AA
    );

    cv::line
    (
        VectorScopeM,
        centre - cv::Point(0, radius),
        centre + cv::Point(0, radius),
        color,
        1,
        CV_AA
    );

    cv::circle
    (
        VectorScopeM,
        centre,
        radius,
        color,
        1,
        CV_AA
    );


    std::stringstream conf(std::stringstream::in | std::stringstream::out);
    conf <<"Cr";
    cv::putText(VectorScopeM, conf.str(),centre - cv::Point(-10, radius - 20),
                1., 1.1, color, 1, cv::LINE_AA);
    conf.str(std::string());

    conf <<"Cb";
    cv::putText(VectorScopeM, conf.str(),centre + cv::Point(radius - 30, 20),
                1., 1.1, color, 1, cv::LINE_AA);
    conf.str(std::string());

    conf <<"P";
    cv::putText(VectorScopeM, conf.str(),centre + cv::Point(radius * 0.5f, -radius * 0.5f),
                1., 1.1, color, 1, cv::LINE_AA);
    conf.str(std::string());

    conf <<"R";
    cv::putText(VectorScopeM, conf.str(),centre + cv::Point(-radius * 0.5f, -radius * 0.5f),
                1., 1.1, color, 1, cv::LINE_AA);
    conf.str(std::string());

    conf <<"G";
    cv::putText(VectorScopeM, conf.str(),centre + cv::Point(-radius * 0.5f, radius * 0.5f),
                1., 1.1, color, 1, cv::LINE_AA);
    conf.str(std::string());

    conf <<"B";
    cv::putText(VectorScopeM, conf.str(),centre + cv::Point(radius * 0.5f, radius * 0.5f),
                1., 1.1, color, 1, cv::LINE_AA);
    conf.str(std::string());
}

void draw_graph
(
    const cv::Mat& input_image,
    cv::Mat& canvas,
    const float scaler,
    cv::Vec3b graph_color
)
{
    const int w = canvas.rows;
    const int h = canvas.cols;
    const cv::Vec3f shift = cv::Vec3f(0, canvas.rows, canvas.cols) * .5f;

    cv::Vec3b pixel;
    cv::Vec3f ycbcr;
    float cb_coord, cr_coord;

    for (int i = 0; i < input_image.rows; ++i)
    {
        for (int j = 0; j < input_image.cols; ++j)
        {
            pixel = input_image.at<cv::Vec3b>(i, j);
            ycbcr = RGB_2_YCbCr(pixel);

            cb_coord = scaler * ycbcr[1] + shift[1];
            cr_coord = -scaler * ycbcr[2] + shift[2];
            canvas.at<cv::Vec3b>(cr_coord, cb_coord) = graph_color;
        }
    }
}

void draw_vector_scope
(
    const cv::Mat& input_image,
    cv::Mat& canvas,
    cv::Vec3b ui_color,
    cv::Vec3b graph_color,
    const int radius,
    const int domain_supremum
)
{
    const int w = canvas.rows;
    const int h = canvas.cols;
    const float factor = 2.0f * radius / domain_supremum;
    draw_graph(input_image, canvas, factor, graph_color);
    draw_axes(canvas, ui_color, cv::Point(h / 2, w / 2), radius);
}*/
