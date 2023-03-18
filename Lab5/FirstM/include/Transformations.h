#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <opencv2/core/core.hpp>

typedef float coord_t;
typedef float angle_t;
typedef cv::Mat_<coord_t> Matrix;

enum Axis
{
    X, Y, Z,
};

cv::Vec4f transform(const Matrix&, const cv::Vec4f&);
cv::Vec3f rotate(const cv::Vec3f& vec0, const angle_t phi, const Axis axis);
cv::Vec3f rotateX(const cv::Vec3f&, const angle_t);
cv::Vec3f rotateY(const cv::Vec3f&, const angle_t);
cv::Vec3f rotateZ(const cv::Vec3f&, const angle_t);

#endif // TRANSFORMATIONS_H
