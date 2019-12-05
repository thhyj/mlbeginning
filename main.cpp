#include <opencv2/opencv.hpp>
#include <iostream>

#include "opentheimg.cpp"
#include "try1.cpp"
#include "graying.cpp"
#include "lvbo.cpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
inline void shuchu() {
    puts("233");
}
int main() {
    string name = "soccer";
    Mat img1 = imread(name + ".jpg", 1);
    cv::imshow("原始图", img1);
    Mat grayImg = graying(img1);
  //  grayImg = (img1.rows, img1.cols, CV_8U, Scalar(100));
    cv::imshow("灰度图", grayImg);
    GaussianBlur(grayImg, grayImg, Size(5, 5), BORDER_DEFAULT);
    Mat filterImg = filter(grayImg);

   // filterImg = cv2.Canny(grayImg, 256, 256);
    cv::imshow("filter", filterImg);
    waitKey(0);
    return 0;
}