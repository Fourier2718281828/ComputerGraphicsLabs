#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "VectorScope.h"

int main()
{
    std::string str = "Image";
    std::string imageName ("photos/original.tif");
    int rows = 512;
    int cols = 512;
    cv::Vec3b ui_color = cv::Vec3b(255,255,0);
    cv::Vec3b graph_color = cv::Vec3b(0,255,0);
	cv::Mat image = cv::imread(imageName.c_str(), CV_LOAD_IMAGE_COLOR );
	cv::Mat vector_scope(rows, cols, CV_8UC3, cv::Scalar(0));

	if (image.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    draw_vector_scope(image, vector_scope, ui_color, graph_color, 250, 300);

    cv::imshow( "Display window", image );                // Show our image inside it.
    cv::imshow( "VectorScope", vector_scope);                // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    system("Pause");
    return 0;
}
