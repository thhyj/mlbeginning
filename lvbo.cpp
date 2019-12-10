//
// Created by 27689 on 2019/12/4.
//
//#include "Kernel.cpp"
extern void OutPut(string name, cv::Mat &a);
int getNum(int i, int j, int col) {
    return i * col + j;
}
struct ConvolutionKernel {
    int r, c;
    vector<double> kernel;
    ConvolutionKernel(int r = 0, int c = 0):r(r), c(c){

    }
    InitLengthwayKernel() {
        r = 3, c = 3;
        kernel.resize(r * c);
        kernel[getNum(0, 0, c)] = 1;
        kernel[getNum(0, 1, c)] = 0;
        kernel[getNum(0, 2, c)] = 1;

        kernel[getNum(1, 0, c)] = 2;
        kernel[getNum(1, 1, c)] = 0;
        kernel[getNum(1, 2, c)] = 2;

        kernel[getNum(2, 0, c)] = 1;
        kernel[getNum(2, 1, c)] = 0;
        kernel[getNum(2, 2, c)] = 1;
    }
};
// 瞎写一时爽，重构火葬场
ConvolutionKernel kernelSobelLengthway, kernelSobelCrossway;

cv::Mat convolution(cv::Mat temp, int r, int c, vector<double> &kernel) {
    cv::Mat gg = Mat(temp.rows - r / 2, temp.cols - c / 2, CV_8U);
    int sum;
    for(int i = 1; i < r - 1; ++i) {
        for(int j = 1; j < c - 1; ++j) {
            sum = 0;
        }
    }
}
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
bool check(int i, int j, int &row, int &col) {
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
const double pi = acos(-1);
const double zone[8] = {atan2(1,3), atan2(3,1), atan2(3, -1), atan2(1, -3),
                        2 * pi + atan2(-1, -3), 2 * pi + atan2(-3, -1), 2 * pi + atan2(-3, 1), 2 * pi + atan2(-1, 3)};
int getType(double t) {
    for(int i = 0; i < 8; ++i) {
        if(t >= zone[7] || t <= zone[0]) return 0;
        if(t >= zone[0] && t <= zone[1] ) return 1;
        if(t >= zone[1] && t <= zone[2] ) return 2;
        if(t >= zone[2] && t <= zone[3] ) return 3;
        if(t >= zone[3] && t <= zone[4]) return 0;
        if(t >= zone[4] && t <= zone[5]) return 1;
        if(t >= zone[5] && t <= zone[6]) return 2;
        if(t >= zone[6] && t <= zone[7]) return 3;
    }
    puts("你在秀nm呢");
    throw "你在秀nm呢";
}

double getVal(double *a, int i, int j, int col) {
    return *(a + i * col + j);
}
void nonMaximumSuppression(Mat img, vector<double>&gradient) {
    int col = img.cols, row = img.rows;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            switch(getType(gradient[getNum(i, j, col)])) {
                case 0:
                    if(check(i, j - 1, row, col) && img.at<uchar>(i, j - 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if(check(i, j + 1, row, col) && img.at<uchar>(i, j + 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    break;
                case 1:
                    if(check(i - 1, j + 1, row, col) && img.at<uchar>(i - 1, j + 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if(check(i + 1, j - 1, row, col) && img.at<uchar>(i + 1, j - 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    break;
                case 2:
                    if(check(i - 1, j, row, col) && img.at<uchar>(i - 1, j) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if(check(i + 1, j, row, col) && img.at<uchar>(i + 1, j) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    break;
                case 3:
                    if(check(i + 1, j + 1, row, col) && img.at<uchar>(i + 1, j + 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if(check(i - 1, j - 1, row, col) && img.at<uchar>(i - 1, j - 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    break;
            }
        }
    }
}
const int lowTh = 50, highTh = 120;
inline bool lowthcheck(Mat &img, int i, int j, int row, int col) {
    return check(i, j, row, col) && img.at<uchar>(i, j) > highTh;
}
void doubleThresholdDetection(Mat &img1) {
    int col = img1.cols, row = img1.rows;
    cv:: Mat temp;
    img1.copyTo(temp);
    for(int i = 0 ; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if(temp.at<uchar>(i, j) > highTh) {
                continue;
            } else {
                if(temp.at<uchar>(i, j) < lowTh) {
                    img1.at<uchar>(i, j) = 0;
                    continue;
                } else {
                    if(lowthcheck(temp, i - 1, j - 1, row, col) ||
                    lowthcheck(temp, i - 1, j, row, col) ||
                    lowthcheck(temp, i - 1, j + 1, row, col) ||
                    lowthcheck(temp, i, j - 1, row, col) ||
                   // lowthcheck(temp, i, j , row, col) ||
                    lowthcheck(temp, i, j + 1, row, col) ||
                    lowthcheck(temp, i + 1, j - 1, row, col) ||
                    lowthcheck(temp, i + 1, j, row, col) ||
                    lowthcheck(temp, i + 1, j + 1, row, col)
                    ) {
                    //    temp.at<uchar>(i,j) *= 1.5;//这里是瞎搞的
                    //    img1.at<uchar>(i,j) *= 1.5 ;
                        continue;
                    } else {
                        img1.at<uchar>(i, j) = 0;
                    }
                }
            }
        }
    }
}
cv::Mat Combine(Mat &img1, Mat &img2) {
    int row = img1.rows, col = img2.cols;
    Mat img = Mat(row, col, CV_8U);
  //  vector<vector<double> > newOne(row, vector<int>(col, 0));
    vector<double> gradient;//[col];
   // double gradient[row][col];
    for(int i = 0 ; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            int a = img1.at<uchar>(i, j), b = img2.at<uchar>(i, j);
            int temp = sqrt(a * a + b * b);
            gradient.push_back(atan2(b, a));
            if(gradient[getNum(i, j, col)] < 0) gradient[getNum(i, j, col)] += 2 * pi;
            img.at<uchar>(i, j) = temp;
        }
    }
    OutPut("beforenms", img);
    nonMaximumSuppression(img, gradient);
   OutPut("beforedtd", img);
    doubleThresholdDetection(img);
    //imageBinaryzation(img, 100);
   // autoImageBinaryzation(img);
    return img;
}

cv::Mat filter(cv::Mat img) {
  //  cv::imshow("236",img);
    cv::Mat imgl = filterlengthways(img);// 对竖直方向
 //   cv::imshow("235",img);
    cv::Mat img2 = filtercrossways(img);//  对水平方向
    OutPut("heng",img2);
    OutPut("zong",imgl);
    return Combine(imgl, img2);
}

