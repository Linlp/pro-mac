//
//  main.cpp
//  pircture
//
//  Created by linlp on 2018/1/21.
//  Copyright © 2018年 gcxy. All rights reserved.
//
/**/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//图像对比度、亮度调整 访问一个像素：image.at<Vec3b>(y,x)[c]
static void on_ContrastAndBright(int ,void*);

int g_nContrastValue;
int g_nBrightValue;
Mat g_srcImage,g_dstImage;
int main()
{
    g_srcImage = imread("/Users/gcxy/Desktop/opencv-terminal/5/5.3/1.jpg");
    //g_dstImage = Mat::zeros(g_dstImage.size(), g_srcImage.type());
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
    g_nContrastValue=80;
    g_nBrightValue=80;
    
    namedWindow("effective_window",1);
    createTrackbar("Brightness", "effective_window", &g_nContrastValue, 300,on_ContrastAndBright );
    createTrackbar("Contrast", "effective_window", &g_nBrightValue,200,on_ContrastAndBright );
    on_ContrastAndBright(g_nContrastValue,0);
    on_ContrastAndBright(g_nBrightValue,0);
    
    
    cout << endl << "run sucessfully";
    while(char(waitKey(1)) != 'q') {}
    return 0;
}

static void on_ContrastAndBright(int,void*)
{
    namedWindow("oringal_window",1);
    for (int y=0; y<g_srcImage.rows; y++)
    {
        for (int x=0; x<g_srcImage.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
               // g_dstImage.at<Vec3b>(y,x)[c]= saturate_cast<uchar>((g_nContrastValue*0.01)*(g_dstImage.at<Vec3b>(y,x)[c]) + g_nBrightValue);
                g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( (g_nContrastValue*0.01)*( g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );
                //g(x,y)=f(x,y)*a+b
                
            }
        }
    }
    imshow("oringal_window",g_dstImage);
    imshow("effective_window",g_dstImage);
}
