#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat srcImage,hsvImage;
    srcImage = imread("");
    cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
    int hueBinNum = 30;
    int saturationBinNum = 32;
    int histSize[] = {hueBinNum,saturationBinNum};
    float hueRanges[] = {0,180};
    float saturationRanges[] = {0,180};
    const float* ranges[] = {hueRanges,saturationRanges};
    MatND dstHist;
    int channels[] = {0,1};
    
    calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize, ranges,true,false);
    double maxValue=0;
    minMaxLoc(dstHist, 0,&maxValue,0,0);
    int scale =10;
    
    Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10, CV_8UC3);
    for(int hue =0;hue <hueBinNum;hue++)
    {
        for(int saturation =0; saturation < saturationBinNum;saturation++)
            {
                float binValue= dstHist.at<float>(hue,saturation);// 直方图的值
                int intensity = cvRound(binValue*255/maxValue);//intesity
                
                rectangle(histImg, Point(hue*scale,saturation*scale), Point((hue+1)*scale -1, (saturation+1)*scale - 1),Scalar::all(intensity),FILLED);
                imshow("sucai",srcImage);
                imshow("H-S zhifangtu", histImg);
                waitKey();
                
                
    
            }
    }
    
    
    
    return 0;
}



