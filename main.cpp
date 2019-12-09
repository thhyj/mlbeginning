#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include "cv.h"
#include "sensor.cpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
void gInt(int &v) {
    static char ch;
    bool p = 0;
    v = 0;
    do{
        ch = getchar();
        if(ch == '-') p = 1;
    } while(!isdigit(ch));
    while(isdigit(ch)) {
        v = (v + (v << 2) << 1) + (ch ^'0');
        ch = getchar();
    }
    if(p) v = -v;
}
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