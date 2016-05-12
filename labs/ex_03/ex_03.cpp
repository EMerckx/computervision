#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int MAX_KERNEL_LENGTH = 60;

// source: http://opencv-code.com/quick-tips/sharpen-image-with-unsharp-mask/
// Perform in-place unsharp masking operation
void unsharpMask(cv::Mat& im) 
{
    Mat tmp;
    GaussianBlur(im, tmp, cv::Size(0,0), 5);
    addWeighted(im, 1.5, tmp, -0.5, 0, im);
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout << "Usage: ex_03.out image" << endl;
     return -1;
    }

    // read the image
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); 

    // check for errors
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << endl;
        return -1;
    }

    //-----------------------------------------------------------------------------------

    // apply unsharp mask
    Mat image_unsharp_masked;
    GaussianBlur(image, image_unsharp_masked, Size(9,9), 10);
    addWeighted(image, 1.5, image_unsharp_masked, -0.5, 0, image_unsharp_masked);

    //-----------------------------------------------------------------------------------

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );    // Create a window for display.
    imshow( windowName1, image );                   // Show our image inside it.
    moveWindow( windowName1, 0, 0 );                 // Move our window

    // show the blurred image
    string windowName2 = "Unsharp masked image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image_unsharp_masked );
    moveWindow( windowName2, image.size().width, 0 );

    //-----------------------------------------------------------------------------------

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
