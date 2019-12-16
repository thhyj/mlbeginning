//
// Created by 27689 on 2019/12/4.
//
//#include "Kernel.cpp"
extern void OutPut(string name, cv::Mat &a);
void doubleThresholdDetection(Mat &img1);//双阈值检测
int getNum(int i, int j, int col) {
    return i * col + j;
}

cv::Mat filterlengthways(cv::Mat img1) {
    cv::Mat img;
    img1.copyTo(img);
    int row = img.rows;
    int col = img.cols;
    vector<int> temp[row];
    for (int i = 0; i < row; ++i) {
        uchar *p = img.ptr<uchar>(i);
        for (int j = 0; j < col; ++j) {
            temp[i].push_back((int) (*p));
            p++;
        }
    }
    cv::Mat zero = Mat(cv::Size(col, row), CV_8UC1, Scalar(0));
    zero.copyTo(img);
    for (register int i = 1; i < row - 1; ++i) {                        //竖直方向滤波，算子为
        for (register int j = 1; j < col - 1; ++j) {                    //-1 0 1
            int temp1 = 0;                                              //-2 0 2
            temp1 -= temp[i - 1][j - 1];                                //-1 0 1      该算子可以求出水平方向的导数
            temp1 -= temp[i][j - 1] * 2;
            temp1 -= temp[i + 1][j - 1];
            temp1 += temp[i - 1][j + 1];
            temp1 += temp[i][j + 1] * 2;
            temp1 += temp[i + 1][j + 1];
            if (temp1 < 0) temp1 = -temp1;
            if (temp1 > 255) temp1 = 255;
            img.at<uchar>(i, j) = temp1;
        }
    }
    return img;
}

cv::Mat filtercrossways(cv::Mat img1) {
    cv::Mat img;
    img1.copyTo(img);
    int row = img.rows;
    int col = img.cols;
    vector<int> temp[row];
    for (int i = 0; i < row; ++i) {
        uchar *p = img.ptr<uchar>(i);
        for (int j = 0; j < col; ++j) {
            temp[i].push_back((int) (*p));
            p++;
        }
    }
    cv::Mat zero = Mat(cv::Size(col, row), CV_8UC1, Scalar(0));
    zero.copyTo(img);
    for (register int i = 1; i < row - 1; ++i) {
        for (register int j = 1; j < col - 1; ++j) {            //水平方向滤波, 算子为
            int temp1 = 0;                                      //-1 -2 -1
            temp1 -= temp[i - 1][j - 1];                        // 0  0  0
            temp1 -= temp[i - 1][j] * 2;                        // 1  2  1      求出竖直方向的导数
            temp1 -= temp[i - 1][j + 1];
            temp1 += temp[i + 1][j - 1];
            temp1 += temp[i + 1][j] * 2;
            temp1 += temp[i + 1][j + 1];
            if (temp1 < 0) temp1 = -temp1;
            if (temp1 > 255) temp1 = 255;
            img.at<uchar>(i, j) = temp1;
        }
        // puts("");
    }
    return img;
}

void imageBinaryzation(Mat img, int thresholdVal = 0) {                //尝试对边缘进行单固定阈值二值化，但效果不好
    Mat img1;
    img.copyTo(img1);
    Mat_<uchar>::iterator it1 = img1.begin<uchar>();
    Mat_<uchar>::iterator itend1 = img1.end<uchar>();
    for (; it1 != itend1; ++it1) {
        (*it1) > thresholdVal ? (*it1) = 255 : (*it1) = 0;             //如果像素点灰度值大于阈值，灰度置为最大值，否则灰度置为0;
    }
    OutPut("Binaryzation", img1);
}

bool check(int i, int j, int &row, int &col) {                  //检测数组是否越界
    return ((i >= 0) && (i < row) && (j >= 0) && (j < col));
}

void add(Mat &img, int i, int j, int &row, int &col, int &cnt, int &all) {
    if (check(i, j, row, col)) {
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

void autoImageBinaryzation1(Mat img) { //阈值为整行像素点灰度值的平均值
    int row = img.rows, col = img.cols;
    Mat img1;
    img.copyTo(img1);
    for (int i = 0; i < row; ++i) {
        uchar *p = img1.ptr<uchar>(i);
        int aver = 0;

        for(int j = 0; j < col; ++j) {
            aver += *p;
            ++p;
        }
        aver /= col;
        p =  img1.ptr<uchar>(i);
        for (int j = 0; j < col; ++j) {
            (*p) > /*getaver(img, i, j) * 1.5*/ aver ? 0 : (*p) = 0;
            ++p;
        }
    }
    OutPut("autoBinaryzation1", img1);
}
void autoImageBinaryzation2(Mat img) { //阈值为整列像素点灰度值的平均值
    int row = img.rows, col = img.cols;
    Mat img1;
    img.copyTo(img1);
    for(int j = 0; j < col; ++j) {
        int aver = 0;
        for(int i = 0; i < row; ++i) {
            aver += img.at<uchar>(i, j);
        }
        aver /= row;
        for(int i = 0; i < row; ++i) {
            img1.at<uchar>(i, j) > aver ? 0 : img1.at<uchar>(i, j) = 0;
        }
    }
    OutPut("autoBinaryzation2", img1);
}
void autoImageBinaryzation3(Mat img) { //阈值为整列以及整行像素点灰度值的几何平均值
    int row = img.rows, col = img.cols;
    Mat img1;
    vector<int> sum;//sum[i]存储的是当前行所有像素点灰度值的和
    img.copyTo(img1);
    sum.resize(row);
    for(int i = 0; i < row; ++i) {
        sum[i] = 0;
        for(int j = 0; j < col; ++j) {
            sum[i] += img.at<uchar>(i, j);
        }
    }
    for(int j = 0; j < col; ++j) {
        int averlengthway = 0, sum1 = 0, avercrossway = 0, aver;
        for(int i = 0; i < row; ++i) {
            sum1 += img.at<uchar>(i, j);
        }
        averlengthway = sum1 / row;

        for(int i = 0; i < row; ++i) {
            avercrossway = sum[i] / col;
            aver = sqrt(avercrossway * avercrossway + averlengthway * averlengthway);
            img1.at<uchar>(i, j) > aver ? 0 : img1.at<uchar>(i, j) = 0;

        }
    }
    OutPut("autoBinaryzation3", img1);
}
void autoImageBinaryzation4(Mat img) { //阈值为列向相邻以及行向相邻灰度值的几何平均值
    int row = img.rows, col = img.cols;
    Mat img1;
    img.copyTo(img1);
    int avercrossway, averlengthway, sumcrossway, sumlengthway, cntcrossway, cntlengthway, aver;
    for(int j = 0; j < col; ++j) {
        for(int i = 0; i < row; ++i) {
            sumcrossway = sumlengthway = cntcrossway = cntlengthway = 0;
            for(int k = -4; k <= 4; ++k) {
                if(check(i, j + k, row, col)) {
                    sumlengthway += img.at<uchar>(i, j + k);
                    cntlengthway ++;
            }
                if(check(i + k, j, row, col)) {
                    sumcrossway += img.at<uchar>(i + k, j);
                    cntcrossway ++;
                }
            }
            averlengthway = sumlengthway / cntlengthway;
            avercrossway = sumcrossway / cntcrossway;
            aver = sqrt(avercrossway * avercrossway + averlengthway * averlengthway);
            img1.at<uchar>(i, j) > aver * 0.9 ? 0 : img1.at<uchar>(i, j) = 0;
        }
    }
    OutPut("autoBinaryzation4", img1);
    doubleThresholdDetection(img1);

    OutPut("autoBinaryzation4dtd", img1);
}
void autoImageBinaryzation5(Mat img) { //阈值为列向相邻4格以及行向相邻4格灰度值的几何平均值
    int row = img.rows, col = img.cols;
    Mat img1;
    img.copyTo(img1);
    int avercrossway, averlengthway, sumcrossway, sumlengthway, cntcrossway, cntlengthway, aver;
    for(int j = 0; j < col; ++j) {
        for(int i = 0; i < row; ++i) {
            sumcrossway = sumlengthway = cntcrossway = cntlengthway = 0;
            for(int k = -4; k <= 4; ++k) {
                for(int g = -1; g < 1; ++g) {
                if(check(i + g, j + k, row, col)) {
                    sumlengthway += img.at<uchar>(i + g, j + k);
                    cntlengthway ++;
                }
                if(check(i + k, j + g, row, col)) {
                    sumcrossway += img.at<uchar>(i + k, j + g);
                    cntcrossway ++;
                 }
                }
            }
            averlengthway = sumlengthway / cntlengthway;
            avercrossway = sumcrossway / cntcrossway;
            aver = sqrt(avercrossway * avercrossway + averlengthway * averlengthway);
            img1.at<uchar>(i, j) > aver * 0.9 ? 0 : img1.at<uchar>(i, j) = 0;
        }
    }
    OutPut("autoBinaryzation5", img1);
    doubleThresholdDetection(img1);

    OutPut("autoBinaryzation5dtd", img1);
}
void autoImageBinaryzation6(Mat img) { //阈值为列向相邻4格范围内三格三格求梯度以及行向4格范围内三格三格求梯度的几何平均值
    int row = img.rows, col = img.cols;
    Mat img1;
    img.copyTo(img1);
    int avercrossway, averlengthway, sumcrossway, sumlengthway, cntcrossway, cntlengthway, aver;
    for(int j = 0; j < col; ++j) {
        for(int i = 0; i < row; ++i) {
            sumcrossway = sumlengthway = cntcrossway = cntlengthway = 0;
            for(int k = -4; k <= 4; ++k) {
                for(int g = -2; g < 2; ++g) {
                    if(check(i + g, j + k, row, col)) {
                        sumlengthway += img.at<uchar>(i + g, j + k);
                        cntlengthway ++;
                    }
                    if(check(i + k, j + g, row, col)) {
                        sumcrossway += img.at<uchar>(i + k, j + g);
                        cntcrossway ++;
                    }
                }
            }
            averlengthway = sumlengthway / cntlengthway;
            avercrossway = sumcrossway / cntcrossway;
            aver = sqrt(avercrossway * avercrossway + averlengthway * averlengthway);
            img1.at<uchar>(i, j) > aver * 0.9 ? 0 : img1.at<uchar>(i, j) = 0;
        }
    }
    OutPut("autoBinaryzation6", img1);
    doubleThresholdDetection(img1);

    OutPut("autoBinaryzation6dtd", img1);

    OutPut("myfilter", img1);
}
const double pi = acos(-1);
const double zone[8] = {atan2(1, 3), atan2(3, 1), atan2(3, -1), atan2(1, -3),
                        2 * pi + atan2(-1, -3), 2 * pi + atan2(-3, -1), 2 * pi + atan2(-3, 1), 2 * pi + atan2(-1, 3)};

int getType(double t) {
    for (int i = 0; i < 8; ++i) {
        if (t >= zone[7] || t <= zone[0]) return 0;
        if (t >= zone[0] && t <= zone[1]) return 1;
        if (t >= zone[1] && t <= zone[2]) return 2;
        if (t >= zone[2] && t <= zone[3]) return 3;
        if (t >= zone[3] && t <= zone[4]) return 0;
        if (t >= zone[4] && t <= zone[5]) return 1;
        if (t >= zone[5] && t <= zone[6]) return 2;
        if (t >= zone[6] && t <= zone[7]) return 3;
    }
    puts("你在秀nm呢");
    throw "你在秀nm呢";
}

double getVal(double *a, int i, int j, int col) {
    return *(a + i * col + j);
}

void nonMaximumSuppression(Mat img, vector<double> &gradient) {
    int col = img.cols, row = img.rows;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            switch (getType(gradient[getNum(i, j, col)])) {
                case 0:
                    if (check(i, j - 1, row, col) && img.at<uchar>(i, j - 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if (check(i, j + 1, row, col) && img.at<uchar>(i, j + 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    break;
                case 1:
                    if (check(i - 1, j + 1, row, col) && img.at<uchar>(i - 1, j + 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if (check(i + 1, j - 1, row, col) && img.at<uchar>(i + 1, j - 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    break;
                case 2:
                    if (check(i - 1, j, row, col) && img.at<uchar>(i - 1, j) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if (check(i + 1, j, row, col) && img.at<uchar>(i + 1, j) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    break;
                case 3:
                    if (check(i + 1, j + 1, row, col) && img.at<uchar>(i + 1, j + 1) > img.at<uchar>(i, j)) {
                        img.at<uchar>(i, j) = 0;
                    }
                    if (check(i - 1, j - 1, row, col) && img.at<uchar>(i - 1, j - 1) > img.at<uchar>(i, j)) {
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
    cv::Mat temp;
    img1.copyTo(temp);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (temp.at<uchar>(i, j) > highTh) {
                continue;
            } else {
                if (temp.at<uchar>(i, j) < lowTh) {
                    img1.at<uchar>(i, j) = 0;
                    continue;
                } else {
                    if (lowthcheck(temp, i - 1, j - 1, row, col) ||
                        lowthcheck(temp, i - 1, j, row, col) ||
                        lowthcheck(temp, i - 1, j + 1, row, col) ||
                        lowthcheck(temp, i, j - 1, row, col) ||
                        // lowthcheck(temp, i, j , row, col) ||
                        lowthcheck(temp, i, j + 1, row, col) ||
                        lowthcheck(temp, i + 1, j - 1, row, col) ||
                        lowthcheck(temp, i + 1, j, row, col) ||
                        lowthcheck(temp, i + 1, j + 1, row, col)
                            ) {
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
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int a = img1.at<uchar>(i, j), b = img2.at<uchar>(i, j);
            int temp = sqrt(a * a + b * b);
            gradient.push_back(atan2(b, a));
            if (gradient[getNum(i, j, col)] < 0) gradient[getNum(i, j, col)] += 2 * pi;
            img.at<uchar>(i, j) = temp;
        }
    }
 //   autoImageBinaryzation1(img);
   // autoImageBinaryzation2(img);
    //autoImageBinaryzation3(img);
    //autoImageBinaryzation4(img);
   // autoImageBinaryzation5(img);
    autoImageBinaryzation6(img);
    imageBinaryzation(img, 80);
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
    cv::Mat imgl = filterlengthways(img);// 对竖直方向滤波
    //   cv::imshow("235",img);
    cv::Mat img2 = filtercrossways(img);//  对水平方向滤波
    OutPut("heng", img2);               //  输出横向和纵向的滤波效果图
    OutPut("zong", imgl);
    return Combine(imgl, img2);         //  对竖直方向和水平方向的滤波结果进行组合，得到最终边缘
}

