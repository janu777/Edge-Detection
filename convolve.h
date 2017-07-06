#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
Mat convolve(Mat image, Mat kernel)
{
	Mat result(image.rows,image.cols,CV_8UC1);
	/*int inttype = image.type();
    string r, a;
    uchar depth = inttype & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (inttype >> CV_CN_SHIFT);
    switch ( depth ) {
        case CV_8U:  r = "8U";   a = "Mat.at<uchar>(y,x)"; break;  
        case CV_8S:  r = "8S";   a = "Mat.at<schar>(y,x)"; break;  
        case CV_16U: r = "16U";  a = "Mat.at<ushort>(y,x)"; break; 
        case CV_16S: r = "16S";  a = "Mat.at<short>(y,x)"; break; 
        case CV_32S: r = "32S";  a = "Mat.at<int>(y,x)"; break; 
        case CV_32F: r = "32F";  a = "Mat.at<float>(y,x)"; break; 
        case CV_64F: r = "64F";  a = "Mat.at<double>(y,x)"; break; 
        default:     r = "User"; a = "Mat.at<UKNOWN>(y,x)"; break; 
    }   
    r += "C";
    r += (chans+'0');
    cout << "Mat is of type " << r << " and should be accessed with " << a << endl;
    waitKey(0);
	image.copyTo(result);*/
	int c = image.cols;
  	int r = image.rows;
  	int l = (kernel.rows- 1)/2;
  	int u =0;
  	int v =0;
  	for(int x = 0; x<r ; x++)
  	{
  		for(int y = 0; y<c ; y++)
  		{
  			int val = 0;

  			for(int j = -l,u = 0; j<=l; j++,u++)
  			{
  				v = 0;
  				for(int k = -l; k<=l; k++,v++)
  				{
  					int p = x - j;
  					int q = y - k;
  					int pix = int(image.at<uchar>(p,q));
  					val = val+(pix*kernel.at<double>(u,v));
  				}
  			}
  			val = (val<0?0:val);	
  			result.at<uchar>(x,y) = val;
  		}
  	}
  	return result;
}