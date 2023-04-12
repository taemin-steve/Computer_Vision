#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// constants
const int DELAY_CAPTION = 2000;
const int DELAY_BLUR = 400;
const int MAX_KERNEL_LENGTH = 31;
const char WINDOW_NAME[] = "Smoothing Demo";

// global variables
Mat g_img_src;
Mat g_img_dst;

// global functions that work on the global variables
int display_caption(const char* caption);
int display_result(int delay = DELAY_BLUR);

int main()
{
    // Create a window
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);

    // Load a color image
    g_img_src = imread("lena.jpg", IMREAD_COLOR);
    if (g_img_src.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Original image
    if (display_caption("Original Image") != 0) return 0;
    g_img_dst = g_img_src.clone();
    display_result(-1);

    // Box blur
    if (display_caption("Homogeneous Blur") != 0) return 0;
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        blur(g_img_src, g_img_dst, Size(i, i));
        if( display_result() != 0 ) return 0;
    }

    // Gaussian blur
    if (display_caption("Gaussian Blur") != 0) return 0;
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        GaussianBlur(g_img_src, g_img_dst, Size(i, i), 0, 0);
        if (display_result() != 0) return 0;
    }

    // Median blur
    if (display_caption("Median Blur") != 0) return 0;
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        medianBlur(g_img_src, g_img_dst, i);
        if (display_result() != 0) return 0;
    }

    // Bilateral blur
    if (display_caption("Bilateral Blur") != 0) return 0;
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        bilateralFilter(g_img_src, g_img_dst, i, i*2, i/2);
        if (display_result() != 0 ) return 0;
    }

    // Destroy all windows
    waitKey();
    destroyAllWindows();

    return 0;
}

// display caption in a black image
int display_caption(const char* caption)
{
    // black image
    g_img_dst = Mat::zeros(g_img_src.size(), g_img_src.type());

    // put the caption 
    putText(g_img_dst, caption,
            Point(g_img_src.cols/4, g_img_src.rows/2),
            FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

    return display_result(DELAY_CAPTION);
}

// display the result image
int display_result(const int delay)
{
    // display the result
    imshow(WINDOW_NAME, g_img_dst);

    // wait the key
    int c = waitKey(delay);

    // if any key is pressed, done
    if (c >= 0) { return -1; }

    return 0;
}