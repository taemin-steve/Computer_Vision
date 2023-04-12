#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Trackbar callback function
void do_nothing(int pos, void *param)
{
}

int main()
{
    // Create a video capture object
    VideoCapture capture(0);

    // Check if camera loading is successful
    if (!capture.isOpened())
    {
        cout << "Error: No camera exists!" << endl;
        exit(-1);
    }

    // Create a window
    String strWindowName = "Canny Edge Detection";
    namedWindow(strWindowName);

    // Create trackbars
    int default_value[] = {2000, 4000};
    createTrackbar("Thld1", strWindowName, default_value,   5000, do_nothing);
    createTrackbar("Thld2", strWindowName, default_value+1, 5000, do_nothing);

    // Infinite loop
    Mat frame, flipped_frame, img_gray, img_edge, img_result;
    while (true)
    {
        // Read a video frame
        capture >> frame;

        // Check if frame capture is successful
        if (frame.empty()) break;

        // Flip the image horizontally
        flip(frame, flipped_frame, 1);

        // Convert the frame to gray
        cvtColor(flipped_frame, img_gray, COLOR_BGR2GRAY);

        // Get the threshold values
        int thld1 = getTrackbarPos("Thld1", strWindowName);
        int thld2 = getTrackbarPos("Thld2", strWindowName);

        // Canny edge detection
        Canny(img_gray, img_edge, thld1, thld2, 5);

        // Copy to the result and make it dark
        flipped_frame.copyTo(img_result);
        img_result = img_result/2;

        // For each pixel
        uchar *pImgEdge, *pImgResult;
        for (int row = 0; row < img_edge.rows; ++row)
        {
            pImgEdge  = img_edge.ptr<uchar>(row);
            pImgResult = img_result.ptr<uchar>(row);
            for (int col = 0; col < img_edge.cols; ++col)
            {
                // If it is an edge
                if (pImgEdge[col] != 0)
                {
                    // Draw the edge in green
                    pImgResult[3*col + 0] = 0;
                    pImgResult[3*col + 1] = 255;
                    pImgResult[3*col + 2] = 0;        
                }
            }
        }

        // Display the frame in a window
        imshow("Canny Edge Detection", img_result);

        // Take the keyboard input
        char key = waitKey(1);

        // Press ESC to quit
        if (key == 27) break;

        // Press Spacebar to pause
        if (key == 32)
        {
            key = waitKey(0);
            if (key == 27) break;
        }
    }

    // Release the capture object
    capture.release();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}