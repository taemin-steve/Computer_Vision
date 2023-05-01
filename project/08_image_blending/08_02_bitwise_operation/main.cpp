#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_messi = imread("messi5.jpg");
    Mat img_logo  = imread("opencv-logo-white.png");

    // Check if image loading is successful
    if (img_messi.empty() || img_logo.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Display the result
    imshow("Lionel Messi", img_messi);
    imshow("OpenCV Logo", img_logo);
    waitKey();

    // Now create a mask of logo and create its inverse mask also
    Mat img_logo_gray;
    cvtColor(img_logo, img_logo_gray, COLOR_BGR2GRAY);

    Mat img_mask, img_mask_inv;
    threshold(img_logo_gray, img_mask, 10, 255, THRESH_BINARY); // 그레이 스케일로 바꾼다음에 마스크 만들어 버림
    bitwise_not(img_mask, img_mask_inv); // 비트와이즈로 마스크 인버스

    // I want to put logo on top-left corner, So I create a ROI
    Mat img_roi = img_messi(Rect(0, 0, img_logo.cols, img_logo.rows)); // 로고 크기만큼 ROI 땀

    // Take only region of logo from logo image
    Mat img_logo_fg;
    bitwise_and(img_logo, img_logo, img_logo_fg, img_mask);// 마지막 옵션에 마스크 영역에 대해서만 하게끔 가능


    // Now black-out the area of logo in ROI
    Mat img_messi_bg;
    bitwise_and(img_roi, img_roi, img_messi_bg, img_mask_inv);// 
    imshow("1", img_messi_bg);

    // Put logo in ROI and modify the main image
    add(img_logo_fg, img_messi_bg, img_roi);

    // Display the result
    imshow("Lionel Messi with OpenCV Logo", img_messi);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}