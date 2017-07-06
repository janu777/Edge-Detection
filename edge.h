#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <convolve.h>
#include <gaussian_blur.h>
using namespace std;
using namespace cv;
/* we will be using Prewitt, Sobel operators
and see how each one of them work*/
void edge_detector(Mat gray)
{
	Mat skernel = (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
	Mat pkernel = (Mat_<double>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
	double mag;
	double dir;
	Mat magnitude;
	Mat direction;
	gray.copyTo(magnitude);
	gray.copyTo(direction);
	Mat skernel1,pkernel1;
	transpose(skernel,skernel1);
	transpose(pkernel,pkernel1);
	Mat sob = convolve(gray,skernel);
	Mat pre = convolve(gray,pkernel);
	Mat sob1 = convolve(gray,skernel1);
	Mat pre1 = convolve(gray,pkernel1);
	for(int x =0;x<gray.rows;x++)
	{
		for(int y=0;y<gray.cols;y++)
		{
			double s = pre.at<double>(x,y);
			double s1 = pre1.at<double>(x,y); 
			mag = sqrt((s*s)+s1*s1);
			dir = atan(s/s1);
			magnitude.at<double>(x,y)=mag;
			direction.at<double>(x,y)=dir;
		}
	}
	namedWindow("sobel", CV_WINDOW_NORMAL );
  	namedWindow("Prewitt", CV_WINDOW_NORMAL );
  	namedWindow("original", CV_WINDOW_NORMAL );
  	imshow("sobel",sob);
  	imshow("Prewitt",pre);
  	imshow("original",gray);
  	waitKey(0);
}