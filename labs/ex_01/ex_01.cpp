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
    
    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );    // Create a window for display.
    imshow( windowName1, image );                   // Show our image inside it.
    moveWindow( windowName1, 0, 0);                 // Move our window

    // show the original image
    string windowName2 = "Treshold image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, tres_image );
    moveWindow( windowName2, image.size().width, 0);

    // write images
    imwrite( "1_gray_image.png", gray_image );
    imwrite( "1_tres_image.png", tres_image );

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}