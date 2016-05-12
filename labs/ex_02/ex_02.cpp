#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int MAX_KERNEL_LENGTH = 60;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout << "Usage: ex_02.out image" << endl;
     return -1;
    }

    // read the image
    Mat image;
    image = imread( argv[1], CV_LOAD_IMAGE_COLOR ); 

    // check for errors
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << endl;
        return -1;
    }

    //-----------------------------------------------------------------------------------

    // apply the gausian blur
    Mat image_gauss;
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ){ 
        GaussianBlur( image, image_gauss, Size( i, i ), 0, 0 );
    }

    //-----------------------------------------------------------------------------------

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );    // Create a window for display.
    imshow( windowName1, image );                   // Show our image inside it.
    moveWindow( windowName1, 0, 0 );                 // Move our window

    // show the blurred image
    string windowName2 = "Gaussian blurred image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image_gauss );
    moveWindow( windowName2, image.size().width, 0 );

    //-----------------------------------------------------------------------------------

    waitKey(0);
    return 0;
}