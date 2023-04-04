#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a grayscale image
    Mat srcImage = imread("home.jpg");

    // Check if image loading is successful
    if (srcImage.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Split BGR channels
    vector<Mat> BGR_planes;
    split(srcImage, BGR_planes);

    // void calcHist(const Mat *images, int nimages, const int *channels,
	//               InputArray mask, OutputArray hist,
    //               int dims, const int *histSize, const float **ranges,
    //               bool uniform = true, bool accumulate = false)

    // Create the output histogram
    vector<Mat> hists(3);

    // The number of bins
    int histSize = 256; // for every intensity

    // The value ranges
    float range[] = {0, 256}; // the upper boundary is exclusive
    const float* ranges[] = {range};

    // Calculate the image histogram
    for (int c = 0; c < 3; c++)
    {
        calcHist(&BGR_planes[c], 1, nullptr, Mat(), // do not use mask 
                 hists[c], 1, &histSize, ranges, 
                 true, // the histogram is uniform
                 false // do not accumulate
                 );
    }

    // Histogram image
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w/histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // For each channel
    for (int c = 0; c < 3; c++)
    {
        // Normalize the histogram in [0, rows]
        normalize(hists[c], hists[c], 0, histImage.rows, NORM_MINMAX, -1, Mat());

        // Draw the histogram
        Scalar color(c==0?255:0, c==1?255:0, c==2?255:0);
        for(int i = 1; i < histSize; i++)
        {
            line(histImage, Point(bin_w*(i-1), hist_h - cvRound(hists[c].at<float>(i-1))),
                            Point(bin_w*(i),   hist_h - cvRound(hists[c].at<float>(i))),
                            color, 2);

        }
    }

    // Display the image and its histogram
    imshow("Source Image", srcImage);
    imshow("Histogram", histImage);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}