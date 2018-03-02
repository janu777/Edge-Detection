#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <gaussian_blur.h>
using namespace std;
using namespace cv;
/* we will be using Prewitt, Sobel and Roberts operator
and see how each one of them work*/
Mat double_threshold(Mat thin,int Tlow,int Thigh)
{
	int r = thin.rows;
	int c = thin.cols;
	Mat thresholded(r,c,CV_8UC1);
	thin.copyTo(thresholded);
	int sum = 1;
	for(int x=0;x<r;x++)
	{
		for(int y=0;y<c;y++)
		{
			if(int(thin.at<uchar>(x,y))>Thigh)
			{	
				thresholded.at<uchar>(x,y) = 255; 
			}
			else if(int(thin.at<uchar>(x,y))<Tlow)
			{
				thresholded.at<uchar>(x,y) = 0;
			}
		}
	}
	while(sum!=0)
	{
		sum = 0;
		for(int x=0;x<r;x++)
		{
			for(int y=0;y<c;y++)
			{
				if(thresholded.at<uchar>(x,y) == 0 || thresholded.at<uchar>(x,y) == 255)
					continue;
				int flag = 0;
				for(int j = -1; j<=1; j++)
  				{
  					for(int k = -1; k<=1; k++)
  					{
  						int p = x + j;
  						int q = y + k;
  						if(thresholded.at<uchar>(p,q) == 255)
  						{
  							thresholded.at<uchar>(x,y) = 255;
  							sum+=1;
  							flag = 1;
  							break;
  						}
  						
  					}
  					if(flag == 1)
  						break;
  				}
			}
		}
	}
	for(int x=0;x<r;x++)
	{
		for(int y=0;y<c;y++)
		{
			if((thresholded.at<uchar>(x,y) != 255) && (thresholded.at<uchar>(x,y) != 0))
				thresholded.at<uchar>(x,y) = 0;
		}
	}
	return thresholded;
}
Mat non_maximal_supression(Mat magnitude,Mat direction)
{
	Mat new1;
	magnitude.copyTo(new1);
	int r = magnitude.rows;
	int c = magnitude.cols;
	int sum = 0;
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{	
			int angle = int(direction.at<uchar>(i,j));
			int MA,MB;
			int MC = int(magnitude.at<uchar>(i,j));
			if(angle == 0)
			{
				MA = int(magnitude.at<uchar>(i,j-1));
				MB = int(magnitude.at<uchar>(i,j+1));
			}
			else if(angle == 45)
			{
				MA = int(magnitude.at<uchar>(i-1,j+1));
				MB = int(magnitude.at<uchar>(i+1,j-1));
			}
			else if(angle == 90)
			{
				MA = int(magnitude.at<uchar>(i-1,j));
				MB = int(magnitude.at<uchar>(i+1,j));
			}
			else if(angle == 135)
			{
				MA = int(magnitude.at<uchar>(i-1,j-1));
				MB = int(magnitude.at<uchar>(i+1,j+1));
			}
			if(MA>MC || MB>MC)
				new1.at<uchar>(i,j)=0;				
		}
	}
	return new1;
}
Mat canny_edge(Mat gray,int Tlow,int Thigh)
{
	Mat blur;
	blur = gaussian_blur(gray,3,1);
	int val_x,val_y,mag;
	int newAngle;
	int thisAngle;
	int c = gray.cols;
  	int r = gray.rows;
  	Mat Gx(r,c,CV_8UC1);
  	Mat Gy(r,c,CV_8UC1);
  	Mat high_thresh(r,c,CV_8UC1);
  	Mat low_thresh(r,c,CV_8UC1);
  	Mat magnitude(r,c,CV_8UC1);
  	Mat direction(r,c,CV_8UC1);
  	Mat canny_kernel_x = (Mat_<double>(2, 2) << -1, 1, -1, 1);
  	Mat canny_kernel_y = (Mat_<double>(2, 2) << 1, 1, -1, -1);
	for(int x = 0; x<r ; x++)
  	{
  		for(int y = 0; y<c ; y++)
  		{
  			val_x = 0;
  			val_y = 0;
        		val_x = val_x+(int(blur.at<uchar>(x,y))*canny_kernel_x.at<double>(0,0));
        		val_x = val_x+(int(blur.at<uchar>(x,y+1))*canny_kernel_x.at<double>(0,1));
        		val_x = val_x+(int(blur.at<uchar>(x+1,y))*canny_kernel_x.at<double>(1,0));
        		val_x = val_x+(int(blur.at<uchar>(x+1,y+1))*canny_kernel_x.at<double>(1,1));
  			val_x = (val_x<0?0:val_x);	
  			Gx.at<uchar>(x,y) = val_x;
  			val_y = val_y+(int(blur.at<uchar>(x,y))*canny_kernel_y.at<double>(0,0));
        		val_y = val_y+(int(blur.at<uchar>(x,y+1))*canny_kernel_y.at<double>(0,1));
        		val_y = val_y+(int(blur.at<uchar>(x+1,y))*canny_kernel_y.at<double>(1,0));
        		val_y = val_y+(int(blur.at<uchar>(x+1,y+1))*canny_kernel_y.at<double>(1,1));
  			val_y = (val_y<0?0:val_y);	
  			Gy.at<uchar>(x,y) = val_y;
  			mag = sqrt((val_x*val_x)+ (val_y*val_y));
			thisAngle = (atan2(val_y,val_x)/3.14159) * 180.0;
  			if ( ( (thisAngle < 22.5) && (thisAngle > -22.5) ) || (thisAngle > 157.5) || (thisAngle < -157.5) )
				newAngle = 0;
			if ( ( (thisAngle > 22.5) && (thisAngle < 67.5) ) || ( (thisAngle < -112.5) && (thisAngle > -157.5) ) )
				newAngle = 45;
			if ( ( (thisAngle > 67.5) && (thisAngle < 112.5) ) || ( (thisAngle < -67.5) && (thisAngle > -112.5) ) )
				newAngle = 90;
			if ( ( (thisAngle > 112.5) && (thisAngle < 157.5) ) || ( (thisAngle < -22.5) && (thisAngle > -67.5) ) )
				newAngle = 135;
  			magnitude.at<uchar>(x,y) = mag;
  			direction.at<uchar>(x,y) = newAngle;
  		}
  	}
  	Mat thin = non_maximal_supression(magnitude,direction);
  	Mat thresholded = double_threshold(thin,Tlow,Thigh);
  	return thresholded;
}
