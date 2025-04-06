#include "opencv2/opencv.hpp"

#include<iostream>
#include<stdio.h>

using namespace std;

int main(int arg, char** argu) {
	cv::Mat img = cv::imread("test.jpg");

	imshow("img", img);
	cv::waitKey(0);

	return 0;
}