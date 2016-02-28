#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
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
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    // read the image
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); 

    // check for errors
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    // apply unsharp mask
    Mat image_unsharp_masked;
    GaussianBlur(image, image_unsharp_masked, Size(9,9), 10);
    addWeighted(image, 1.5, image_unsharp_masked, -0.5, 0, image_unsharp_masked);

    // show the original image
    namedWindow( "Original image", WINDOW_AUTOSIZE );
    imshow( "Original image", image );

    // show the blurred image
    namedWindow( "Unsharp masked image", WINDOW_AUTOSIZE );
    imshow( "Unsharp masked image", image_unsharp_masked );

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
