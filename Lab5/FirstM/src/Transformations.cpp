#include "Transformations.h"
#include <cmath>

Matrix getRotationMat(const angle_t phi, const Axis axis)
{
    const Matrix res(3, 3);
    const coord_t cos = std::cos(phi);
    const coord_t sin = std::sin(phi);

    switch(axis)
    {
        case X:
            res << 1.0f, 0.0f, 0.0f,
                   0.0f,  cos, -sin,
                   0.0f,  sin, -cos;
            break;
        case Y:
            res << cos,  0.0f, sin,
                   0.0f, 1.0f, 0.0f,
                   -sin, 0.0f, cos;
            break;
        case Z:
            res << cos , -sin, 0.0f,
                   sin ,  cos, 0.0f,
                   0.0f, 0.0f, 1.0f;
            break;
    }

    return res;

}

cv::Vec4f transform(const Matrix& mat, const cv::Vec4f& vec0)
{
    const Matrix vec(vec0);
    const Matrix res = mat * vec;
    return cv::Vec4f(res.ptr<float>());
}

cv::Vec3f rotate(const cv::Vec3f& vec0, const angle_t phi, const Axis axis)
{
    const Matrix vec(vec0);
    const Matrix rot(getRotationMat(phi, axis));
    const Matrix res = rot * vec;
    return cv::Vec3f(res.ptr<float>());
}


cv::Vec3f rotateX(const cv::Vec3f& vec, const angle_t a)
{
    return rotate(vec, a, X);
}

cv::Vec3f rotateY(const cv::Vec3f& vec, const angle_t a)
{
    return rotate(vec, a, Y);
}

cv::Vec3f rotateZ(const cv::Vec3f& vec, const angle_t a)
{
    return rotate(vec, a, Z);
}
