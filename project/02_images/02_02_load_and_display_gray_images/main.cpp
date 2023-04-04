#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image in a grayscale
    Mat img = imread("messi5.jpg", IMREAD_GRAYSCALE); //! is imread() is shallow copy? how can i test it??

    // Check if image loading is successful
    if (img.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Display the image in a window
    imshow("Lionel Messi in Grayscale", img);

    /// Test for shallow copy-----------------
    Mat img_copy_shallow = img;
    Mat img_copy_Deep = img.clone();
    img = imread("messi5.jpg");
    imshow("shallow_copy", img_copy_shallow); // It should be color image
    imshow("deep_copy", img_copy_Deep); // It should be gray Image
    ///----------------------------------------

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}