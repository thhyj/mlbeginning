using namespace std;
using namespace cv;
extern void shuchu();
void opentheimg(string name) {
    freopen("a.txt", "w", stdout);
    Mat img1 = imread(name + ".jpg", 1);
    cout << img1.cols << '\n' << img1.rows<<'\n';
    cout <<img1;
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

