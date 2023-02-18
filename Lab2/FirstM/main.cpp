#include <iostream>
#include "model.h"
#include "graphics.h"

void depict_circles(cv::Mat& image)
{
    const int h = image.rows;
    const int w = image.cols;
    const int r = 100;

    for(int x = r, y = r; x < w - r && y < h - r; x += 2*r, y += 2*r)
    {
        my_circle(image, cv::Point(x, y), r, cv::Vec3b(255, 255, 255));
    }
}

void depict_model(cv::Mat& image, Model* const model, const bool using_my_function)
{

    const int width  = image.rows;
    const int height = image.cols;

    for (int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++)
        {
            cv::Vec3f v0 = model->vert(face[j]);
            cv::Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0[0]+1.) * width/2.;
            int y0 = (v0[1]+1.) * height/2.;
            int x1 = (v1[0]+1.) * width/2.;
            int y1 = (v1[1]+1.) * height/2.;

            if(using_my_function)
                my_line
                    (
                        image,
                        cv::Point(x0, height - y0),
                        cv::Point(x1, height - y1),
                        cv::Vec3b(255, 255, 255)
                    );
            else
                cv::line
                    (
                        image,
                        cv::Point(x0, height - y0),
                        cv::Point(x1, height - y1),
                        cv::Scalar(255, 255, 255),
                        1, CV_AA
                    );
        }
    }
}

int main()
{
    const int width  = 800;
    const int height = 800;
    const std::string filename = "african_head.obj";

    Model* model = new Model(filename.c_str());

    cv::Mat using_my_func(width, height, CV_8UC3, cv::Scalar(0));
    cv::Mat using_cv_func(width, height, CV_8UC3, cv::Scalar(0));
    cv::Mat circles(width, height, CV_8UC3, cv::Scalar(0));

    depict_model(using_my_func, model, true);
    depict_model(using_cv_func, model, false);
    depict_circles(circles);

    cv::imshow( "Using my function", using_my_func);
    cv::imshow( "Using cv function", using_cv_func);
    cv::imshow( "Circles", circles);

    cv::waitKey(0); // Wait for a keystroke in the window

    system("Pause");
    return 0;
}
