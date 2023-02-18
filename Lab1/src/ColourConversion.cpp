#include "ColourConversion.h"

cv::Vec3f RGB_2_YCbCr(cv::Vec3b  vec)
{
    uchar fr = vec[2];
    uchar fg = vec[1];
    uchar fb = vec[0];

    float Y =  static_cast<float>(0.299 * fr + 0.587 * fg + 0.114 * fb);
    float Cb = static_cast<float>(-0.169 * fr - 0.331 * fg + 0.500 * fb);
    float Cr = static_cast<float>(0.500 * fr - 0.418 * fg - 0.082 * fb);

    return cv::Vec3f(Y, Cb, Cr);
}

