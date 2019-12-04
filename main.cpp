#include <opencv2/opencv.hpp>
#include <iostream>
#include "opentheimg.cpp"
#include "try1.cpp"
#include "graying .cpp"
#include "lvbo.cpp"
using namespace std;
using namespace cv;
inline void shuchu() {
    puts("233");
}
int main() {
    string name = "0_2";
    Mat img1 = imread(name + ".jpg", 1);
    cv::imshow("原始图", img1);
    Mat grayImg = graying(img1);
    cv::imshow("灰度图", grayImg);
    Mat filterImg = filter(img1);
    cv::imshow("竖直滤波", filterImg);
    waitKey(0);
    return 0;
}