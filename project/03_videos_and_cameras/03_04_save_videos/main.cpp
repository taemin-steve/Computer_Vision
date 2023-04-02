#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Create a video capture object
    VideoCapture videoCapture(0);

    // Check if camera loading is successful
    if (!videoCapture.isOpened())
    {
        cout << "Error: No camera exists!" << endl;
        exit(-1);
    }

    // Video properties
    float videoFPS  = videoCapture.get(CAP_PROP_FPS);
    int videoWidth  = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    int videoHeight = videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    cout << "video FPS : "    << videoFPS    << endl;
    cout << "video width : "  << videoWidth  << endl;
    cout << "video height : " << videoHeight << endl;

    // Create and open a video writer object
    VideoWriter videoWriter;
    videoWriter.open("output", 
                     VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                     videoFPS , 
                     Size(videoWidth, videoHeight), 
                     true);

   // Check if opening a video writer is successful
    if (!videoWriter.isOpened())
    {
        cout << "Error: Can't write a video!" << endl;
        exit(-1);
    }

    // Infinite loop
    Mat frame, flipped_frame;
    while (true)
    {
        // Read a video frame
        videoCapture >> frame;

        // Check if frame capture is successful
        if (frame.empty()) break;

        // Save the frame
        videoWriter << frame;

        // Display the frame in a window
        imshow("Video Frame", frame);

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

    // Release the capture and writer object
    videoCapture.release();
    videoWriter.release();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}