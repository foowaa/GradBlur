/*
parameters: img: Mat to be blured; anchor: Point; r: the complexity of blurring
return: see: Mat
author: Chunlin Tian
date: 2018/1/26
*/
#include "blur_optimal.h"
cv::Mat gradBlur(const cv::Mat& img, const cv::Point anchor, int r){
	int row = img.size().width;
	int col = img.size().height;

	int x0 = anchor.x;
	int y0 = anchor.y;

	//r<=x0, r<=row-x0; r<=y0, r<=col-y0
	//TODO: if r is illegal
	//FIXED NOW
	int min_res = std::min({ x0, row - x0, y0, col - y0 });
	if (min_res < r){
		r = min_res;
		if (r == 0){
			x0 = 10;
			y0 = 10;
			r = 5;
		}
	}
	int stepx1 = x0 / r;
	int stepx2 = (row - x0) / r;
	int stepy1 = y0 / r;
	int stepy2 = (col - y0) / r;


	std::vector<cv::Mat> src;
	cv::Mat mask1, mask2, mask, tmp, see;

	img.convertTo(img, CV_8UC3); 
	see = cv::Mat::Mat(row, col, CV_8UC3, CV_RGB(255, 255, 255));
	for (int i = 1; i < r; i++){
		src.push_back(img.clone());
		int kernel_siz = -2 * i + 2 * r + 1;
		tmp = cv::Mat::Mat(row, col, CV_8UC3, CV_RGB(255, 255, 255)); 

		//Gaussian OR mean blur
		//cv::GaussianBlur(src[i - 1], tmp, cv::Size(kernel_siz, kernel_siz), 0, 0);
		cv::blur(src[i - 1], tmp, cv::Size(kernel_siz, kernel_siz), cv::Point(-1, -1));

		cv::Rect rect1(stepx1*(i - 1), stepy1*(i - 1), row - (stepx1 + stepx2)*(i - 1), col - (stepy1 + stepy2)*(i - 1));
		cv::Rect rect2(stepx1*i, stepy1*i, row - (stepx1 + stepx2)*i, col - (stepy1 + stepy2)*i);
		mask1 = cv::Mat::zeros(row, col, CV_8UC1);
		mask2 = mask1.clone();
		mask = mask1.clone();
		mask1(rect1).setTo(255);
		mask2(rect2).setTo(255);
		bitwise_xor(mask1, mask2, mask);
		tmp.copyTo(see, mask);
		if (i == r - 1){
			src.push_back(img.clone());
			src[i].copyTo(see, mask2);
		}
	}

	return see;
}