#include <opencv2/opencv.hpp>
#include <iostream>
#include "cv.h"
#include "sensor.cpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
inline void shuchu() {
    puts("233");
}
void OutPut(string name, cv::Mat &a) {
    namedWindow(name, WINDOW_NORMAL);
    cv::imshow(name, a);
}
int main() {
    edgedetection();
    return 0;
}