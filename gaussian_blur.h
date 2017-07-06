#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <convolve.h>
using namespace std;
using namespace cv;
Mat gaussian_kernel(int window_size,float sigma)
{
	Mat H(window_size,window_size,CV_64F);
	double value,param,norm;
	double sum = 0;
	int k = (window_size - 1)/2; // window_size = 2K+1;
	int u = -k;
	int v = -k;
	int x = 0;
	int y = 0;
	norm = 1/(2*3.14*sigma*sigma);
	for(x =0;x<window_size;x++,u++)
	{
		v = -k;
		for(y =0;y<window_size;y++,v++)
		{
			param = -((u*u+v*v)/(2*sigma*sigma));
			value = norm*exp(param);
			H.at<double>(x,y) = value;
			sum = sum+value;
		}
	}
	for(x =0;x<window_size;x++)
	{
		for(y=0;y<window_size;y++)
		{
			H.at<double>(x,y) = H.at<double>(x,y)/sum;
		}
	}
	return H;
}	
Mat gaussian_blur(Mat gray,int window_size,float sigma)
{
	Mat Gauss;
	gray.copyTo(Gauss);
  	Mat kernel = gaussian_kernel(window_size,sigma);
  	Gauss = convolve(gray,kernel);	
  	return Gauss;
}