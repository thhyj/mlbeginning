using namespace std;
using namespace cv;
extern void shuchu();
void gao() {
    //freopen("b.txt", "w", stdout);
    srand(time(0));
    Mat img1 = Mat(cv::Size(5,5),CV_8UC3, 100);
    cout << img1.cols << '\n' << img1.rows<<'\n';
    cout <<img1.at<Vec3b>(2, 3);
    for(int i = 0; i <= 4; ++i) {
        for(int j = 0; j <= 4; ++j) {
            img1.at<Vec3b>(i, j)[0] = rand();
            img1.at<Vec3b>(i, j)[1] = rand();
            img1.at<Vec3b>(i, j)[2] = rand();
        }
    }
    if(img1.empty()) {
        puts("你号没了");
    }
    namedWindow("1", WINDOW_NORMAL);
    imshow("1", img1);
    //  system("pause");
    shuchu();
    while(1) {
        if(waitKey(30) == 27) break;
    }
}//
// Created by 27689 on 2019/12/4.
//

