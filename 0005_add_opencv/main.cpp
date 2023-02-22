#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

int main()
{
    std::cout << "Add OpenCV" << std::endl;
    cv::Mat myImage = cv::Mat::zeros(500,500,CV_8UC3);

    cv::imshow("myImage", myImage);
    cv::waitKey(0);
    return 0;
}