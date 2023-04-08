#include <iostream>
#include "model.h"
#include "Transformations.h"
#include "graphics.h"
#include "Triangle.h"
#include "ZBuffer.h"

cv::Vec3b reflection_clr(const cv::Vec3b& clr, cv::Point3f v1, cv::Point3f v2, cv::Point3f v3)
{
    double nx,ny,nz,k;
    v2.x -= v1.x;
    v2.y -= v1.y;
    v2.z -= v1.z;
    v3.x -= v1.x;
    v3.y -= v1.y;
    v3.z -= v1.z;

    nx = v2.y * v3.z - v3.y * v2.z;
    ny = -v2.x * v3.z + v3.x * v2.z;
    nz = v2.x * v3.y - v3.x * v2.y;

    k = 0.2 + 0.8*fabs(nz)/sqrt(nx*nx+ny*ny+nz*nz);

    return cv::Vec3b( k*(double)clr.val[0],
                      k*(double) clr.val[1],
                      k*(double)clr.val[2]);
}

void depict_rotated_model(cv::Mat& image, Model* const model, const angle_t angle, const Axis axis)
{
    ZBuffer::getInstance().clear();
    const int width  = image.rows;
    const int height = image.cols;
    cv::Vec3b color = cv::Vec3b(100,50,128);

    for (int i = 0; i < model->nfaces(); i++)
    {
        const std::vector<int> face = model->face(i);
        cv::Vec3f rotated[3] =
        {
            rotate(model->vert(face[0]), angle, axis),
            rotate(model->vert(face[1]), angle, axis),
            rotate(model->vert(face[2]), angle, axis)
        };
        const cv::Vec3b clr = reflection_clr
        (color,rotated[0], rotated[1], rotated[2]);
        cv::Point3f screen_coords[3];

        screen_coords[0] = cv::Point3f
        (
            (rotated[0][0] + 1.) * width/2.,
            std::abs(height - (rotated[0][1] + 1.) * height/2.),
            rotated[0][2]
        );

        screen_coords[1] = cv::Point3f
        (
            (rotated[1][0] + 1.) * width/2.,
            std::abs(height - (rotated[1][1] + 1.) * height/2.),
            rotated[1][2]
        );

        screen_coords[2] = cv::Point3f
        (
            (rotated[2][0] + 1.) * width/2.,
            std::abs(height - (rotated[2][1] + 1.) * height/2.),
            rotated[2][2]
        );

        safe_draw_triangle
        (
            image,
            screen_coords[0],
            screen_coords[1],
            screen_coords[2],
            clr
        );

    }
}

int main()
{
    const int width  = 800;
    const int height = 800;
    const std::string filename = "african_head.obj";

    Model* model = new Model(filename.c_str());

    cv::Mat using_cv_func(width, height, CV_8UC3, cv::Scalar(0));

    ZBuffer::getInstance().init(width, height);

    for (int Beta=200; ; Beta+=1)
    {
        ZBuffer::getInstance().clear();
        using_cv_func = cv::Scalar(0, 0, 0);
        depict_rotated_model(using_cv_func, model, Beta*3.14/180, Y);
        cv::imshow( "Model", using_cv_func);
        cv::waitKey(100);
    }
    cv::waitKey(0);

    system("Pause");
    return 0;
}
