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
void OutPut(string name, cv::Mat &a) {
    namedWindow(name, WINDOW_NORMAL);
    cv::imshow(name, a);
}
int main() {
    string name;
    cin >> name;
    Mat &&img1 = imread(name + ".jpg", 1);
    if(img1.empty()) {
        puts("你在输nm呢?");
        exit(0);
    }
  //  puts("233");
    OutPut("原始图", img1);
    Mat &&grayImg = graying(img1);
    OutPut("灰度图", grayImg);
    GaussianBlur(grayImg, grayImg, Size(5, 5), BORDER_DEFAULT);
   Mat &&filterImg = filter(grayImg);

//    filterImg = cv2.Canny(grayImg, 256, 256);
    //namedWindow("filter", WINDOW_AUTOSIZE);
    OutPut("filter", filterImg);
    string outname;
    cin >> outname;
    cv::imwrite(outname + ".jpg", filterImg);
    waitKey(0);
    return 0;
}