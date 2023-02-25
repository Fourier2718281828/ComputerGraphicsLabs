#include <iostream>
#include <cstdlib>
#include <time.h>
#include <exception>
#include "model.h"
#include "Triangles.h"

void depict_model(cv::Mat& image, Model* const model)
{
    const int width  = image.rows;
    const int height = image.cols;
    srand(time(0));

    for (int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model->face(i);
        cv::Point screen_coords[3];
        for (int j=0; j<3; j++)
        {
            cv::Vec3f world_coords = model->vert(face[j]);
            screen_coords[j] = cv::Point
            (
                (world_coords[0] + 1.) * width/2.,
                std::abs(height - (world_coords[1] + 1.) * height/2.)
            );
        }

        safe_draw_triangle
        (
            image,
            screen_coords[0],
            screen_coords[1],
            screen_coords[2],
            cv::Vec3b(rand()%255, rand()%255, rand()%255)
        );
    }
}

int main()
{
    const int width  = 800;
    const int height = 800;
    const std::string filename = "african_head.obj";

    Model* model = new Model(filename.c_str());

    cv::Mat using_my_func(width, height, CV_8UC3, cv::Scalar(0));
   /* draw_triangle(using_my_func,
             cv::Point(100+0, 0),
             cv::Point(100+0, 300),
             cv::Point(100+100, 100),
             cv::Vec3b(100+100, 100, 100)
             );*/
    depict_model(using_my_func, model);
    cv::imshow( "Using my function", using_my_func);

    cv::waitKey(0); // Wait for a keystroke in the window

    system("Pause");
    return 0;
}
