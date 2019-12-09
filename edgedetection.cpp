extern string Name;
void edgedetection() {
    cin >> Name;
    mkdir(Name.c_str());
    Mat &&img1 = imread(Name + ".jpg", 1);
    if(img1.empty()) {
        puts("你在输nm呢?");
        exit(0);
    }
    //  puts("233");
    OutPut("img", img1);
    Mat &&grayImg = graying(img1);
    OutPut("grayimg", grayImg);
    GaussianBlur(grayImg, grayImg, Size(5, 5), BORDER_DEFAULT);
    Mat &&filterImg = filter(grayImg);

//    filterImg = cv2.Canny(grayImg, 256, 256);
    //namedWindow("filter", WINDOW_AUTOSIZE);
    OutPut("filter", filterImg);
    string outname;
  //  cin >> outname;
  //  cv::imwrite(outname + ".jpg", filterImg);
    waitKey(0);
}//
// Created by 27689 on 2019/12/8.
//

