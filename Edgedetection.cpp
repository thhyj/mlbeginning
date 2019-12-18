extern string Name;
void Edgedetection() {
    cin >> Name;                            //输入图片名
    mkdir(Name.c_str());                    //创建名字为图片名的文件夹
    Mat &&img1 = imread(Name + ".jpg", 1);
    if(img1.empty()) {
        puts("输入文件为空");
        exit(0);
    }
    OutPut("img", img1);                                        //输出原图
    Mat &&grayImg = Graying(img1);                              //图像灰度化
    OutPut("grayimg", grayImg);                                 //输出灰度图
    GaussianBlur(grayImg, grayImg, Size(5, 5), BORDER_DEFAULT); //进行高斯模糊（这个是最后懒了，觉得代码只是繁琐就不想手写，调的库
    Mat &&filterImg = filter(grayImg);                          //进行边缘检测
    OutPut("filter", filterImg);                                //输出结果图
    string outname;
    waitKey(0);
}//
// Created by 27689 on 2019/12/8.
//

