#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int MAX_KERNEL_LENGTH = 60;

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

    // apply the gausian blur
    Mat image_gauss;
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ){ 
        GaussianBlur( image, image_gauss, Size( i, i ), 0, 0 );
    }

    // show the original image
    namedWindow( "Original image", WINDOW_AUTOSIZE );
    imshow( "Original image", image );

    // show the blurred image
    namedWindow( "Gaussian blurred image", WINDOW_AUTOSIZE );
    imshow( "Gaussian blurred image", image_gauss );

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}