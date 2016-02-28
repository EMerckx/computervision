#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

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

    // apply grayscale
    Mat image_grayscale;
    cvtColor( image, image_grayscale, CV_BGR2GRAY );

    // apply Sobel
    Mat image_sobel;
    Mat image_sobel_x, image_sobel_y;
    Sobel(image_grayscale, image_sobel, CV_32F, 1, 0, 3);

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0);

    // show the gray image
    string windowName2 = "Gray image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image_grayscale );
    moveWindow( windowName2, image.size().width, 0);

    // show the sobel image
    string windowName3 = "Sobel image";
    namedWindow( windowName3, WINDOW_AUTOSIZE );
    imshow( windowName3, image_sobel );
    moveWindow( windowName3, 2*image.size().width, 0);

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
