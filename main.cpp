#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <edge.h>
#include <canny.h>

using namespace std;
using namespace cv; 

int main()
{
	Mat original = imread("/home/linux/Image processing/Pictures/lena.jpg");
	Mat gray,Gauss;
	cvtColor(original,gray,COLOR_BGR2GRAY);
	Mat canny;
	canny = canny_edge(gray,8,15);
	return 0;
}