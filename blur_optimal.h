#ifndef BLUR_OPTIMAL_H_
#define BLUR_OPTIMAL_H_
#include <algorithm>
#include <vector>
#include "opencv2/imgproc/imgproc.hpp"
cv::Mat gradBlur(const cv::Mat& img, const cv::Point anchor, int r);
#endif 