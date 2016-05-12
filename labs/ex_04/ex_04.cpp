#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout << "Usage: ex_04.out image" << endl;
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

    // apply medianblur
    Mat image_median;
    medianBlur( image, image_median,5 );

    //-----------------------------------------------------------------------------------

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0 );

    // show the blurred image
    string windowName2 = "Median blur image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image_median );
    moveWindow( windowName2, image.size().width, 0 );
    
    //-----------------------------------------------------------------------------------

    waitKey(0);
    return 0;
}
