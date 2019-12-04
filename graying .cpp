//
// Created by 27689 on 2019/12/4.
//
cv::Mat graying(cv::Mat &img) {
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
            p2++;
            p++;
         //   Vec3b &pix = *p++;//彩色图                             //pix指向内容
         //   uchar &pix2 = *p2++;//灰度图                           //&pix指向地址
         //   pix2 = pix[0] * 0.114 + pix[1] * 0.587 + pix[2] * 0.299;
        }
    }


    return grayImg;
}
