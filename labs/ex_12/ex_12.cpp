// see: http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 3)
    {
        cout << "Usage: ex_12.out image1 image2" << endl;
        return -1;
    }

    // read the image
    Mat image1;
    image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat image2;
    image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);

    // check for errors
    if(! image1.data )
    {
        cout <<  "Could not open or find the first image" << endl;
        return -1;
    }
    if(! image2.data )
    {
        cout <<  "Could not open or find the second image" << endl;
        return -1;
    }

    //-----------------------------------------------------------------------------------

    // STEP 1: 


    //-----------------------------------------------------------------------------------

    // show the original image 1
    string windowName1 = "Original image 1";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image1 );
    moveWindow( windowName1, 0, 0);

    // show the original image
    string windowName2 = "Original image 2";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image2 );
    moveWindow( windowName2, image1.size().width, 0);

    /*// show the canny edges
    string windowName2 = "Canny edges";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, cannyEdges );
    moveWindow( windowName2, image.size().width, 0);

    // show the original image
    string windowName3 = "Result";
    namedWindow( windowName3, WINDOW_AUTOSIZE );
    imshow( windowName3, image_dst );
    moveWindow( windowName3, 
        image.size().width + cannyEdges.size().width, 0);*/

    //-----------------------------------------------------------------------------------

    // Wait for a keystroke in the window
    waitKey(0);
    return 0;
}