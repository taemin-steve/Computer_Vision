#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_logo  = imread("opencv-logo-white.png");

    // Check if image loading is successful
    if (img_logo.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Display the result

    Mat img_BGR[3];
    split(img_logo, img_BGR);

    Mat img_BGR_R_Mask;
    threshold(img_BGR[2], img_BGR_R_Mask, 10, 255, THRESH_BINARY);

    Mat img_BGR_G_Mask;
    threshold(img_BGR[1], img_BGR_G_Mask, 10, 255, THRESH_BINARY);

    Mat img_BGR_B_Mask;
    threshold(img_BGR[0], img_BGR_B_Mask, 10, 255, THRESH_BINARY);

    Mat img_BGR_RG_Mask;
    bitwise_and(img_BGR_R_Mask,img_BGR_G_Mask,img_BGR_RG_Mask);
    Mat img_BGR_RGB_Mask;
    bitwise_and(img_BGR_RG_Mask,img_BGR_B_Mask,img_BGR_RGB_Mask);

    cvtColor(img_BGR_R_Mask, img_BGR_R_Mask, COLOR_GRAY2BGR);
    cvtColor(img_BGR_G_Mask, img_BGR_G_Mask, COLOR_GRAY2BGR);
    cvtColor(img_BGR_B_Mask, img_BGR_B_Mask, COLOR_GRAY2BGR);
    cvtColor(img_BGR_RGB_Mask, img_BGR_RGB_Mask, COLOR_GRAY2BGR);

    Mat result;
    hconcat(img_logo,img_BGR_R_Mask,result);
    hconcat(result,img_BGR_G_Mask,result);
    hconcat(result,img_BGR_B_Mask,result);
    hconcat(result,img_BGR_RGB_Mask,result);





    imshow("OpenCV Logo", result);
    waitKey();


    // // Now create a mask of logo and create its inverse mask also
    // Mat img_logo_gray;
    // cvtColor(img_logo, img_logo_gray, COLOR_BGR2GRAY);

    // Mat img_mask, img_mask_inv;
    // threshold(img_logo_gray, img_mask, 10, 255, THRESH_BINARY);
    // bitwise_not(img_mask, img_mask_inv);

    // // I want to put logo on top-left corner, So I create a ROI
    // Mat img_roi = img_messi(Rect(0, 0, img_logo.cols, img_logo.rows));

    // // Take only region of logo from logo image
    // Mat img_logo_fg;
    // bitwise_and(img_logo, img_logo, img_logo_fg, img_mask);

    // // Now black-out the area of logo in ROI
    // Mat img_messi_bg;
    // bitwise_and(img_roi, img_roi, img_messi_bg, img_mask_inv);

    // // Put logo in ROI and modify the main image
    // add(img_logo_fg, img_messi_bg, img_roi);

    // // Display the result
    // imshow("Lionel Messi with OpenCV Logo", img_messi);
    // waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}