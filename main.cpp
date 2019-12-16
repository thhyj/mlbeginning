#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include <dir.h>
#include "cv.h"
#include "sensor.cpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
string Name;
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
void OutPut(string name, cv::Mat &a) {  //输出图像函数
    namedWindow(name, WINDOW_AUTOSIZE); //图片显示自适应窗口大小
    cv::imshow(name, a);                //显示图片
    cv::imwrite(Name + "/out" + name + ".jpg", a);//输出图片到图片名的文件夹中
}
int main() {
    Edgedetection();//进行边缘检测
    return 0;
}