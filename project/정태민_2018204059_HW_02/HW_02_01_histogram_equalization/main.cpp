#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a grayscale image
    Mat srcImage = imread("lena.jpg", IMREAD_COLOR);

    // Check if image loading is successful
    if (srcImage.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }
    
    Mat img_BGR[3];
    split(srcImage, img_BGR);

    Mat img_BGR_Equalized[3];
    equalizeHist(img_BGR[0],img_BGR_Equalized[0]);
    equalizeHist(img_BGR[1],img_BGR_Equalized[1]);
    equalizeHist(img_BGR[2],img_BGR_Equalized[2]);

    // Histogram Equalization
    Mat dstImage;
    merge(img_BGR_Equalized, 3 , dstImage);

    // Display the result
    Mat rstImage;
    vconcat(srcImage, dstImage, rstImage);
    // imshow("Histogram Equalization", rstImage);

    // Histogram

    // Collect the images
    Mat imgs[] = {img_BGR[0], img_BGR[1],img_BGR[2]};
    Mat imgs_Equalized [] = {img_BGR_Equalized[0], img_BGR_Equalized[1],img_BGR_Equalized[2]};

    // Create the output histogram
    // src normal, src accumulate, dst normal, dst accumulate
    Mat hists[3];
    Mat hists_Equalized[3];

    // The number of bins
    int histSize = 256; // for every intensity

    // The value ranges
    float range[] = {0, 256}; // the upper boundary is exclusive
    const float* ranges[] = {range};

    // For each image: src vs. dst
    for (int i = 0; i < 3; i++)
    {
        // Calculate the image histogram
        calcHist(&imgs[i], 1, nullptr, noArray(), // do not use mask
                hists[i], 1, &histSize, ranges,
                true, // the histogram is uniform
                false // not accumulate
                );

        calcHist(&imgs_Equalized[i], 1, nullptr, noArray(), // do not use mask
                hists_Equalized[i], 1, &histSize, ranges,
                true, // the histogram is uniform
                false // not accumulate
                );
    }

    // Histogram image
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w/histSize);
    Mat normalHistImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    Mat accumulatedHistImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // For each image: src vs. dst
    for (int i = 0; i < 3; i++)
    {
        // Color: src(blue), dst(red)
        Scalar color(i==0?255:0, i==2?255:0, i==1?255:0);

        // Normalize the histogram in [0, hist_h]
        normalize(hists[i], hists[i], 0, hist_h, NORM_MINMAX, -1, noArray());
        normalize(hists_Equalized[i], hists_Equalized[i], 0, hist_h, NORM_MINMAX, -1, noArray());


        // Total sum
        Scalar total = sum(hists[i]);
        float scale = (float)hist_h/(float)total[0];

        Scalar total_Equalized = sum(hists_Equalized[i]);
        float scale_Equalized = (float)hist_h/(float)total_Equalized[0];

        // Plot the histogram
        float prevVal, currVal, prevAccuVal, currAccuVal;
        prevVal = cvRound(hists[i].at<float>(0));
        prevAccuVal = scale * prevVal;

        float prevVal_Equalized, currVal_Equalized, prevAccuVal_Equalized, currAccuVal_Equalized;
        prevVal_Equalized = cvRound(hists_Equalized[i].at<float>(0));
        prevAccuVal_Equalized = scale_Equalized * prevVal_Equalized;


        for (int b = 1; b < histSize; b++)
        {
            // Current iteration
            currVal = cvRound(hists[i].at<float>(b));
            currAccuVal = prevAccuVal + scale * currVal;

            currVal_Equalized = cvRound(hists_Equalized[i].at<float>(b));
            currAccuVal_Equalized = prevAccuVal_Equalized + scale_Equalized * currVal_Equalized;

            // Plot the histogram: normal
            line(normalHistImage, Point(bin_w*(b-1), hist_h - prevVal),
                                  Point(bin_w*(b),   hist_h - currVal),
                                  color, 2);

            // Plot the histogram: accumulated
            line(accumulatedHistImage, Point(bin_w*(b-1), hist_h - prevAccuVal_Equalized),
                                       Point(bin_w*(b),   hist_h - currAccuVal_Equalized),
                                       color, 2);

            // Next iteration
            prevVal = currVal;
            prevAccuVal = currAccuVal;

            prevVal_Equalized = currVal_Equalized;
            prevAccuVal_Equalized = currAccuVal_Equalized;
        }
    }

    // Display the image and its histogram
    Mat rstHistImage;
    vconcat(normalHistImage, accumulatedHistImage, rstHistImage);
    // imshow("result", rstHistImage);

    resize(rstHistImage, rstHistImage, rstImage.size());
    
    Mat result;
    hconcat(rstImage, rstHistImage, result);
    imshow("result", result);

   
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;

}

