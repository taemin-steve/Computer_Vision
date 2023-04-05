#include "gray_histogram.hpp"

Mat gray_histogram(const Mat img_gray, const int hist_w, const int hist_h, const Scalar color)
{
    // void calcHist(const Mat *images, int nimages, const int *channels,
	//               InputArray mask, OutputArray hist,
    //               int dims, const int *histSize, const float **ranges,
    //               bool uniform = true, bool accumulate = false)

    // Create the output histogram
    Mat hist;

    // The number of bins
    int histSize = 256; // for every intensity

    // The value ranges
    float range[] = {0, 256}; // the upper boundary is exclusive
    const float* ranges[] = {range};

    // Calculate the image histogram
    calcHist(&img_gray, 1, nullptr, noArray(), // do not use mask
             hist, 1, &histSize, ranges,
             true, // the histogram is uniform
             false // do not accumulate
             );

    // Histogram image
    int bin_w = cvRound((double) hist_w/histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // Normalize the histogram in [0, hist_h]
    normalize(hist, hist, 0, hist_h, NORM_MINMAX, -1, noArray());

    // Plot the histogram
    for(int b = 1; b < histSize; b++)
    {
        line(histImage, Point(bin_w*(b-1), hist_h - cvRound(hist.at<float>(b-1))),
                        Point(bin_w*(b),   hist_h - cvRound(hist.at<float>(b))),
                        color, 2);
    }

    return histImage;
}