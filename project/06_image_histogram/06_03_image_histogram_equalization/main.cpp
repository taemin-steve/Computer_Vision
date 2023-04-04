#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a grayscale image
    Mat srcImage = imread("unequalized.jpg", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (srcImage.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Histogram Equalization
    Mat dstImage;
    equalizeHist(srcImage, dstImage);

    // Display the result
    Mat rstImage;
    hconcat(srcImage, dstImage, rstImage);
    imshow("Histogram Equalization", rstImage);
    waitKey();

    // Histogram

    // Collect the images
    Mat imgs[] = {srcImage, dstImage};

    // Create the output histogram
    // src normal, src accumulate, dst normal, dst accumulate
    Mat hists[4]; // src

    // The number of bins
    int histSize = 256; // for every intensity

    // The value ranges
    float range[] = {0, 256}; // the upper boundary is exclusive
    const float* ranges[] = {range};

    // For each image: src vs. dst
    for(int i = 0; i < 2; i++)
    {
        // For each case: normal, accumulated
        for (int j = 0; j < 2; j++)
        {
            // Calculate the image histogram
            calcHist(&imgs[i], 1, nullptr, Mat(), // do not use mask
                    hists[2*i+j], 1, &histSize, ranges,
                    true, // the histogram is uniform
                    j==0?false:true // not accumulate / accumulate
                    );
        }
    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}