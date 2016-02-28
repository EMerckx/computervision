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

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    Mat gray_image;
    cvtColor(image, gray_image, CV_BGR2GRAY);

    Mat tres_image;
    threshold( gray_image, tres_image, 127, 0, CV_THRESH_TRUNC );

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", tres_image );                   // Show our image inside it.

    // write images
    imwrite( "1_gray_image.png", gray_image );
    imwrite( "1_tres_image.png", tres_image );

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}