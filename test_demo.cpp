/*
test demo
cltian
*/
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include "blur_optimal.h"
using namespace cv;
using namespace std;

Mat src;
char window_name[] = "Filter Demo 1";

int main(int argc, char** argv)
{
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	src = imread("lena.jpg", 1);

	clock_t begin = clock();
	Mat result = gradBlur(src, Point(306, 268), 11);
	clock_t end = clock();
	double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << " s" << endl;
	imshow(window_name,result);
	//imwrite("./img/gaussg/" + to_string(11) + ".jpg", result);
	waitKey(1500);
	getchar();
	return 0;
}

