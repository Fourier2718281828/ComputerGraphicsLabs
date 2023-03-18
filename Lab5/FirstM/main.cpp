#include <iostream>
#include "model.h"
#include "Transformations.h"

void depict_rotated_model(cv::Mat& image, Model* const model, const angle_t angle, const Axis axis)
{
    const int width  = image.rows;
    const int height = image.cols;

    for (int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++)
        {
            cv::Vec3f v00 = model->vert(face[j]);
            cv::Vec3f v10 = model->vert(face[(j+1)%3]);
            cv::Vec3f v0 = rotate(v00, angle, axis);
            cv::Vec3f v1 = rotate(v10, angle, axis);
            int x0 = (v0[0]+1.) * width/2.;
            int y0 = (v0[1]+1.) * height/2.;
            int x1 = (v1[0]+1.) * width/2.;
            int y1 = (v1[1]+1.) * height/2.;

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

    cv::Mat using_cv_func(width, height, CV_8UC3, cv::Scalar(0));

    depict_rotated_model(using_cv_func, model, 3.14/5, Y);
    cv::imshow( "Using cv function", using_cv_func);

    cv::waitKey(0); // Wait for a keystroke in the window

    system("Pause");
    return 0;
}
