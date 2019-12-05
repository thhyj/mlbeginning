//
// Created by 27689 on 2019/12/4.
//
// 数组越界真难搞，得把它提出来做mmp 这里有锅，得记着
cv::Mat filterlengthways(cv::Mat img1) {
    cv::Mat img;
    img1.copyTo(img);
    int row = img.rows;
    int col = img.cols;
    vector<int>temp[row];
    for(int i = 0; i < row; ++i) {
        uchar *p = img.ptr<uchar>(i);
        for(int j = 0 ; j < col; ++j) {
            temp[i].push_back((int)(*p));
            p++;
        }
    }
    cv::Mat zero = Mat(cv::Size(col,row),CV_8UC1, Scalar(0));
    zero.copyTo(img);
    for(register int i = 1; i < row - 1; ++i) {
        for(register int j = 1; j < col - 1; ++j) {
            int temp1 = 0;
            temp1 -= temp[i - 1][j - 1];
            temp1 -= temp[i][j - 1] * 2;
            temp1 -= temp[i + 1][j - 1];
            temp1 += temp[i - 1][j + 1];
            temp1 += temp[i][j + 1] * 2;
            temp1 += temp[i + 1][j + 1];
            if(temp1 < 0) temp1 = -temp1;
            if(temp1 > 255) temp1 = 255;
            img.at<uchar>(i, j) = temp1;}
    }
    return img;
}
cv::Mat filtercrossways(cv::Mat img1) {
    cv::Mat img;
    img1.copyTo(img);
    int row = img.rows;
    int col = img.cols;
    vector<int>temp[row];
    for(int i = 0; i < row; ++i) {
        uchar *p = img.ptr<uchar>(i);
        for(int j = 0 ; j < col; ++j) {
            temp[i].push_back((int)(*p));
            p++;
        }
    }
    cv::Mat zero = Mat(cv::Size(col,row),CV_8UC1, Scalar(0));
    zero.copyTo(img);
    for(register int i = 1; i < row - 1; ++i) {
        for(register int j = 1; j < col - 1; ++j) {
            int temp1 = 0;
            temp1 -= temp[i - 1][j - 1];
            temp1 -= temp[i - 1][j] * 2;
            temp1 -= temp[i - 1][j + 1];
            temp1 += temp[i + 1][j - 1];
            temp1 += temp[i + 1][j] * 2;
            temp1 += temp[i + 1][j + 1];
            if(temp1 < 0) temp1 = -temp1;
            if(temp1 > 255) temp1 = 255;
            img.at<uchar>(i, j) = temp1;
        }
        // puts("");
    }
    return img;
}
void imageBinaryzation(Mat img, int thresholdVal = 0) {
    Mat_<uchar>:: iterator it1 = img.begin<uchar>();
    Mat_<uchar>:: iterator itend1 = img.end<uchar>();
    for(; it1 != itend1; ++it1) {
        (*it1) > thresholdVal ? (*it1) = 255 : (*it1) = 0;
    }
}
bool check(int &i, int &j, int &row, int &col) {
    return ((i >= 0) && (i < row) && (j >= 0) && (j < col));
}
void add(Mat &img, int i, int j, int &row, int &col, int &cnt, int &all) {
    if(check(i, j, row, col)) {
        cnt++;
        all += img.at<uchar>(i, j);
    };
}
int getaver(Mat &img, int i, int j) {
    int cnt = 0, row = img.rows, col = img.cols, all = 0;
    add(img, i - 1, j - 1, row, col, cnt, all);
    add(img, i - 1, j + 1, row, col, cnt, all);
    add(img, i - 1, j, row, col, cnt, all);
    add(img, i, j - 1, row, col, cnt, all);
    add(img, i, j + 1, row, col, cnt, all);
    add(img, i, j, row, col, cnt, all);
    add(img, i + 1, j - 1, row, col, cnt, all);
    add(img, i + 1, j + 1, row, col, cnt, all);
    add(img, i + 1, j, row, col, cnt, all);
    return all / cnt;
}
void autoImageBinaryzation(Mat img) {
    int row = img.rows, col = img.cols;
    for(int i = 0; i < row; ++i) {
        uchar *p = img.ptr<uchar>(i);
        for(int j = 0; j < col; ++j) {
            (*p) > getaver(img, i, j) * 2? (*p) = 255 : (*p) = 0;
            ++p;
        }
    }
}
cv::Mat Combine(Mat &img1, Mat &img2) {
    int row = img1.rows, col = img2.cols;
    Mat img = Mat(row, col, CV_8U);
    for(int i = 0 ; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            int a = img1.at<uchar>(i, j), b = img2.at<uchar>(i, j);
            int temp = sqrt(a * a + b * b);
            img.at<uchar>(i, j) = temp;
        }
    }
    cv::imshow("before", img);
    imageBinaryzation(img, 100);
   // autoImageBinaryzation(img);
    return img;
}
cv::Mat filter(cv::Mat img) {
    cv::imshow("236",img);
    cv::Mat imgl = filterlengthways(img);
    cv::imshow("235",img);
    cv::Mat img2 = filtercrossways(img);
    cv::imshow("heng",img2);
    cv::imshow("zong",imgl);
    return Combine(imgl, img2);
}

