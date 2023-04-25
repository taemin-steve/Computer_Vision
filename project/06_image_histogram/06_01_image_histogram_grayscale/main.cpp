#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a grayscale image
    Mat srcImage = imread("noisy2.png", 0);

    // Check if image loading is successful
    if (srcImage.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

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
    calcHist(&srcImage, 1, nullptr, Mat(), // do not use mask
             hist, 1, &histSize, ranges,
             true, // the histogram is uniform
             false // do not accumulate
             );

    // Histogram image
    int hist_w = 512, hist_h = 400; // 그냥 내가 원하는 크기의 window 
    int bin_w = cvRound((double) hist_w/histSize); // 하나의 bin의 size. 현재는 256칸을 나눠야 함!
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255)); // 
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat()); // 최소값 0, 최대값이 histImage의 높이가 되게끔 해달라!
    for(int i = 1; i < histSize; i++)
    {
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1))), //좌표계가 달라서 이렇게 해줘야함
                        Point(bin_w*(i),   hist_h - cvRound(hist.at<float>(i))),
                        Scalar(255, 0, 0), 2);
    }

    // Display the image and its histogram
    imshow("Source Image", srcImage);
    imshow("Histogram", histImage);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}