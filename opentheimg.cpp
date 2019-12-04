using namespace std;
using namespace cv;
void opentheimg(string name) {
    Mat img1 = imread(name + ".jpg");
    if(img1.empty()) {
        puts("你号没了");
    }
    imshow("1", img1);
    //  system("pause");
    while(1) {
        if(waitKey(30) == 27) break;
    }
}//
// Created by 27689 on 2019/12/4.
//

