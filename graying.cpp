//
// Created by 27689 on 2019/12/4.
//
cv::Mat Graying(cv::Mat img) {
    int row = img.rows;
    int col = img.cols;
  //  cv::imshow("灰度图", img);
    cv::Mat grayImg = Mat(row, col, CV_8U);
    cout << row << '\n' << col;
    for(register int i = 0; i < row; ++i) {
        Vec3b *p = img.ptr<Vec3b>(i);
        uchar *p2 = grayImg.ptr<uchar>(i);
        for(register int j = 0; j <=col; ++j) {
            *p2 = (*p)[0] * 0.114 + (*p)[1] * 0.587 + (*p)[2] * 0.299;
            //Gray = 0.2989*R+0.5870*G+0.1140*B 注意opencv的Mat类型是BGR顺序
            p2++;
            p++;
        }
    }
    return grayImg;
}
