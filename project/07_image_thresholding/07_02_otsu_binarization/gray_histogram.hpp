#ifndef _GRAY_HISTOGRAM_HPP_
#define _GRAY_HISTOGRAM_HPP_

#include <opencv2/opencv.hpp>
using namespace cv;

Mat gray_histogram(const Mat img_gray, const int hist_w, const int hist_h, const Scalar color);

#endif // _GRAY_HISTOGRAM_HPP_