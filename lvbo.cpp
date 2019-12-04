//
// Created by 27689 on 2019/12/4.
//
void add(uchar &a, uchar b) {
    if((int)a + (int)b > 255) {
        a = 255;
        return;
    }
    a+=b;
}
uchar mul(uchar a, uchar b) {
    if((int)a * (int)b > 255) {
        a = 255;
        return a;
    }
    a*=b;
    return a;
}
void minu(uchar &a, uchar b) {
    if((int)a - (int)b < 0) {
        a = 0;
        return;
    }
    a-=b;
}
// 数组越界真难搞，得把它提出来做mmp 这里有锅，得记着
cv::Mat filterlengthways(cv::Mat img) {
    int row = img.rows;
    int col = img.cols;
    cv::Mat temp;
    img.copyTo(temp);
    cv::Mat zero = Mat(cv::Size(row,col),CV_8UC1, Scalar(0));
    zero.copyTo(img);
    cv::imshow("qaq", temp);
    for(register int i = 1; i < row - 1; ++i) {
        for(register int j = 1; j < col - 1; ++j) {
            cout << (int)img.at<uchar>(i,j)<<' ';
        }
        puts("");
    }
    puts("-------------------------------------------------------------------------------------");
    for(register int i = 1; i < row - 1; ++i) {
        for(register int j = 1; j < col - 1; ++j) {
           // cout << "before " <<(int)(img.at<uchar>(i, j)) << '\n';
            minu(img.at<uchar>(i, j), temp.at<uchar>(i - 1, j - 1));
            minu(img.at<uchar>(i, j), mul(temp.at<uchar>(i, j - 1) , 2));
            minu(img.at<uchar>(i, j), temp.at<uchar>(i + 1, j - 1));

            add(img.at<uchar>(i, j), temp.at<uchar>(i - 1, j + 1));
            add(img.at<uchar>(i, j), mul(temp.at<uchar>(i, j + 1) , 2));
            add(img.at<uchar>(i, j), temp.at<uchar>(i + 1, j + 1));
           // cout << "after " <<(int)(img.at<uchar>(i, j)) << '\n';
          cout << (int)temp.at<uchar>(i,j)<<' ';
        }
        puts("");
    }
    puts("-------------------------------------------------------------------------------------");
    for(register int i = 1; i < row - 1; ++i) {
        for(register int j = 1; j < col - 1; ++j) {
              cout << (int)img.at<uchar>(i,j)<<' ';
        }
           puts("");
    }
    return img;
}
cv::Mat filter(cv::Mat img) {

    cv::Mat imgl = filterlengthways(img);
    return imgl;
}

